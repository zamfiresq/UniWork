#grupare mult litere
d={}
f=open("litere.in")
for linie in f:
    ls_cuvinte=linie.split()
    for cuv in ls_cuvinte:
        litere_cuv=frozenset(cuv)
        if litere_cuv in d: #cauta intre chieile dictionarului
            d[litere_cuv].append(cuv)
        else:
            d[litere_cuv]=[cuv]
f.close()
print(d)
litere_grupuri=list(d.keys()) #sortam cheile
litere_grupuri.sort(key=len,reverse=True)
print(litere_grupuri)
def cheie(x):
    return len(x),x
for mult_litere in litere_grupuri:
#for mult_litere in sorted(d,key=len,reverse=True):
    if len(d[mult_litere])>1:
        d[mult_litere].sort(key=cheie)
        print(*d[mult_litere])
"""    
g=open("rime.out","w")
for grup in grupuri:
    grup.sort(reverse=True)
    g.write(" ".join(grup))
    g.write("\n")
g.close()
"""