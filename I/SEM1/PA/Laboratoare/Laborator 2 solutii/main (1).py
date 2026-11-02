"""
Problema 5
a) Scrieți un program care să înlocuiască într-o propoziție toate aparițiile unui cuvânt
𝑠 cu un cuvânt 𝑡 (!cuvânt, nu subșir). Cuvintele sunt separate prin unul sau mai multe
spații.
b) Aceeași cerință ca la a), dar pentru cazul în care cuvintele din propoziție sunt
despărțite între ele prin spații și semnele de punctuație uzuale
"""
"""
prop=input()
s=input()
t=input()
prop=prop.replace(" "+s+" "," "+t+" ")
prop=prop.replace(" "+s+" "," "+t+" ")
print(prop)
"""
prop=input()
s=input()
t=input()
cuv=prop.split(" ")
print(cuv)
for i in range(0, len(cuv)):
    if cuv[i]==s:
        cuv[i]=t
print(cuv)
cuv=" ".join(cuv)
print(cuv)