def afis_matrice(m):
	for linie in m:
		for x in linie:
			print(f"{x:4}",end="")
		print()

f=open("triunghi.in")
n=int(f.readline())
t=[]
for linie in f:
	t.append([int(x) for x in linie.split()])
f.close()

#VARIANTA 1: s[i][j] = suma maxima pentru traseul care incepe cu celula (i,j)
s=[[0 for j in range(i)] for i in range(1,n+1)]

for i in range(n):
	s[n-1][i]=t[n-1][i]

for i in range(n-2,-1,-1):
	for j in range(0,i+1):
		if s[i+1][j]>s[i+1][j+1]:
			s[i][j]=t[i][j]+s[i+1][j]
		else:
			s[i][j]=t[i][j]+s[i+1][j+1]
#afis_matrice(t)
afis_matrice(s)

#traseu reconstituit din relatia de recurenta
print("Un traseu construit din relatia de recurenta (numerotare linii/coloane de la 1)")
j=0
for i in range(n-1):
	print(f"{t[i][j]} ({i+1} {j+1})")
	if s[i][j]==t[i][j]+s[i+1][j+1]:
		j+=1

print(f"{t[n-1][j]} ({n} {j+1})") #ultima linie

""""""
#VARIANTA 2: s[i][j] = suma maxima pentru traseul care incepe se termina cu celula (i,j)
#si incepe cu (1,1)

s=[[0 for j in range(i)] for i in range(1,n+1)]

s[0][0]=t[0][0]

for i in range(1,n):
	s[i][0]=t[i][0]+s[i-1][0]
	for j in range(1,i):
		if s[i-1][j]>s[i-1][j-1]:
			s[i][j]=t[i][j]+s[i-1][j]
		else:
			s[i][j]=t[i][j]+s[i-1][j-1]
	s[i][i]=t[i][i]+s[i-1][i-1]
#afis_matrice(t)
afis_matrice(s)

#solutia = maximul pe ultima linie
jmax=0
for j in range(n):
	if s[n-1][jmax]<s[n-1][j]:
		jmax=j

#traseu reconstituit din relatia de recurenta - de jos in sus
print("Un traseu construit din relatia de recurenta (numerotare linii/coloane de la 1) de jos in sus")
j=jmax
for i in range(n-1,-1,-1):
	print(f"{t[i][j]} ({i+1} {j+1})")
	if j>0 and s[i][j]==t[i][j]+s[i-1][j-1]:
		j-=1


