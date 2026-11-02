# Tema laborator AA - Algoritmi Genetici

import math
import random
import copy

# date de intrare puse intr-un fisier de intrare
f = open("/Users/alexandrazamfirescu/Desktop/date_intrare.txt", "r")

n = int(f.readline())
a, b = map(int, f.readline().split())
a1, b1, c1 = map(int, f.readline().split())
p = int(f.readline())
pc = float(f.readline())
pm = float(f.readline())
nr_etape = int(f.readline())
lista_max = []
lista_medie = []

for i in range(nr_etape):
    lista_max.append(float("-inf"))
    lista_medie.append(0)

f.close()

# afisare in fisier 
g = open("/Users/alexandrazamfirescu/Desktop/evolutie.txt", "w")


# functia pe care vrem sa o maximizam este functia fitness
# functie polinomiala
def f(a1, b1, c1, x):
    return a1 * x ** 2 + b1 * x + c1


# creez individul - structura
class Individ:
    def __init__(self, cromozom, fitness, x):
        self.cromozom = cromozom
        self.fitness = fitness # f
        self.x = x 
        #g.write(type(cromozom))

        
# numarul de biti necesari pentru a reprezenta un numar in binar
lungime_individ = math.ceil(math.log2((b - a) * (10 ** p))) 

# translatie liniara (valoarea lui x codificata din domeniu)
def translatie_liniara(cromozom):
    x_binar_zecimal = int("".join(str(bit) for bit in cromozom), 2) # transform x din binar in zecimal
    x = x_binar_zecimal * (b - a) / (2 ** lungime_individ - 1) + a # formula de la curs 
    return round(x, p)

# ---------------------------------------------------------------------------------------------------------------

######## ETAPE ALGORITM GENETIC ########

