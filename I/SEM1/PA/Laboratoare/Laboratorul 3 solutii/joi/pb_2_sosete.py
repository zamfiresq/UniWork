#folosim vector de frecvente
"""
l=input().split()
for i in range(len(l)):
    l[i]=int(l[i])
print(l)
"""    
l=[int(x) for x in input().split()]
fr=[0 for i in range(100)] #fr=[0]*100
for x in l:
    fr[x]+=1
#parcurgem vectorul de frecvente
#nr de perechi cu elemente de valoare i = fr[i]//2
nr_perechi=0
for i in range(100):
    nr_perechi += fr[i]//2
print(nr_perechi)

"""varianta -suma cu comprehension
nr_perechi=sum([fr[i]//2 for i in range(100)]) #vom reveni - cu generator() in loc de [] pentru a nu creea o noua lsita
print(nr_perechi)
"""
