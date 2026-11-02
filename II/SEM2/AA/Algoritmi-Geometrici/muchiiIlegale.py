# muchii ilegale

# ne vom folosi de criteriul numeric pentru a determina daca un punct este in interiorul unui cerc circumscris triunghiului
# daca punctul e in interiorul cercului, atunci muchia triunghiului este ilegala
# daca punctul e in exteriorul cercului, atunci muchia triunghiului este legala

def det3x3(matrice):
    return (matrice[0][0] * (matrice[1][1] * matrice[2][2] - matrice[1][2] * matrice[2][1])
            - matrice[0][1] * (matrice[1][0] * matrice[2][2] - matrice[1][2] * matrice[2][0])
            + matrice[0][2] * (matrice[1][0] * matrice[2][1] - matrice[1][1] * matrice[2][0]))

def det4x4(matrice):
    determinant = 0
    for i in range(4):
        matrice_temp = [] # matricea 3x3 obtinuta prin eliminarea liniei 0 si coloanei i
        for j in range(1, 4):
            linie = []
            for k in range(4):
                if k != i:
                    linie.append(matrice[j][k])
            matrice_temp.append(linie)
        determinant3x3 = det3x3(matrice_temp)
        if i % 2 == 0: # daca i este par adunam, altfel scadem
            determinant += matrice[0][i] * determinant3x3
        else:
            determinant -= matrice[0][i] * determinant3x3
    return determinant

def determinant_final(ax, ay, bx, by, cx, cy, dx, dy):
    # determinantul pentru a stabili daca muchia AC este legala sau ilegala
    matrice_ac = [[ax, ay, ax**2 + ay**2, 1],
                    [cx, cy, cx**2 + cy**2, 1],
                    [dx, dy, dx**2 + dy**2, 1],
                    [bx, by, bx**2 + by**2, 1]]
    
    det_ac = det4x4(matrice_ac)
    if det_ac > 0:
        print("AC: ILLEGAL")
    else:
        print("AC: LEGAL")

    # determinantul pentru a stabili daca muchia BD este legala sau ilegala
    matrice_bd = [[bx, by, bx**2 + by**2, 1],
                    [cx, cy, cx**2 + cy**2, 1],
                    [dx, dy, dx**2 + dy**2, 1],
                    [ax, ay, ax**2 + ay**2, 1]]
    
    det_bd = det4x4(matrice_bd)
    if det_bd > 0:
        print("BD: ILLEGAL")
    else:
        print("BD: LEGAL")

# citire date de intrare
ax, ay = map(int, input().split())
bx, by = map(int, input().split())
cx, cy = map(int, input().split())
dx, dy = map(int, input().split())

determinant_final(ax, ay, bx, by, cx, cy, dx, dy)