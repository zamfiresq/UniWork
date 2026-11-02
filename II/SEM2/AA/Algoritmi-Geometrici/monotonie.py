# monotonia unui poligon

# functie pentru determinarea numarului de schimbari de directie pentru coordonatele punctelor pe o axa
def nr_schimbari_dir(n, maxim, axa, puncte):
    schimbari_totale = 0
    index = 0
    directie_curenta = 0
    for i in range(maxim, n + maxim): 
        index = i % n
        if axa == 'x': # axa Ox
            if puncte[index][0] < puncte[(index + 1) % n][0]: # cazul pentru x-crescator
                if directie_curenta == 0: 
                    directie_curenta = 1
                elif directie_curenta == -1:  # schimbare de directie
                    directie_curenta = 1
                    schimbari_totale += 1

            elif puncte[index][0] > puncte[(index + 1) % n][0]: # cazul pentru x-descrescator
                if directie_curenta == 0:
                    directie_curenta = -1
                elif directie_curenta == 1:
                    directie_curenta = -1
                    schimbari_totale += 1

        elif axa == 'y': # axa Oy
            if puncte[index][1] < puncte[(index + 1) % n][1]: # cazul pentru y-crescator
                if directie_curenta == 0:
                    directie_curenta = 1
                elif directie_curenta == -1:
                    directie_curenta = 1
                    schimbari_totale += 1

            elif puncte[index][1] > puncte[(index + 1) % n][1]: # cazul pentru y-descrescator
                if directie_curenta == 0:
                    directie_curenta = -1
                elif directie_curenta == 1:
                    directie_curenta = -1
                    schimbari_totale += 1
        else:
            print("Axa de coordonate invalida!")
            return 0
    return schimbari_totale

# citire date
n = int(input())
puncte = [] # lista de puncte

max_x, max_y = float('-inf'), float('-inf') 
x_maxim = y_maxim = 0 

# citire puncte
for i in range(n):
    x, y = map(int, input().split())
    puncte.append((x, y))

    # actualizare maxim x si y
    if x > max_x: 
        max_x = x
        x_maxim = i

    if y > max_y:
        max_y = y
        y_maxim = i

nr_schimbari_x = nr_schimbari_dir(n, x_maxim, 'x', puncte)
nr_schimbari_y = nr_schimbari_dir(n, y_maxim, 'y', puncte)

# daca numarul de schimbari este mai mare de 2, atunci poligonul nu este monoton
print("NO" if nr_schimbari_x > 2 else "YES")
print("NO" if nr_schimbari_y > 2 else "YES")