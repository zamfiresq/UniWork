lung=[int(x) for x in input().split()]
nr_deplasari=0
while len(lung)>1: #for i in range(len(lung)-1): #complexitate: se repeta de n ori (De fapt n-2)
    l1=min(lung)  #O(n), de fapt n-i
    lung.remove(l1) #O(n), de fapt n-i
    l2=min(lung) #O(n), de fapt n-i-1
    lung.remove(l2) #O(n), de fapt n-i-1
    print(f"interclasam lungimile  {l1} cu {l2} => lungime {l1+l2}")
    lung.append(l1+l2) #O(n)
    nr_deplasari+=(l1+l2)
#complexitate n*(n+n+n+n)  => O(n^2)
# (mai exact suma pentru i de la 0 la n-2 din 4(n-i), dar suma 1+2+...+n=n(n+1)/2 este O9n2), ca si n+n+...+n)

print(nr_deplasari) #=> O(n^2)

import heapq
ls=[3,7,5,9,8]
h=[]
for x in ls:
    heapq.heappush(h,x)
    print(h)
heapq.heappush(h,4)
print(h)
x=heapq.heappop(h) #minimul din h - h[0]
print(x)
print(h)


nr_deplasari=0
ls=[int(x) for x in input().split()]
lung=[] #heap de lungimi
for x in ls:
    heapq.heappush(lung, x)

#while len(lung)>1: #complexitate: se repeta de n ori
for i in range(len(lung)-1):
    print(lung)
    l1=heapq.heappop(lung) #minimul este lung[0]
    l2=heapq.heappop(lung)  #cplx O(log(n))

    print(f"interclasam lungimile  {l1} cu {l2} => lungime {l1+l2}")
    heapq.heappush(lung, l1+l2) #O(log(n)
    nr_deplasari+=(l1+l2)
# complexitate n*(log(n)+log(n)+log(n)) => O(n log(n))
print(nr_deplasari) #=> O(n log(n))


