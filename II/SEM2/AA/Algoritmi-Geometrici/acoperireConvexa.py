# acoperire convexa a unui poligon stelat
# complexitate O(n)
# calculare determinant pentru 3 puncte
def calculare_determinant(x1, y1, x2, y2, x3, y3):
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) > 0 # modificare determinant

# >0 => viraj la stanga
# <0 => viraj la dreapta
# =0 => coliniare

n = int(input()) # citim n

puncte = []
ls = [] # frontiera superioara
li = [] # frontiera inferioara
l = []  # frontiera finala

# citim punctele
for i in range(n):
    x, y = map(int, input().split())
    puncte.append((x, y))

puncte.sort() # sortare dupa x

# graham scan

# primele 2 puncte din frontiera inferioara
li.append(puncte[0])
li.append(puncte[1])

# calculare frontiera inferioara
for i in range(2, n): 
    li.append(puncte[i])
    while len(li) > 2 and not calculare_determinant(li[-3][0], li[-3][1], li[-2][0], li[-2][1], li[-1][0], li[-1][1]):
        li.pop(-2) # eliminam penultimul element, pentru a mentine virajul la stanga

# primele 2 puncte din frontiera superioara
ls.append(puncte[n - 1])
ls.append(puncte[n - 2])

# calculare frontiera superioara
for i in range(n - 3, -1, -1): 
    ls.append(puncte[i])
    while len(ls) > 2 and not calculare_determinant(ls[-3][0], ls[-3][1], ls[-2][0], ls[-2][1], ls[-1][0], ls[-1][1]): # nu determina virajul la stanga
        ls.pop(-2)

# eliminam primul si ultimul element din frontiera superioara pentru a evita duplicarea punctelor
ls.pop(0)
ls.pop(-1)

# construire frontiera finala
l = li + ls

# afișare frontiera finala + coordonatele punctelor
print(len(l))
for punct in l:
    print(punct[0], punct[1])
