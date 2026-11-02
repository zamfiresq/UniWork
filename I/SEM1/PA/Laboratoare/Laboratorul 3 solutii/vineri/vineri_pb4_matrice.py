#s=input() "4 3"
#input().split() =>["4","3"]
"""
ls=input().split()
m=int(ls[0])
n=int(ls[1])
print(m,n)

#x,y=1,2
#x,y=[1,2]
m,n=input().split()
m=int(m)
n=int(n)
print(m,n)
"""

m,n=[int(x) for x in input().split()]
print(m,n)
"""
#CITIRE MATRICE
#varianta 1
a=[]
for i in range(m):
    linie=input().split()
    for j in range(len(linie)):
        linie[j]=int(linie[j])
    #linie=[int(x) for x in input().split()]
    a.append(linie)
print(a)

#varianta 2 - comprehensiune pt o linie
a=[]
for i in range(m):
    linie=[int(x) for x in input().split()]
    a.append(linie)
print(a)
"""
#varianta 3-doar comprehensiune
a=[[int(x) for x in input().split()] for i in range(m)]
print(a)

#AFISARE MATRICE
for linie in a: #linie este un vector de tip list
    for x in linie:
        print(x,end=" ")
    print()
#stil C
for i in range(m):
    for j in range(n):
        print(a[i][j], end=" ")
    print()

#vector cu max de pe fiecare linie
max_linii=[]
for linie in a:
    max_linii.append(max(linie))
print(max_linii)
#cu comprehensiune
max_linii=[max(linie) for linie in a]

"""
#Solutia completa cu comprehensiune
m,n=[int(x) for x in input().split()]
a=[[int(x) for x in input().split()] for i in range(m)]
max_linii=[max(linie) for linie in a]
"""
