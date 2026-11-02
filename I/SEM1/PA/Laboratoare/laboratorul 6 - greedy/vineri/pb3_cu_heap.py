import heapq
f=open("intervale.in")
n=int(f.readline())
ls_intervale=[]
for linie in f:
    interv=[int(x) for x in linie.split()]
    ls_intervale.append(interv)
f.close()
ls_intervale.sort()
print(ls_intervale)
sali=[] #sali[i]= lista intervalelor programagte in sala i
h=[] #heap de perechi (timp de terminare sala, indice sala)
for interval in ls_intervale:
    #cautam o sala la care putem adauga intervalul
    #extragem din heap sala cu timpul de terminare cel mai mic
    if len(h) == 0: #primul interval - heap gol
        sala_noua = [interval]
        sali.append(sala_noua)
        heapq.heappush(h,(interval[1],0))
    else:
        timp_terminare,indice_sala=heapq.heappop(h) #sala cu timpul de terminare minim
        #verificam daca interval se poate programa in aceasta sala
        if timp_terminare < interval[0]:
            sali[indice_sala].append(interval) #il adaugam in sala
            #inseram sala in heap cu noul timp de terminare
            heapq.heappush(h,(interval[1], indice_sala))
        else : #nu, cream o sala noua
            sala_noua = [interval]
            sali.append(sala_noua)
            #actualizam heap
            #inseram sala noua in heap
            heapq.heappush(h, (interval[1], len(sali)-1)) #ultima sala, cea noua introdusa
            #punem inapoi in heap sala extrasa, pt ca nu am adaugat interval la ea
            heapq.heappush(h,(timp_terminare,indice_sala))
for s in sali:
    print(*s)