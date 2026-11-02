# punct in poligon convex 

# calculare determinant
def determinant(p, q, r):
    rezultat = q[0] * r[1] + p[0] * q[1] + p[1] * r[0] - p[0] * r[1] - q[1] * r[0] - p[1] * q[0]
    if rezultat > 0: # viraj la stanga
        return 1
    elif rezultat < 0: # viraj la dreapta
        return -1
    else:
        return 0 # coliniare
    
# sortam punctele in functie de x si y
def comparare(p):
    return (p[0], p[1])

# citire date de intrare
n = int(input())

poligon = []

# citire puncte
for i in range(n):
    x, y = map(int, input().split())
    poligon.append((x, y))

# citim puncte pentru verificarea pozitiei lor fata de poligon
m = int(input())

puncte_de_verificat = []

for j in range(m):
    x, y = map(int, input().split())
    puncte_de_verificat.append((x, y, j)) # punctele cu indicele asociat

# frontiere
frontiera_superioara = []
frontiera_inferioara = []
pozitii = [-1] * m # lista de pozitii

index_stg = index_dr = 0

# cautam punctele cu x minim si x maxim pentru determinarea punctului de pornire
for i in range(n):
    if index_stg == -1 or poligon[i][0] < poligon[index_stg][0]: # daca x din varful curent este mai mic decat x din varful stanga
        index_stg = i
    if index_dr == -1 or poligon[i][0] > poligon[index_dr][0]:
        index_dr = i

# construim frontiera inferioara
i = index_stg
while True:
    frontiera_inferioara.append(poligon[i])
    i = (i + 1) % n
    if i == (index_dr + 1) % n:
        break

# construim frontiera superioara
i = index_stg
while True:
    frontiera_superioara.append(poligon[i])
    i = (i - 1 + n) % n
    if i == (index_dr - 1 + n) % n:
        break

# sortare puncte de verificare
puncte_de_verificat.sort(key = comparare)

# dimensiune frontiera inferioara si superioara
lung_inf = len(frontiera_inferioara)
lung_sup = len(frontiera_superioara)
 
minim_x = frontiera_inferioara[0][0]
maxim_x = frontiera_inferioara[-1][0]

# indici de parcurgere pentru frontiere
index_inf = index_sup = index = 0

# verificam daca poligonul este in interior, exterior sau pe frontiera
# exterior
while index < m and puncte_de_verificat[index][0] < minim_x:
    pozitii[puncte_de_verificat[index][2]] = -1
    index += 1

minim_y = maxim_y = frontiera_inferioara[0][1]

while index_inf < lung_inf and frontiera_inferioara[index_inf][0] == minim_x:
    minim_y = min(minim_y, frontiera_inferioara[index_inf][1])
    index_inf += 1

while index_sup < lung_sup and frontiera_superioara[index_sup][0] == minim_x:
    maxim_y = max(maxim_y, frontiera_superioara[index_sup][1])
    index_sup += 1

while index < m and puncte_de_verificat[index][0] == minim_x:
    if minim_y <= puncte_de_verificat[index][1] <= maxim_y:
        pozitii[puncte_de_verificat[index][2]] = 0
    else:
        pozitii[puncte_de_verificat[index][2]] = -1
    index += 1

# intermediar
while index < m and puncte_de_verificat[index][0] < maxim_x:
    while index_inf < lung_inf and frontiera_inferioara[index_inf][0] <= puncte_de_verificat[index][0]:
        index_inf += 1
    index_inf -= 1

    while index_sup < lung_sup and frontiera_superioara[index_sup][0] <= puncte_de_verificat[index][0]:
        index_sup += 1
    index_sup -= 1

    # determinam orientarea punctelor de verificare fata de frontiere
    orientare_inf = determinant(frontiera_inferioara[index_inf], frontiera_inferioara[index_inf + 1], puncte_de_verificat[index])
    orientare_sup = determinant(frontiera_superioara[index_sup], frontiera_superioara[index_sup + 1], puncte_de_verificat[index])

    if orientare_inf == -1 or orientare_sup == 1:
        pozitii[puncte_de_verificat[index][2]] = -1
    elif orientare_inf == 0 or orientare_sup == 0:
        pozitii[puncte_de_verificat[index][2]] = 0
    else:
        pozitii[puncte_de_verificat[index][2]] = 1

    index += 1

# verificarea punctelor aflate la marginea poligonului
minim_y = maxim_y = frontiera_inferioara[-1][1] 

index_inf = lung_inf - 1
index_sup = lung_sup - 1

while index_inf >= 0 and frontiera_inferioara[index_inf][0] == maxim_x:
    minim_y = min(minim_y, frontiera_inferioara[index_inf][1])
    index_inf -= 1

while index_sup >= 0 and frontiera_superioara[index_sup][0] == maxim_x:
    maxim_y = max(maxim_y, frontiera_superioara[index_sup][1])
    index_sup -= 1

while index < m and puncte_de_verificat[index][0] == maxim_x:
    if minim_y <= puncte_de_verificat[index][1] <= maxim_y:
        pozitii[puncte_de_verificat[index][2]] = 0
    else:
        pozitii[puncte_de_verificat[index][2]] = -1
    index += 1

while index < m:
    pozitii[puncte_de_verificat[index][2]] = -1
    index += 1



# afisam rezultatele
for rez in pozitii:
    if rez == -1:
        print("OUTSIDE")
    elif rez == 0:
        print("BOUNDARY")
    else:
        print("INSIDE")
