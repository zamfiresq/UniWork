print("frozenset de litere")
nume_fisier=input()
f = open(nume_fisier)
d = {}  #multime litere:lista de cuvinte cu acele litere
for linie in f:
  ls_cuvinte = linie.split()
  for cuv in ls_cuvinte:  #fiecare cuvant
    litere_cuv = frozenset(cuv)
    if litere_cuv in d:
      d[litere_cuv].append(cuv)
    else:
      d[litere_cuv] = [cuv]  #lista cu un element
f.close()
def cheie_lungime(elem):
  return len(elem)

chei_sortate = sorted(d,key=cheie_lungime,reverse=True)

print(chei_sortate)

for mult_litere in chei_sortate: 
  d[mult_litere].sort(key=len)
  if len(d[mult_litere])>1:
      print(" ".join(d[mult_litere]))
