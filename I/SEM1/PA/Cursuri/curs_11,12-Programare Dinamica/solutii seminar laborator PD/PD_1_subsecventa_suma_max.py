"""
s[i]=suma maxima a unei subsecvente care se termina pe pozitia i
lung[i]= lungimea subsecventei de suma maxima care se termina pe pozitia i
s[i]=max{s[i-1]+v[i],v[i]}
daca s[i]=s[i-1]+v[i] atunci lung[i]=lung[i-1]+1, altfel lung[i]=1
"""


f=open("sir.in")
v=[int(x) for x in f.readline().split()]
f.close()
n=len(v)
s=[0]*n
lung=[0]*n
smax=s[0]=v[0]
lmax=lung[0]=1
pmax=0
for i in range(1,n):
    if s[i-1]>0:
        s[i]=s[i-1]+v[i]
        lung[i]=lung[i-1]+1
    else:
        s[i]=v[i]
        lung[i]=1
    if s[i]>smax:
        smax=s[i]
        lmax=lung[i]
        pmax=i-lung[i]+1
print(lmax)
print(v)
print(s)
print(lung)
for i in range(pmax,pmax+lmax):
    print(v[i],end=" ")

#fara vectori
smax = s= v[0]
lmax = lung = 1
pmax = 0
for i in range(1, n):
    if s  > 0:
        s = s + v[i]
        lung = lung + 1
    else:
        s = v[i]
        lung = 1
    if s > smax:
        smax = s
        lmax = lung
        pmax = i - lung + 1
print(lmax)
print(v)
print(s)
print(lung)
for i in range(pmax, pmax + lmax):
    print(v[i], end=" ")
