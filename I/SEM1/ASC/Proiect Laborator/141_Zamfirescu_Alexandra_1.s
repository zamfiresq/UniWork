.data
    n:          .space 4
    task:       .space 4
    k_len:      .space 4
    src:        .space 4
    dst:        .space 4
    nn:         .space 4                # n * n
    tmp:        .space 4
    map_size:   .space 4                # dimensiunea blocului alocat cu mmap2
    ptr_a:      .space 4                # adresa matricei de adiacenta A
    ptr_res:    .space 4                # adresa matricei A^p
    ptr_prod:   .space 4                # adresa matricei produs
    m_counts:   .space 400              # M_i pentru fiecare nod (100 * 4 bytes)
    fmt_in:     .asciz "%d"
    fmt_num:    .asciz "%d "
    fmt_res:    .asciz "%d"

.text
.globl main

# matrix_mult(m1, m2, mres, n): mres = m1 * m2 (matrici patratice n x n, elemente de 4 bytes)
matrix_mult:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx                          # registri care trebuie restaurati
    pushl %esi
    pushl %edi
    subl $4, %esp                       # variabila locala: sum = -16(%ebp)

    xorl %esi, %esi                     # i = 0
mm_i_loop:
    cmpl 20(%ebp), %esi
    jge mm_end
    xorl %edi, %edi                     # j = 0
mm_j_loop:
    cmpl 20(%ebp), %edi
    jge mm_j_end
    movl $0, -16(%ebp)                  # sum = 0
    xorl %ebx, %ebx                     # k = 0
mm_k_loop:
    cmpl 20(%ebp), %ebx
    jge mm_k_end
    movl %esi, %eax
    imull 20(%ebp), %eax                # i * n
    addl %ebx, %eax                     # i * n + k
    movl 8(%ebp), %edx                  # adresa m1
    movl (%edx,%eax,4), %eax            # m1[i][k]
    movl %ebx, %ecx
    imull 20(%ebp), %ecx                # k * n
    addl %edi, %ecx                     # k * n + j
    movl 12(%ebp), %edx                 # adresa m2
    movl (%edx,%ecx,4), %ecx            # m2[k][j]
    imull %ecx, %eax                    # m1[i][k] * m2[k][j]
    addl %eax, -16(%ebp)                # sum += produs
    incl %ebx
    jmp mm_k_loop
mm_k_end:
    movl %esi, %eax
    imull 20(%ebp), %eax
    addl %edi, %eax                     # i * n + j
    movl 16(%ebp), %edx                 # adresa mres
    movl -16(%ebp), %ecx
    movl %ecx, (%edx,%eax,4)            # mres[i][j] = sum
    incl %edi
    jmp mm_j_loop
mm_j_end:
    incl %esi
    jmp mm_i_loop
mm_end:
    addl $4, %esp                       # dezalocam variabila locala
    popl %edi
    popl %esi
    popl %ebx
    popl %ebp
    ret

main:
    pushl %esi                          # esi si edi trebuie restaurati la iesire
    pushl %edi

    # 1. citim numarul cerintei
    pushl $task
    pushl $fmt_in
    call scanf
    addl $8, %esp

    # 2. citim numarul de noduri
    pushl $n
    pushl $fmt_in
    call scanf
    addl $8, %esp

    # alocam dinamic spatiul pentru cele 3 matrici (A, A^p, produs): 3 * n * n * 4 bytes
    movl n, %eax
    imull n, %eax
    movl %eax, nn                       # nn = n * n
    imull $12, %eax                     # 3 matrici * 4 bytes per element
    movl %eax, map_size

    pushl %ebx                          # ebx si ebp trebuie restaurati dupa apel
    pushl %ebp
    movl $192, %eax                     # eax = 192: numarul syscall-ului mmap2
    movl $0, %ebx                       # ebx = 0 (addr): lasam kernelul sa aleaga adresa
    movl map_size, %ecx                 # ecx = dimensiunea de alocat: 3 * n * n * 4 bytes
    movl $3, %edx                       # edx = 3 (PROT_READ | PROT_WRITE): citim si scriem in zona
    movl $0x22, %esi                    # esi = 0x22 (MAP_PRIVATE | MAP_ANONYMOUS): memorie privata, fara fisier
    movl $-1, %edi                      # edi = -1 (fd): mapare anonima, nu avem fisier asociat
    movl $0, %ebp                       # ebp = 0 (offset): nu e folosit la maparea anonima
    int $0x80                           # apelam kernelul; adresa blocului ajunge in eax
    popl %ebp
    popl %ebx

    movl %eax, ptr_a                    # A este la inceputul blocului (zona vine initializata cu 0)
    movl nn, %ecx
    shll $2, %ecx                       # ecx = n * n * 4 = dimensiunea unei matrici
    addl %ecx, %eax
    movl %eax, ptr_res                  # A^p urmeaza dupa A
    addl %ecx, %eax
    movl %eax, ptr_prod                 # produsul urmeaza dupa A^p

    # 3. citim M_0 ... M_{N-1}
    xorl %esi, %esi                     # i = 0
