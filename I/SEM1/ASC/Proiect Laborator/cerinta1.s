.data
    n:          .space 4
    tmp:        .space 4
    m_counts:   .space 400          # M_i pentru fiecare nod (100 * 4 bytes)
    matrix:     .space 40000        # matricea de adiacenta (100 * 100 * 4 bytes)
    fmt_in:     .asciz "%d"
    fmt_num:    .asciz "%d"
    fmt_sp:     .asciz " "
    fmt_nl:     .asciz "\n"

.text
.globl main

main:
    pushl %esi                      # esi si edi trebuie restaurati la iesire
    pushl %edi

    # 1. citim si ignoram numarul cerintei
    pushl $tmp
    pushl $fmt_in
    call scanf
    addl $8, %esp

    # 2. citim numarul de noduri
    pushl $n
    pushl $fmt_in
    call scanf
    addl $8, %esp

    # 3. citim M_0 ... M_{N-1}
    xorl %esi, %esi                 # i = 0
read_m_loop:
    cmpl n, %esi
    jge read_m_end
    leal m_counts(,%esi,4), %eax   # adresa lui m_counts[i]
    pushl %eax
    pushl $fmt_in
    call scanf
    addl $8, %esp
    incl %esi
    jmp read_m_loop
read_m_end:

    # 4. citim vecinii si completam matricea
    xorl %esi, %esi                 # i = 0
read_adj_loop:
    cmpl n, %esi
    jge read_adj_end
    xorl %edi, %edi                 # j = 0
read_nb_loop:
    cmpl m_counts(,%esi,4), %edi   # j < M_i ?
    jge read_nb_end
    pushl $tmp
    pushl $fmt_in
    call scanf
    addl $8, %esp
    movl tmp, %eax                  # v = vecinul citit
    movl %esi, %ecx
    imull n, %ecx                   # ecx = i * N
    addl %eax, %ecx                 # ecx = i * N + v
    movl $1, matrix(,%ecx,4)        # matrix[i][v] = 1
    incl %edi
    jmp read_nb_loop
read_nb_end:
    incl %esi
    jmp read_adj_loop
read_adj_end:

    # 5. afisam matricea
    xorl %esi, %esi                 # i = 0
print_row_loop:
    cmpl n, %esi
    jge print_end
    xorl %edi, %edi                 # j = 0
print_col_loop:
    cmpl n, %edi
    jge print_col_end
    movl %esi, %ecx
    imull n, %ecx
    addl %edi, %ecx                 # ecx = i * N + j
    pushl matrix(,%ecx,4)
    pushl $fmt_num
    call printf
    addl $8, %esp
    movl n, %eax
    decl %eax
    cmpl %eax, %edi                 # ultima coloana? fara spatiu
    je no_space
    pushl $fmt_sp
    call printf
    addl $4, %esp
no_space:
    incl %edi
    jmp print_col_loop
print_col_end:
    pushl $fmt_nl
    call printf
    addl $4, %esp
    incl %esi
    jmp print_row_loop
print_end:

    xorl %eax, %eax                 # return 0
    popl %edi
    popl %esi
    ret