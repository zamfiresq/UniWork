limita_stanga = []
limita_dreapta = []
limita_jos = []
limita_sus = []

def intersectie(a, b, c, pozitiv):
    global limita_stanga, limita_dreapta, limita_jos, limita_sus
    limita_intersectie = 0.0 # limita de intersectie
    pozitiv = True

    # pentru by + c <= 0
    if a == 0:
        if b < 0:
            pozitiv = False
        limita_intersectie = float(-c) / b
        if pozitiv:
            limita_sus.append(limita_intersectie)
        else:
            limita_jos.append(limita_intersectie)
    else:  #pentru ax + c <= 0
        if a < 0:
            pozitiv = False
        limita_intersectie = float(-c) / a
        if pozitiv:
            limita_dreapta.append(limita_intersectie)
        else:
            limita_stanga.append(limita_intersectie)


# functie care returneaza indexul celui mai mare element din lista mai mic decat elementul dat
# cautare binara
def mai_mic_mai_mare(smaller_lim, element):
    if not smaller_lim or element < smaller_lim[0]:
        return -1
    for i in range(len(smaller_lim) - 1, -1, -1):
        if element > smaller_lim[i]:
            return i
    return -1

def mai_mare_mai_mic(bigger_lim, element):
    if not bigger_lim or element > bigger_lim[-1]:
        return -1
    for i in range(len(bigger_lim)):
        if element < bigger_lim[i]:
            return i
    return -1

n = int(input())
for i in range(n):
    a, b, c = map(int, input().split())
    intersectie(a, b, c, True)

m = int(input())

# sortam listele
limita_stanga.sort()
limita_dreapta.sort()
limita_jos.sort()
limita_sus.sort()

for i in range(m):
    x, y = map(float, input().split())

    limita_stanga_index = mai_mic_mai_mare(limita_stanga, x)
    limita_dreapta_index = mai_mare_mai_mic(limita_dreapta, x)
    limita_jos_index = mai_mic_mai_mare(limita_jos, y)
    limita_sus_index = mai_mare_mai_mic(limita_sus, y)

# daca nu exista nicio intersectie
    if limita_stanga_index == -1 or limita_dreapta_index == -1 or limita_jos_index == -1 or limita_sus_index == -1:
        print("NO")
    else:
        arie = (limita_dreapta[limita_dreapta_index] - limita_stanga[limita_stanga_index]) * (limita_sus[limita_sus_index] - limita_jos[limita_jos_index])
        print("YES")
        print("{:.6f}".format(arie))
