f=open("studenti.in")
d={}
for linie in f:
  ls=linie.split(", ")
  nume=ls[0]
  prenume=ls[1]
  nume_complet=nume+" "+prenume
  grupa=int(ls[2])
  ls_note=[int(x) for x in ls[3:]]
  print(nume,prenume,grupa,ls_note)  
  if grupa in d:
    d[grupa][nume_complet]=ls_note
  else:
    d[grupa]={}
    d[grupa][nume_complet]=ls_note
    #d[grupa]={nume_complet:ls_note}
print(d)
f.close()
"""
a) Să se afișeze pentru fiecare grupă în parte studenții;
"""
for grupa in d:
  print(grupa)
  #d[grupa]={nume_student:lista_note}
  for nume_student in d[grupa]: #dupa chei
    print(nume_student)
    
"""
  b) Să se afișeze pentru o grupă citită de la tastatură numele și media fiecărui student dacă a
fost prezent și a promovat toate cele 5 examene din sesiune sau mesajul "restantier"
"""
print("b)")
grupa=191 #int(input())
for nume in d[grupa]:
  ls_note=d[grupa][nume]
  #este integralist
  if len(ls_note)==5 and min(ls_note)>=5:
    media=sum(ls_note)/len(ls_note)
    print(f"{nume} media {media:.2f}")
  else:
    print(f"{nume} restantier")
    
  