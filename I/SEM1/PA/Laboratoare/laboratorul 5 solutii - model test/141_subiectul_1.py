def citire_numere(nume_fisier):
    matrice = []
    with open(nume_fisier) as f:
        for linie in f:
            ls = [int(x) for x in linie.split()]
            matrice.append(ls)
    return matrice

"""
din fiecare sublistă se vor elimina toate aparițiile valorii minime
 
din fiecare sublistă se vor păstra doar primele m elemente, unde m reprezintă lungimea 
minimă a unei subliste
"""

def prelucrare_lista(lista):
    lung_min=len(lista[0])
    for subls in lista: #lista = lista de liste, subls = o sublista
        #determinam minimul din subls
        x=min(subls)
        #stergem minimul din subls - toate aparitiile (cum am sters si toate 0-urile din lista)
        while x in subls:
            subls.remove(x)
            #tema - cu index
        if len(subls)<lung_min:
            lung_min=len(subls)
    #lung_min=min([len(subls) for subls in lista])
    #print(lung_min)
    for subls in lista:
        #pastram din subls doar primele lung_min elemente - de la 0 la lung_min-1:
        #subls= NU
        #subls[:]= DA
        del subls[lung_min:]
        #subls[lung_min:]=[]

#c)
mat=citire_numere("numere.in")
#print(mat)
prelucrare_lista(mat)
#print(mat)
for linie in mat:
    #var 1- print(*linie)
    for x in linie:
        print(x,end=" ")
    print()

#d)
mat=citire_numere("numere.in")
k=int(input())
g=open("cifre.out","w")
#numerele cu k cifre descrescator, fara duplicate
set_k=set()
for linie in mat:
    for x in linie:
        #if (10**(k-1))<=x<(10**k):
        if len(str(x))==k:
            set_k.add(x)
print(set_k)
#var-cu compreh
set_k={x for linie in mat for x in linie if len(str(x))==k}
print(set_k)
set_K_sortat=sorted(set_k,reverse=True)
for x in set_K_sortat:
    g.write(f"{x} ") #g.write(str(x)+" ")
#g.writelines([str(x)+" " for x in sorted(set_k,reverse=True)])
g.write("\n")
g.write(",".join([str(x) for x in sorted(set_k,reverse=True)]))
g.close()