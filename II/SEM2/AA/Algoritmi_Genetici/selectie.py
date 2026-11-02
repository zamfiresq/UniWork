# Algoritmul de selectie - Algoritmi Genetici

import math
import random

# citim de la tastatura coeficientii polinomului
a, b, c = map(int, input("").split())
n = int(input("")) # populatia cromozomilor
valori_decodificate = list(map(float, input("").split()))

# functia fitness va fi functia polinomiala
def f(a, b, c, x):
    return a * x ** 2 + b * x + c

def subintervale_selectie():
    # determinam valorile de fitness pentru fiecare individ
    for i in range(n):
        valori_decodificate[i] = f(a, b, c, valori_decodificate[i])
        
    # determinam suma valorilor de fitness
    suma = sum(valori_decodificate)

    # calculam sumele partiale ale fitness-urilor si le impartim la suma valorilor
    # pentru a obtine capetele intervalelor de selectie
    intervale_selectie = []

    suma_partiala = 0
    for i in range(n):
        intervale_selectie.append(suma_partiala / suma)
        suma_partiala += valori_decodificate[i]
        
    intervale_selectie.append(suma_partiala / suma)

    for interval in intervale_selectie:
        print(round(interval, 6))

subintervale_selectie()



