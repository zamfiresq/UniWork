ls=input().split()
n=int(ls[0])
m=int(ls[1])
#print(n,m)
"""
n,m =[int(x) for x in input().split()] #"4 3" => ["4","3"], n,m=[4,3]
print(n,m)
"""
"""
a=[]
for i in range(n):
    linie_i=[int(x) for x in input().split()]
    a.append(linie_i)
print(a)
"""
a=[[int(x) for x in input().split()] for i in range(n)]
print(a)

for linie in a: #o linie este o lista
    for x in linie:
        print(x,end=" ")
    print()
print()
for i in range(n):
    for j in range(m):
        print(a[i][j],end=" ")
    print()
lista_maxime=[]
for linie in a: #o linie este o lista
    max_linie=max(linie)
    lista_maxime.append(max_linie)
print(lista_maxime)

#varianta cu comprehension
lista_maxime=[max(linie) for linie in a]
print(lista_maxime)