#maxim_global = float("-inf")
for etapa in range(nr_etape): # 50
    # PRIMA ETAPA 

    # POPULATIA INITIALA
    def populatie_initiala():
        if(etapa == 0):
            g.write("\nPopulatia initiala:\n") 
        populatie_initiala = []

        for i in range(n):
            cromozom = random.choices([0, 1], k=lungime_individ)
            x = translatie_liniara(cromozom)
            fitness = f(a1, b1, c1, x)
            individ = Individ(cromozom, fitness, x)
            populatie_initiala.append(individ)

            # transform cromozomul in string
            cromozom_str = "".join(str(bit) for bit in cromozom)
            if(etapa == 0):
                if(i < 9):
                    g.write(f" {i + 1}. {cromozom_str}, x= {x}, f= {str(fitness)}\n")
                else:
                    g.write(f"{i + 1}. {cromozom_str}, x= {x}, f= {str(fitness)}\n")

        return populatie_initiala


    # # SELECTIE
    def selectie(populatie):
        populatia_noua = [] # populatia P(t+1) pe baza P(t)

        # calculam intai probabilitatea de selectie pentru fiecare individ
        if etapa == 0:
            g.write("\n\nProbabilitate selectie\n")
            sumaFitness = sum(individ.fitness for individ in populatie)
            for i in range(n):
                probabilitate_selectie = populatie[i].fitness / sumaFitness
                
                if (etapa == 0):
                    if(i < 9):
                        g.write(f"cromozom    {i + 1} probabilitate {str(probabilitate_selectie)}\n")
                    else:
                        g.write(f"cromozom   {i + 1} probabilitate {str(probabilitate_selectie)}\n")


            # calcularea intervalelor de selectie
            intervale_selectie = []
            suma_partiala = 0 
            for individ in populatie:
                intervale_selectie.append(suma_partiala / sumaFitness)
                suma_partiala += individ.fitness


            if(etapa == 0):
                g.write("\n\nIntervale probabilitati selectie\n") # afisare intervale
                subliste = [intervale_selectie[i:i + 5] for i in range(0, len(intervale_selectie), 5)] 
                for sublista in subliste:
                    interval_str = " ".join([str(interval) for interval in sublista])
                    g.write(interval_str + "\n")
            
            # va trebui sa generam un u aleator pe [0, 1) pentru a determina intervalul din care face parte
            for i in range(n):
                u = random.random()

                # cautarea binara a gasi intervalul din care face parte u
                dreapta = n - 1
                stanga = 0
                mijloc = (stanga + dreapta) // 2

                while(stanga < dreapta):
                    if intervale_selectie[mijloc] < u:
                        stanga = mijloc + 1
                    else:
                        dreapta = mijloc - 1
                    mijloc = (stanga + dreapta) // 2

                if(etapa == 0):
                    g.write(f"u = {u} selectam cromozomul {stanga + 1}\n")

                # adaugam cromozomul selectat in populatia noua
                populatia_noua.append(populatie[stanga])

            populatie = copy.deepcopy(populatia_noua) 


        # dupa selectie
        if(etapa == 0):
            g.write("\n\nDupa selectie:\n")
            for i in range(n):
                cromozom_str = "".join(str(bit) for bit in populatia_noua[i].cromozom)
                if(i < 9):
                    g.write(f" {i + 1}. {cromozom_str}, x= {str(round(populatia_noua[i].x, p))}, f= {str(round(populatia_noua[i].fitness, p))}\n")
                else:
                    g.write(f"{i + 1}. {cromozom_str}, x= {str(round(populatia_noua[i].x, p))}, f= {str(round(populatia_noua[i].fitness, p))}\n")


        return populatia_noua       

       # CROSSOVER - cu un punct de rupere
    def crossover(populatie):
        incrucisari = []
        index_cross = []

        if etapa == 0:
            g.write(f"\n\nProbabilitatea de incrucisare {str(pc)}\n")

        # generam u aleator pe [0, 1) pentru a determina daca se face crossover in functie de pc
        for i in range(n):
            u = random.random()

            # verificam daca cromozomul participa la crossover
            if u < pc:
                cromozom_str = "".join([str(bit) for bit in populatie[i].cromozom])
                g.write(f"{i + 1}:  {cromozom_str}  u= {str(u)} < {str(pc)} participa\n")
                incrucisari.append(populatie[i]) 
                index_cross.append(i)
            else:
                cromozom_str = "".join([str(bit) for bit in populatie[i].cromozom])
                g.write(f"{i + 1}:  {cromozom_str}  u= {str(u)}\n")
            
        # daca avem numar impar de cromozomi care participa la crossover, eliminam ultimul cromozom
        if len(incrucisari) % 2 == 1:
            incrucisari.pop()
            index_cross.pop()

        # facem crossover intre cromozomii care participa
        for i in range(len(incrucisari) // 2):
            punct_rupere_1 = random.randint(1, lungime_individ - 2)  
            punct_rupere_2 = random.randint(punct_rupere_1 + 1, lungime_individ - 1)  # al doilea punct de rupere


            print("Punctele de rupere alese:", punct_rupere_1, punct_rupere_2)


            # cromozomii inainte de primul punct de rupere 
            c1 = incrucisari[i].cromozom[:punct_rupere_1] + incrucisari[i + len(incrucisari) // 2].cromozom[punct_rupere_1:punct_rupere_2] + incrucisari[i].cromozom[punct_rupere_2:] # cromozom 1
            c2 = incrucisari[i + len(incrucisari) // 2].cromozom[:punct_rupere_1] + incrucisari[i].cromozom[punct_rupere_1:punct_rupere_2] + incrucisari[i + len(incrucisari) // 2].cromozom[punct_rupere_2:] # cromozom 2
            
            print(f"Portiune: {incrucisari[i + len(incrucisari) // 2].cromozom[punct_rupere_1:punct_rupere_2]}")
            

            # ----------------------------------
            # # inlocuire sectiuni
            # c2_final = c2[:punct_rupere_1] + c1[punct_rupere_1:punct_rupere_2] + c2_final[punct_rupere_2:]

            # #print(c1_final)
            # print(c2_final)

            if etapa == 0:
                cromozom1_str = "".join([str(bit) for bit in incrucisari[i].cromozom]) 
                cromozom2_str = "".join([str(bit) for bit in incrucisari[i + len(incrucisari) // 2].cromozom])
                

                if etapa == 0:
                    g.write(f"\nRecombinare dintre cromozomul {index_cross[i] + 1} cu cromozomul {index_cross[i + len(incrucisari) // 2] + 1}:\n")
                    g.write(f"{cromozom1_str} {cromozom2_str} puncte {str(punct_rupere_1)} si {str(punct_rupere_2)}\nRezultat: ")
                    g.write("".join([str(bit) for bit in c1]) + " " + "".join([str(bit) for bit in c2]) + "\n")


            # actualizare populatie dupa crossover
            populatie[index_cross[i]].cromozom = c1
            populatie[index_cross[i + len(incrucisari) // 2]].cromozom = c2



        # dupa recombinare
        if etapa == 0:
            g.write("\nDupa recombinare:\n")
            for index, individ in enumerate(populatie):
                cromozom_str = "".join([str(bit) for bit in individ.cromozom])

                if(index < 9):
                    g.write(f" {index + 1}:  {cromozom_str}, x= {str(round(individ.x, p))}, f= {str(round(individ.fitness, p))}\n")
                else:
                    g.write(f"{index + 1}:  {cromozom_str}, x= {str(round(individ.x, p))}, f= {str(round(individ.fitness, p))}\n")

        return populatie




        # MUTATIE
    def mutatie(populatie):
        if etapa == 0:
            g.write(f"\n\nProbabilitatea de mutatie pentru fiecare gena {str(pm)}\n")
            g.write("Au fost modificati cromozomii:\n")

        for i in range(n):
            u = random.random()
            if u < pm:
                pozitie = random.randint(0, lungime_individ - 1) # pozitia aleatorie pentru mutatie
                populatie[i].cromozom[pozitie] = 1 - populatie[i].cromozom[pozitie] 
                if etapa == 0:
                    g.write(f"{i + 1}\n")
                
        # dupa mutatie
        if etapa == 0:
            g.write("\nDupa mutatie:\n")

            for index, individ in enumerate(populatie):
                cromozom_str = "".join([str(bit) for bit in individ.cromozom])

                if(etapa == 0):
                    if(index < 9):
                        g.write(f" {index + 1}:  {cromozom_str}, x= {str(round(individ.x, p))}, f= {str(round(individ.fitness, p))}\n")
                    else:
                        g.write(f"{index + 1}:  {cromozom_str}, x= {str(round(individ.x, p))}, f= {str(round(individ.fitness, p))}\n")
    

        return populatie
        
    populatie = populatie_initiala() # 20 de indivizi
    if etapa == 0:
        populatie = selectie(populatie)
        populatie = crossover(populatie)    
        populatie = mutatie(populatie)

    medie_locala = 0.0 
    for index in range(len(populatie)): # parcurgem fiecare individ
        if populatie[index].fitness > lista_max[etapa]:
            lista_max[etapa] = populatie[index].fitness
        medie_locala += populatie[index].fitness
    lista_medie[etapa] = medie_locala / n

    # EVOLUTIA MAXIMA + VALOAREA MEDIE
    if etapa == 0:
        g.write("\n\nEvolutia maximului si a valorii medii a functiei fitness\n")
        g.write("Etapa      Maxim        Medie\n")

    maxim = lista_max[etapa]
    medie = lista_medie[etapa]

    if etapa < 9:
        g.write(f" {etapa + 1}        {str(round(maxim, p))}     {str(round(medie, p))}\n")
    else:
        g.write(f"{etapa + 1}        {str(round(maxim, p))}     {str(round(medie, p))}\n")

    
g.close()