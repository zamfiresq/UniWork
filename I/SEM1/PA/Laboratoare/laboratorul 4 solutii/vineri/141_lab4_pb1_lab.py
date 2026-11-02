#grupare p-rime (p-sufix)
nume_fisier=input()
p=int(input())
d={}#cheie=sufix, valoarea=lista cu cuvintele avand acel sufix
f=open(nume_fisier)
for linie in f:
    ls_cuvinte=linie.split()
    for cuv in ls_cuvinte:
        sufix_cuv=cuv[-p:]
        if sufix_cuv in d: #cauta intre chieile dictionarului
            d[sufix_cuv].append(cuv)
        else:
            d[sufix_cuv]=[cuv]
f.close()
print(d)
grupuri=list(d.values())
print(grupuri)
grupuri.sort(key=len,reverse=True)
print(grupuri)
for grup in grupuri:
    grup.sort(reverse=True)
    print(*grup)
g=open("rime.out","w")
for grup in grupuri:
    grup.sort(reverse=True)
    g.write(" ".join(grup))
    g.write("\n")
g.close()