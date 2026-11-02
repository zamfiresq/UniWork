"""
#seminar1 prob codificare-decodificare
n=input()
nr=0
for c in n:
    if c.isdigit():
        nr=nr*10+int(c)
    else:
        for i in range(nr):
            print(c, end="")
        nr=0

print()

n=input()
ant=n[0]
nr=1
for i in range(1,len(n)):
    if n[i]==ant:
        nr+=1
    else:
        print(nr,end="")
        print(ant,end="")
        nr=1
        ant=n[i]
print(nr,end="")
print(ant,end="")
"""
#prob 2 lab 2
s=input()
prima_lit=s[0]
for i in range(1, len(s)):
    if(s[i]==prima_lit):
        s[:i]=s[i+1:]  #stergere caracter curent==prima_lit
print("dupa stergerea literei", '"', prima-lit, '"', "sirul obtinut este", s, "de lungime", '"', len(s), '"')

