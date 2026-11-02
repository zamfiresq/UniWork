"""1.	Se citește un cuvânt. Să se șteargă din cuvânt toate aparițiile primei litere.
Se va afișa un mesaj de forma:
După ștergerea literei 'X' șirul obținut este "S" de lungime L folosind diferite tipuri de formatare
(cu parametri poziționali și f-stringuri)"""
s="acasa"
c=s[0]
s=s.replace(c,"")
print("Dupa stergerea literei '{}' sirul obtinut este \"{}\" de lungime {}".format(c,s,len(s)) )
print(f"Dupa stergerea literei '{c}' sirul obtinut este \"{s}\" de lungime {len(s)}" )
print(f"""Dupa stergerea literei '{c}' sirul obtinut este "{s}" de lungime {len(s)}""")

