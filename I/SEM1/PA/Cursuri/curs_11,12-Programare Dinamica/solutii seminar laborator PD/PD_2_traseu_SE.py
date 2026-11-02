def afis_matrice(m):
    for linie in m:
        for x in linie:
            print(f"{x:4}", end="")
        print()


f = open("matrice_S_E.in")
m,n= (int(x) for x in f.readline().split())
a = []
for linie in f:
    a.append([int(x) for x in linie.split()])
f.close()

print(a)

#VARIANTA 1 s[i][j] = suma maxima pentru un traseu care se termina pe pozitia (i,j) (incepand din (1,1), de fapt (0,0))

s=[[0 for j in range(n)] for i in range(m)]

#stim direct
s[0][0]=a[0][0]

#calculam prima linie din s
for j in range(1,n):
    s[0][j]=a[0][j]+s[0][j-1]

#calculam prima coloana din s
for i in range(1,m):
    s[i][0]=a[i][0]+s[i-1][0]

for i in range(1,m):
    for j in range(1,n):
        if s[i-1][j]>s[i][j-1]:
            s[i][j]=a[i][j]+s[i-1][j]
        else:
            s[i][j]=a[i][j]+s[i][j-1]
afis_matrice(a)
print()
afis_matrice(s)
print("suma maxima ",s[m-1][n-1])

#reconstituire traseu din recurenta - de la sfarsit (m-1,n-1) la inceput:
def traseu(i,j):
    if i>=0:

        if j>0 and s[i][j]==a[i][j]+s[i][j-1]:
            traseu(i,j-1)
        else:
            traseu(i-1, j)
        print(f"{i + 1} {j + 1}")

traseu(m-1,n-1)


#VARIANTA 1 s[i][j] = suma maxima pentru un traseu care incepe pe pozitia (i,j)
# (si terminand pe pozitia (m,n))

s=[[0 for j in range(n)] for i in range(m)]

#stim direct
s[m-1][n-1]=a[m-1][n-1]

#calculam ultima linie din s
for j in range(n-2,-1,-1):
    s[m-1][j]=a[m-1][j]+s[m-1][j+1]

#calculam ultima coloana din s
for i in range(m-2,-1,-1):
    s[i][n-1]=a[i][n-1]+s[i+1][n-1]

for i in range(m-2,-1,-1):
    for j in range(n-2,-1,-1):
        if s[i+1][j]>s[i][j+1]:
            s[i][j]=a[i][j]+s[i+1][j]
        else:
            s[i][j]=a[i][j]+s[i][j+1]
afis_matrice(a)
print()
afis_matrice(s)
print("suma maxima ",s[0][0])

#reconstituire traseu din recurenta - de la (0,0)
def traseu(i,j):
    if i<=m-1 and j<=n-1:
        print(f"{i + 1} {j + 1}")
        if i<m-1 and s[i][j]==a[i][j]+s[i+1][j]: #!!iesire din matrice
            traseu(i+1,j)
        else:
            traseu(i, j+1)


traseu(0,0)