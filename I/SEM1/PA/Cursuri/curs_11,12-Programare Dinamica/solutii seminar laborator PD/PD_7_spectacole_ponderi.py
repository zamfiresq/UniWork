#Varianta 1:
# profit_term[i]= profit maxim submultime spectacole care SE TERMINA cu spectacolul i:
# depinde de activitati care se termina inainte de i =>n2
#profit_term[i]=max{castig(i)+profit_term[j]|j este inaintea lui i si nu se intersect cu i
#=>activitatile ordonate dupa sfarsit
def citire_spectacole(nume_fisier):
    ls = []
    i=0
    with open(nume_fisier) as f:
        n=int(f.readline())
        for linie in f:
            i=i+1
            liniesplit=linie.split()
            s, t = (int(x) for x in liniesplit[0].strip("[]\n").split(","))
            ls.append((i,[s,t],int(liniesplit[1]))) #primul element- indicele activitatii, al doilea -intervalul de desfasurare (putea fi memorat si ca tuplu)
    return n,ls

n,ls=citire_spectacole("spectacole_ponderi.in")

ls.sort(key=lambda x:x[1][1])
print(ls)
profit_term=[0]*n
pred=[None]*n
profit_term[0]=ls[0][2]
imax=0
for i in range(1,n):
    profit_term[i]=ls[i][2]

    for j in range(0,i): #dintre ctivitatile anterioare care nu se intersecteaza cu i -> cea cu profitul total maxim
        if ls[i][1][0]>ls[j][1][1] and profit_term[j]+ls[i][2]>profit_term[i]:
            profit_term[i]=profit_term[j]+ls[i][2]
            pred[i]=j
    if profit_term[i]>profit_term[imax]:
        imax=i
rez=[]
while imax!=None:
    rez.append(ls[imax])
    imax=pred[imax]
print(rez[::-1])

#Varianta 2:
#ult(i)=ultimul interval inainte de i care nu se inters cu acesta (si incepe inaintea lui)
#subpb:profitul maxim pt primele i activitati
#recurenta: profit_max[i]=max{iau obiectul i->mai raman {1,...,ult(i)}, restul sunt incompatibile cu i,nu iau obiectul i}
#                       =max{castig[i]+profit_max(ult[i]),profit_max[i-1] !!!daca nu are ult(i) atunci pp profit_max[]=0
#cplx depinde de cum calculez ult(i) - cu for j<i sau cu cautare binara a extrem initiale a lui i printre cele finale ale intervalelor dinainte

n,ls=citire_spectacole("spectacole_ponderi.in")

ls.sort(key=lambda x:x[1][1])
#calcul O(n2) pentru ult:
ult=[-1]*n
for i in range(1,n):
    for j in range(i-1,-1,-1):
        if ls[i][1][0]>ls[j][1][1]:
            ult[i]=j
            break
print(ult)
profit_term[0]=ls[0][2]
imax=0
for i in range(1,n):
    if ult[i]>=0:
        profit_term[i]=max(ls[i][2]+profit_term[ult[i]],profit_term[i-1])
    else:
        profit_term[i] =max(ls[i][2],profit_term[i-1])
    if profit_term[i]>profit_term[imax]:
        imax=i

rez=[]
while imax!=-1:
    if profit_term[imax]==profit_term[imax-1]: #nu am luat imax
        imax-=1
    else:
        rez.append(ls[imax])
        imax=ult[imax]
print(rez[::-1])

#determinare ult cu cautare binara - tema  
