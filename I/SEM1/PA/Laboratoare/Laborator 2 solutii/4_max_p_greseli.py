prop="Problemele cu șiruri de caracteger nu sunt ggerle daca gerpeti gergulat!"
s="re"
t="ger"
prop=prop.replace(t,s) # !!! replace nu modifica s + inlocuieste toate aparitiile
print(prop)

#b)
prop="Problemele cu șiruri de caracteger nu sunt ggerle daca gerpeti gergulat!"
s="re"
t="ger"
p=2
if prop.count(t)>p:  
    print(f"prea multe greseli, doar {p} au fost corectate")
    s=s.replace(t,s,p) #inlocuieste doar primele p aparitii

print(prop)

