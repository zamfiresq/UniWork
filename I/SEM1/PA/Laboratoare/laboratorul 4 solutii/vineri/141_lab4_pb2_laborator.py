f=open("studenti.in")
d={}
for linie in f:
    ls=linie.split(", ")
    #print(ls)
    nume_complet=ls[0]+ " "+ls[1]
    grupa=int(ls[2])
    ls[-1].strip("\n")
    note=[int(x) for x in ls[3:]]
    #print(note)
    if grupa in d:
        d[grupa][nume_complet]=note
    else:
        d[grupa]={nume_complet:note} #d[sufix_cuv]=[cuv]

f.close()
print(d)
print(d[191]["Marin Ioana"])
for grupa in d: #dupa chei
#for grupa in sorted(d):
    print(grupa)
    print(*sorted(d[grupa].keys()),sep="\n")
    """
    for nume_complet in d[grupa]:
        print(nume_complet,*d[grupa][nume_complet])
    """
print("b)")
grupa=191
#d[grupa]
for nume in d[grupa]:
    ls_note=d[grupa][nume]
    if len(ls_note)==5 and min(ls_note)>=5:
        md=sum(ls_note)/len(ls_note)
        print(f"{nume} media {md:.2f}")
    else:
        print(f"{nume} restantier")
