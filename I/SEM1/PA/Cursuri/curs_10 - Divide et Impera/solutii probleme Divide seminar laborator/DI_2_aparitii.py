def prima_aparitie(v,x,p,u):
    print(p,u)
    if p>u:
        return -1
    mij=(p+u)//2
    if (v[mij]==x) and (mij==0 or v[mij-1]!=x):
        return mij
    if x<=v[mij]:
        return prima_aparitie(v,x,p,mij-1)
    else:
        return prima_aparitie(v, x, mij + 1, u)
def ultima_aparitie(v,x,p,u):
    if p>u:
        return -1
    mij=(p+u)//2
    if (v[mij]==x) and (mij==len(v)-1 or v[mij+1]!=x):
        return mij
    if x<v[mij]:
        return ultima_aparitie(v,x,p,mij-1)
    else:
        return ultima_aparitie(v, x, mij + 1, u)
def nr_aparitii(v,x):
    p1 = prima_aparitie(v,x,0,len(v)-1)
    if p1 == -1:
        return 0
    p2 = ultima_aparitie(v, x, 0, len(v) - 1)
    if p2 == -1:
        return 1
    print("prima",x,":",p1,p2)
    return p2 - p1 + 1


v= [1, 2, 2, 3, 3, 3, 3,5,6,6,7,7,7]

print(nr_aparitii(v,1))
print(nr_aparitii(v,2))
print(nr_aparitii(v,3))
print(nr_aparitii(v,4))
print(nr_aparitii(v,5))
print(nr_aparitii(v,6))
print(nr_aparitii(v,7))