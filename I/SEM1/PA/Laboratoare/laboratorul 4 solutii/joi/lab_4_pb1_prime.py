print("p-rime")
p = int(input("p="))
f = open("rime.in")
d = {}  #sufix:lista de cuvinte cu acel sufix
for linie in f:
  ls_cuvinte = linie.split()
  for cuv in ls_cuvinte:  #fiecare cuvant
    suf_cuv = cuv[-p:]
    if suf_cuv in d:
      d[suf_cuv].append(cuv)
    else:
      d[suf_cuv] = [cuv]  #lista cu un element
f.close()
print(d)
print(d.items())
grupuri = list(d.items())  #perechi (sufix, lista de cuvinte)
"""
parametru- un element si returneaza dupa ce cheie facem comparatia - in acest caz lungimea listei
elem[0] este sufixul, elem[1] este lista
"""


def comparator_lung(elem):
  return len(elem[1])


grupuri.sort(key=comparator_lung, reverse=True)
print(grupuri)

for sufix, lista_cuv in grupuri:
  lista_cuv.sort(reverse=True)
  print(*lista_cuv)
  
g = open("rime.out", "w")
for sufix, lista_cuv in grupuri:
  lista_cuv.sort(reverse=True)
  g.write(" ".join(lista_cuv))  #doar sit de caracter
  g.write("\n")
g.close()
