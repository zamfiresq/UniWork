#n=int(input())
v=[int(x) for x in input().split()]
frecv=[0 for i in range(100)]
#frecv=[0]*100
for x in v:
    frecv[x]+=1
nr_perechi=0
for i in range(100):
    nr_perechi+=frecv[i]//2
print(nr_perechi)

nr_perechi=0
for f in frecv:
    nr_perechi += f // 2
print(nr_perechi)

nr_perechi=sum([f//2 for f in frecv]) #dezavantaj- creeaza o noua lista in memorie
#puteam folosi generator
#nr_perechi=sum((f//2 for f in frecv))
print(nr_perechi)