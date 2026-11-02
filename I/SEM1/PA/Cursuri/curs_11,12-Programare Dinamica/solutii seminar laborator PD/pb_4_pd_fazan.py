prop="unu mama marte carte mare teatru doi" #pp cuvintele lung>=2
sir=prop.split()
n=len(sir)
lung=[0 for i in range(n)]
pred=[-1 for i in range(n)]
lung[0]=1 #pred[0]ramane -1
imax=0
for i in range(1,n):
    lmax=0
    for j in range(i):
        if (sir[j][-2:]==sir[i][:2]) and (lung[j]>lmax):
            lmax=lung[j]
            pred[i]=j
    lung[i]=1+lmax
    if lung[i]>lung[imax]:
        imax=i
print(lung)
print(pred)
print(imax)
print("lungime ",lung[imax])
print("un subsir")
rez=[]
while imax!=-1:
    rez.append(sir[imax])
    imax=pred[imax]
print(*rez[::-1])

