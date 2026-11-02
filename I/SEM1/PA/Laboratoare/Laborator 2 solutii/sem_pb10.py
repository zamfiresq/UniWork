
#seminar1 prob codificare-decodificare
#decodificarea
n=input()
nr=0
rez=""
ls_rez=[]
for c in n:
    if c.isdigit(): #"0"<=c<="9"
        nr=nr*10+int(c)
    else:
        """
        for i in range(nr):
            print(c, end="")
        """
        """
        print(c*nr, end="")
        """
        rez=rez+c*nr
        ls_rez.extend([c]*nr)
        nr=0

print(rez)
print(ls_rez)
ls_rez="".join(ls_rez) #separator.join(lista de cuvinte)
print(ls_rez)

n=rez
ant=n[0]
nr=1
sir_init=""
for i in range(1,len(n)):
    if n[i]==ant:
        nr+=1
    else:
        """print(nr,end="")
        print(ant,end="")
        """
        sir_init+=str(nr)+ant
        nr=1
        ant=n[i]
"""        
print(nr,end="")
print(ant,end="")
"""
sir_init+=str(nr)+ant
print(sir_init)