read_m_loop:
    cmpl n, %esi
    jge read_m_end
    leal m_counts(,%esi,4), %eax        # adresa lui m_counts[i]
    pushl %eax
    pushl $fmt_in
    call scanf
    addl $8, %esp
    incl %esi
    jmp read_m_loop
read_m_end:

    # 4. citim vecinii si completam matricea
    xorl %esi, %esi                     # i = 0
read_adj_loop:
    cmpl n, %esi
    jge read_adj_end
    xorl %edi, %edi                     # j = 0
read_nb_loop:
    cmpl m_counts(,%esi,4), %edi        # j < M_i ?
    jge read_nb_end
    pushl $tmp
    pushl $fmt_in
    call scanf
    addl $8, %esp
    movl tmp, %eax                      # v = vecinul citit
    movl %esi, %ecx
    imull n, %ecx                       # ecx = i * N
    addl %eax, %ecx                     # ecx = i * N + v
    movl ptr_a, %edx
    movl $1, (%edx,%ecx,4)              # A[i][v] = 1
    incl %edi
    jmp read_nb_loop
read_nb_end:
    incl %esi
    jmp read_adj_loop
read_adj_end:

    cmpl $1, task
    jne cerinta2

    # cerinta 1: afisam matricea
    xorl %esi, %esi                     # i = 0
print_row_loop:
    cmpl n, %esi
    jge main_end
    xorl %edi, %edi                     # j = 0
print_col_loop:
    cmpl n, %edi
    jge print_col_end
    movl %esi, %ecx
    imull n, %ecx
    addl %edi, %ecx                     # ecx = i * N + j
    movl ptr_a, %edx
    pushl (%edx,%ecx,4)
    pushl $fmt_num
    call printf
    addl $8, %esp
    incl %edi
    jmp print_col_loop
print_col_end:
    incl %esi
    jmp print_row_loop

cerinta2:
    # citim k (lungimea), sursa si destinatia
    pushl $k_len
    pushl $fmt_in
    call scanf
    addl $8, %esp
    pushl $src
    pushl $fmt_in
    call scanf
    addl $8, %esp
    pushl $dst
    pushl $fmt_in
    call scanf
    addl $8, %esp

    # res = A (A^1)
    xorl %esi, %esi
copy1_loop:
    cmpl nn, %esi
    jge copy1_end
    movl ptr_a, %edx
    movl (%edx,%esi,4), %eax
    movl ptr_res, %edx
    movl %eax, (%edx,%esi,4)
    incl %esi
    jmp copy1_loop
copy1_end:

    movl $1, %edi                       # p = 1
pow_loop:
    cmpl k_len, %edi
    jge pow_end
    pushl n                             # argumentele, de la dreapta la stanga
    pushl ptr_prod                      # mres
    pushl ptr_a                         # m2 = A
    pushl ptr_res                       # m1 = A^p
    call matrix_mult                    # prod = A^p * A
    addl $16, %esp

    xorl %esi, %esi                     # res = prod
copy2_loop:
    cmpl nn, %esi
    jge copy2_end
    movl ptr_prod, %edx
    movl (%edx,%esi,4), %eax
    movl ptr_res, %edx
    movl %eax, (%edx,%esi,4)
    incl %esi
    jmp copy2_loop
copy2_end:
    incl %edi
    jmp pow_loop
pow_end:

    movl src, %eax
    imull n, %eax
    addl dst, %eax                      # src * n + dst
    movl ptr_res, %edx
    pushl (%edx,%eax,4)
    pushl $fmt_res
    call printf
    addl $8, %esp

main_end:
    pushl %ebx
    movl $91, %eax                      # eax = 91: syscall munmap (echivalentul lui free)
    movl ptr_a, %ebx                    # ebx = adresa de inceput a blocului alocat cu mmap2
    movl map_size, %ecx                 # ecx = dimensiunea blocului, aceeasi ca la alocare
    int $0x80
    popl %ebx

    xorl %eax, %eax                     # return 0
    popl %edi
    popl %esi
    ret

.section .note.GNU-stack,"",@progbits