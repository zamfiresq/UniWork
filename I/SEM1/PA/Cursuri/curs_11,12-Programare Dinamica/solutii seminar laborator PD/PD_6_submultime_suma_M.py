#subpb: (s,i) - se poate obtine suma s din primele i elemente
#v[s][i] = true ddc v[s-ai][i-1] este true #s=1,..,M
#stim v[0][0]=True, v[s][0]=False (cu submultimea vida putem obtine suma 0)

f=open("multime.in")
n=int(f.readline())
a=[0]
a.extend([int(x) for x in f.readline().split()])
M=int(f.readline())
v=[[False for j in range(M+1)] for i in range(n+1)]
elem=[[0 for j in range(M+1)] for i in range(n+1)]
v[0][0]=True
for i in range(1, n + 1):
    for s in range(0, M + 1):
        #daca s nu s-a putut inca obtine vedem daca putem obtine suna s folosind a[i]
        #s se poate obtine folosind a[i] <=> s-a[i] s-a putut deja obtine (pana la pasul i-1)
        if v[i-1][s]==False and s >= a[i] and v[i-1][s-a[i]]==True:
            v[i][s] = True
            elem[i][s] = a[i]
        else:
            v[i][s] = v[i-1][s]
            elem[i][s] = elem[i - 1][s]
print(v[n][M])
if v[n][M]:
    i = n
    s = M
    while s>0:
        print(elem[i][s],end=" ")
        s=s-elem[i][s]
        i=i-1

f.close()
print()
print("varianta cu un vector")
#VARIANTA
#suficient vector pentru memoizare, nu matrice
f=open("multime.in")
n=int(f.readline())
a=[int(x) for x in f.readline().split()]
M=int(f.readline())
v=[None]*(M+1)
v[0]=-1
for i in range(n):
    #print(v)
    #print(a[i])
    for s in range(M,a[i]-1,-1):
        if v[s]==None and v[s-a[i]] != None:
            v[s]=i #indice ultimului element
#print(a)
#print(v)
if v[M]!=None:
    s=M
    while s>0:
        print(a[v[s]],end=" ")
        s=s-a[v[s]]

