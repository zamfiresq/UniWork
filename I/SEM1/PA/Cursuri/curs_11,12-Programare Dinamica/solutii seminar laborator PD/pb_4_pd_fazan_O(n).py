prop="unu mama marte carte mare teatru doi" #pp cuvintele lung>=2
sir=prop.split()
n=len(sir)
lung=[0 for i in range(n)]
pred=[-1 for i in range(n)]
d={}
lung[0]=1 #pred[0]ramane -1
imax=0
sufix_cuv=sir[0][-2:]
d[sufix_cuv]=0
print(d)
for i in range(1,n):
    """
    lmax=0
    for j in range(i):
        if (sir[j][-2:]==sir[i][:2]) and (lung[j]>lmax):
            lmax=lung[j]
            pred[i]=j
    lung[i]=1+lmax
    """
    sufix_cuv=sir[i][-2:]
    prefix_cuv=sir[i][:2]
    if  prefix_cuv in d:
        lung[i]= 1 + lung[d[prefix_cuv]]
        pred[i] = d[prefix_cuv]
    else:
        lung[i] = 1

    if lung[i]>lung[imax]:
        imax=i

    #actualizarea dictionarului
    if sufix_cuv in d:
        if lung[i]>lung[d[sufix_cuv]]:
            d[sufix_cuv]=i
    else:
        d[sufix_cuv]=i
    print(d)

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
def f(x,y):
    return x+y
ls=[8,9]
print(f(*ls))
