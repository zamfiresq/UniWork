# testul de orientare

def test_orientare(xp, yp, xq, yq, xr, yr):
    # calculare orientare
    orientare = (xq * yr + xp * yq + yp * xr) - (xq * yp + xr * yq + yr * xp) 

    # verificam valoarea orientarii
    if orientare == 0:
        return "TOUCH"
    elif orientare < 0:
        return "RIGHT"
    else:
        return "LEFT"

    
# citire input 
# t = int(input())

# for i in range(t):
#     xp, yp, xq, yq, xr, yr = map(int, input().split())
#     test_orientare(xp, yp, xq, yq, xr, yr)


# 3
# 1 1 5 3 2 3
# 1 1 5 3 4 1
# 1 1 5 3 3 2
    

# ---------------------------------------------------------------------

# orientare viraje - Roby

# creez un array de viraje
viraje = [0,0,0]

def viraj(xp, yp, xq, yq, xr, yr):
    # apelam functia test_orientare
    rezultat = (xq * yr + xp * yq + yp * xr) - (xq * yp + xr * yq + yr * xp) 

    if rezultat > 0:
        viraje[0] += 1 # viraje stanga 
    elif rezultat < 0:
        viraje[1] += 1 # viraje dreapta
    else:
        viraje[2] += 1 # viraje touch

# citire input
n = int(input())

# sa zicem ca luam primele 2 puncte
x_start, y_start = map(int, input().split()) # x1 = x_start, y1 = y_start
x1, y1 = x_start, y_start

x2, y2 = map(int, input().split()) 

for i in range(n - 2):
    x3, y3 = map(int, input().split())

    viraj(x1, y1, x2, y2, x3, y3)

    x1, x2, y1, y2 = x2, x3, y2, y3 

# trebuie sa ne intoarcem la primul punct (start)
viraj(x1, y1, x2, y2, x_start, y_start)
for i in viraje:
    print(i, end=" ")


# 7
# 1 1
# 2 2
# 2 0
# 3 0
# 4 0
# 5 0
# 6 0




