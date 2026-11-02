#varianta cu split
propozitie="mar mar mare mare amar mar   mar mar"
s="mar"
t="para"
ls=propozitie.split(" ")
for i in range(len(ls)):
    if ls[i] == s:
        ls[i] = t
propozitie=" ".join(ls)
print(propozitie)

#varianta cu replace
propozitie="mar mar mare mare amar mar mar mar"
s="mar"
t="para"
rezultat=" "+propozitie+" "
rezultat=rezultat.replace(" "+s+" "," "+t+" ") #!!!probleme cu aparitii consecutive
rezultat=rezultat.replace(" "+s+" "," "+t+" ")
propozitie = rezultat[1:-1]
print(propozitie)