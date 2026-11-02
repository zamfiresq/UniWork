f=open("intervale.in")
n=int(f.readline())
ls_intervale=[]
for linie in f:
    interv=[int(x) for x in linie.split()]
    ls_intervale.append(interv)
f.close()
ls_intervale.sort()
print(ls_intervale)
sali=[] #sali[i]= lista intervalelor programate in sala i
for interval in ls_intervale:
    #cautam o sala la care putem adauga interval:
    for s in sali:
        ult_interval_din_s=s[-1] #se termina cel mai tarziu
        if ult_interval_din_s[1]<interval[0]:
            s.append(interval)
            break
    else: #daca nu a iesit cu break - nu a gasit sala
        sala_noua=[interval]
        sali.append(sala_noua)
print("programare sali")
i=1
for s in sali:
    print(f"sala {i}: ",end="")
    print(*s) #print(s[0],s[1],....)
    """
    for interv in s:
        print(interv,end=" ")
    print()
    """
    i+=1
