# pozitia unui punct fata de un poligon

# functie pentru determinarea orientarii
def orientare(p, q, r):
    rez = q[0] * r[1] + p[0] * q[1] + p[1] * r[0] - p[0] * r[1] - q[1] * r[0] - p[1] * q[0]
    if rez > 0:
        return 1  # r este la stanga
    elif rez < 0:
        return -1  # r este la dreapta 
    else:
        return 0  # coliniar

# determinarea pozitiei unui punct fata de un poligon
def pozitie_punct(punct, poligon):
    n = len(poligon)
    muchii_stanga = 0
    muchii_dreapta = 0

    for i in range(n):
        p1 = poligon[i]
        p2 = poligon[(i + 1) % n]

        if p1[1] > p2[1] or (p1[1] == p2[1] and p1[0] > p2[0]):
            p1, p2 = p2, p1  # schimbam ordinea punctelor 

        if punct[1] < p1[1] or punct[1] > p2[1]:
            continue  # ignoram muchia daca punctul este in afara ei

        if p1[0] == p2[0]:
            if punct[1] == p1[1]:
                return 0  # punctul este pe muchie
            elif punct[0] < p1[0]:
                muchii_dreapta += 1 
            elif punct[0] > p1[0]:
                muchii_stanga += 1
        elif p1[1] == p2[1]:
            if punct[0] >= p1[0] and punct[0] <= p2[0]:
                return 0  # punctul este pe muchie
        else:
            rez = orientare(p1, p2, punct)
            if rez == 0:
                return 0  
            if punct[1] == p1[1]:
                continue 
            if rez == -1:
                muchii_stanga += 1
            else:
                muchii_dreapta += 1

    if muchii_stanga % 2 == 1 and muchii_dreapta % 2 == 1:
        return 1  # punctul este in interior
    return -1  # se afla la exterior


poligon = [] # lista de puncte ce reprezinta poligonul

# citim datele de intrare
# coordonatele varfurilor poligonului
n = int(input()) 
for i in range(n):
    x, y = map(int, input().split())
    poligon.append((x, y)) # adaugam punctul in lista

# coordonatele punctului q
m = int(input())
rezultate = [] # lista cu rezultatele
for i in range(m):
    x, y = map(int, input().split())
    punct = (x, y)
    poz = pozitie_punct(punct, poligon)

    if poz == 0:
        rezultate.append("BOUNDARY")
    elif poz == 1:
        rezultate.append("INSIDE")
    else:
        rezultate.append("OUTSIDE")

for rez in rezultate:
    print(rez)

