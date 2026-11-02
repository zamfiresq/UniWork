def max_sum_subset(S, K):
    n = len(S)
    dp = [[False] * (K + 1) for _ in range(n + 1)]
    dp[0][0] = True

    for i in range(1, n + 1):
        for j in range(K + 1):
            dp[i][j] = dp[i - 1][j]
            if j >= S[i - 1]:
                dp[i][j] = dp[i][j] or dp[i - 1][j - S[i - 1]]

    max_sum = 0
    for j in range(K, -1, -1):
        if dp[n][j]:
            max_sum = j
            break

    return max_sum


# Acest cod definește o funcție numită max_sum_subset care primește două argumente: S și K. Această funcție calculează suma maximă a unei submulțimi a listei S care nu depășește valoarea K.
# În interiorul funcției, se inițializează o matrice dp cu dimensiunea (n + 1) x (K + 1), unde n este lungimea listei S. Această matrice este folosită pentru a stoca informații despre sumele parțiale calculate până într-un anumit punct.
# Se setează dp[0][0] ca fiind True, deoarece suma vidă (fără elemente) este întotdeauna 0.
# Se parcurge lista S și se actualizează matricea dp folosind o abordare de programare dinamică. Pentru fiecare element din S, se verifică dacă suma j poate fi obținută folosind elementele anterioare. Dacă suma j este mai mare sau egală cu elementul curent S[i - 1], atunci se actualizează dp[i][j] cu valoarea dp[i - 1][j - S[i - 1]]. 
# În caz contrar, se păstrează valoarea anterioară dp[i - 1][j].
# După actualizarea matricei dp, se găsește suma maximă max_sum care poate fi obținută în submulțimea listei S care nu depășește K. 
# Se parcurge matricea dp de jos în sus și se găsește prima valoare j pentru care dp[n][j] este True. Aceasta reprezintă suma maximă căutată.
# La final, funcția returnează max_sum, adică suma maximă a unei submulțimi a listei S care nu depășește K.
# Această funcție utilizează o abordare de programare dinamică pentru a rezolva problema sumei maxime a unei submulțimi și are o complexitate de timp de O(n * K), unde n este lungimea listei S și K este valoarea maximă permisă.


# n = int(input())
# k = int(input())
# s = []
# for i in range(n):
#     s.append(int(input()))

# dp = [[0 for i in range (k+1)] for j in range(n+1)]
# for i in range(n):
#     for j in range(1,k+1):
#         elem = 0
#         if  dp[i-1][j-s[i-1]] + s[i-1] <=j:
#             elem = dp[i-1][j-s[i-1]] + s[i-1]
#         dp[i][j]=max(dp[i-1][j],elem)


# print (dp[n-1][k])

# Exemplu de utilizare
S = [1, 2, 3, 4, 5]
K = 10
max_sum = max_sum_subset(S, K)
print("Suma maxima este:", max_sum)
