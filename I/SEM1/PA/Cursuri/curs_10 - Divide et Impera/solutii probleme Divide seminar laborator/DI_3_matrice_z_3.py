def umple(x,y,n):
    global k
    if n==1:
        k+=1
        a[x][y]=k
    else:
        dim=n//2
        umple(x,y+dim,dim)
        umple(x+dim,y,dim)
        umple(x, y , dim)
        umple(x + dim, y+dim, dim)




n=int(input())
p2n=1<<n
k=0
a=[[0 for i in range(p2n)] for j in range(p2n)]
umple(0,0,p2n)
for linie in a:
    for x in linie:
        print(f"{x:4}",end="")
    print()