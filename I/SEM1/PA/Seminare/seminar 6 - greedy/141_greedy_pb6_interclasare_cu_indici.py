import heapq
nr_deplasari=0
ls=[int(x) for x in input().split()]
lung=[] #heap de lungimi
k=1
for x in ls:
    heapq.heappush(lung, (x,k))
    k+=1

#while len(lung)>1: #complexitate: se repeta de n ori
for i in range(len(lung)-1):
    l1,i1=heapq.heappop(lung) #minimul este lung[0]
    l2,i2=heapq.heappop(lung)  #cplx O(log(n))

    print(f"interclasam sirul {i1} de lungime {l1} cu sirul {i2} de lungime {l2} => sirul {k} lungime {l1+l2}")
    heapq.heappush(lung, (l1+l2,k)) #O(log(n)
    k+=1
    nr_deplasari+=(l1+l2)
# complexitate n*(log(n)+log(n)+log(n)) => O(n log(n))
print(nr_deplasari) #=> O(n log(n))


