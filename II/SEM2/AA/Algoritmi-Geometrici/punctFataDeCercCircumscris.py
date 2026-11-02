# pozitia unui punct fata de cercul circumscris unui triunghi

# criteriul numeric
# pentru calcularea determinantului unei matrice 4x4, vom calcula intai determinantul matricei 3x3 
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

def determinant_final(ax, ay, bx, by, cx, cy, px, py):
    matrice = [[ax, ay, ax**2 + ay**2, 1],
               [bx, by, bx**2 + by**2, 1],
               [cx, cy, cx**2 + cy**2, 1],
               [px, py, px**2 + py**2, 1]]
    return det4x4(matrice)

    
# citire date de intrare
# coordonate triunghiului ABC
ax, ay = map(int, input().split())
bx, by = map(int, input().split())
cx, cy = map(int, input().split())

# coordonatele punctului P
m = int(input())
puncte = [] 
for i in range(m):
    x, y = map(int, input().split())
    puncte.append((x, y))

# calculul pozitiei punctului fata de cercul circumscris
for punct in puncte:
    rezultat = determinant_final(ax, ay, bx, by, cx, cy, punct[0], punct[1])
    if rezultat > 0:
        print("INSIDE")  # punctul este in interiorul cercului circumscris
    elif rezultat < 0:
        print("OUTSIDE")  # punctul este in exteriorul cercului circumsris
    else:
        print("BOUNDARY")  # punctul este pe cercul circumscris