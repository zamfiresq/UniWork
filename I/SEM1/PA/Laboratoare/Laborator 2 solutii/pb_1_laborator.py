#stergerea aparitiilor primei litere
s="unul altul"
c=s[0]
s=s.replace(s[0],"") #pe toate, !!!!s=
print(f"După ștergerea literei '{c}' șirul obținut este \"{s}\" de lungime {len(s)} ")
print("După ștergerea literei '{}' șirul obținut este \"{}\" de lungime {} ".format(c,s,len(s)))

#Dupăștergerealiterei 'X'șirulobținuteste "S"de lungime L folosind diferite tipuri de formatare

"""problema 4"""
prop="Problemele cu șiruri de caracteger nu sunt ggerle!"
s="re"
t="ger"
"""
a)
prop=prop.replace(t,s) #toate
print(prop)
"""
p=1
if prop.count(t)>p:
    print(f"inlocuim primele {p}")
    prop = prop.replace(t, s, p)  # primele cel mult p
    print(prop)
