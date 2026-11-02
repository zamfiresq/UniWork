f=open("cuburi.in")
n,p=(int(x) for x in f.readline().split())
cuburi=[]
for i in range(n):
    ls=[int(x) for x in f.readline().split()]
    cuburi.append((ls[0],ls[1],i))
print(cuburi)
cuburi.sort(reverse=True)
h=[0]*n
pred=[None]*n
h[0]=cuburi[0][0]
pred[0]=None
hmax=h[0]
pmax=0
for i in range(1,n):
    h[i]=cuburi[i][0]

    for j in range(i):

        if cuburi[i][1]!=cuburi[j][1] and cuburi[i][0]<cuburi[j][0] and h[j]+cuburi[i][0]>h[i]:
            h[i]=h[j]+cuburi[i][0]
            pred[i]=j
    if h[i]>hmax:
        hmax=h[i]
        pmax=i
def afis(cuburi,pred,pmax):
    if pmax!=None:
        afis(cuburi,pred,pred[pmax])
        print(cuburi[pmax],end=' ')

afis(cuburi,pred,pmax)

print()
#h[i]=care are in varf cubul i
#pred[i]=indicele cubului anterior
#depinde de cuburi cu latura mai mare ->ordine de calcul descrescator dupa latura



#h[i]=care are la baza cubul i

cuburi.sort()
h=[0]*n
pred=[None]*n
h[0]=cuburi[0][0]
pred[0]=None
hmax=h[0]
pmax=0
for i in range(1,n):
    h[i]=cuburi[i][0]

    for j in range(i):

        if cuburi[i][1]!=cuburi[j][1] and cuburi[i][0]>cuburi[j][0] and h[j]+cuburi[i][0]>h[i]:
            h[i]=h[j]+cuburi[i][0]
            pred[i]=j
    if h[i]>hmax:
        hmax=h[i]
        pmax=i
def afis(cuburi,pred,pmax):
    if pmax!=None:
        afis(cuburi,pred,pred[pmax])
        print(cuburi[pmax],end=' ')

afis(cuburi,pred,pmax)