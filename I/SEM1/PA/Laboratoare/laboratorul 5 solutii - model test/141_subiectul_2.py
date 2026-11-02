d={}
#ls=[]
with open("cinema.in") as f:
    for linie in f:
        ls=linie.split(" % ")
        cinema=ls[0]
        film=ls[1]
        #sir_ore=ls[2]
        lista_ore=set(ls[2].split())#mergea si lasat list
        print(cinema,film,lista_ore)
        if cinema in d:
            d[cinema][film]=lista_ore
        else:
            d[cinema]={film:lista_ore}
        #ls.append((cinema,film,lista_ore))
        """
        if cinema not in d:
            d[cinema]={}
        d[cinema][film]=lista_ore
        """

print(d)

def sterge_ore(d,cinema,film,ore):
    rez=[]
    if (cinema in d) and (film in d[cinema]):
        #stergem ore din d[cinema][film]
        """
        for x in ore:
            d[cinema][film].discard(x)
        """
        d[cinema][film].difference_update(ore)
        print(d[cinema][film])
        if len(d[cinema][film])==0: #daca filmul nu mai este programat la late ore -stergem asocierea cinema-film
            del d[cinema][film]
            if len(d[cinema])==0:
                del d[cinema]
                return []

        #print(d[cinema])
        print(d[cinema].keys())
        #print(d[cinema].values())
        #print(d.values())
        return list(d[cinema].keys())
    return []

print(d)
filme=sterge_ore(d,"Cinema 1","Minionii 2",{"12:30","19:00"})
#filme=sterge_ore(d,input("cinema: "),input("film: "),{input("ora: ")})
print(d)
print(filme)
def cheie(x):
    #primul criteriu - crescator dupa film = x[0]
    #al doilea criteriu - descresc dupa nr de ore len(x[2]
    return x[0], -len(x[2])
def cinema_film(d,*cinematografe,ora_minima, ora_maxima):
    #(film,cinema,lista_ore) cu cinema  in cinematograle si ore in intervalul [ora_minima, ora_maxima]
    rez=[]
    for cinema in cinematografe:
        if cinema in d:
            #d[cinema]
            for film in d[cinema]:
                #tb sa alegem din d[cinema][film] doar orele din intervalul [ora_minima, ora_maxima]
                #ore_interval=[ora for ora in d[cinema][film] if ora_minima <= ora<= ora_maxima]
                ore_interval=[]
                for ora in d[cinema][film]:
                    if ora_minima <= ora<= ora_maxima:
                        ore_interval.append(ora)
                if len(ore_interval)>0:
                    ore_interval.sort()
                    rez.append((film,cinema,ore_interval))
    rez.sort(key=cheie)
    #rez.sort(key=lambda x:(x[0],-len(x[2])))
    return rez

ls=cinema_film(d,"Cinema 1", "Cinema 2",ora_minima="14:00",ora_maxima="22:00")
print(ls)