# Crossover - Algoritmi Genetici

l = int(input())

# string cromozom1 si cromozom2
x0 = input()
x1 = input()

# punctul de rupere
i = int(input())

C1 = x0[:i] + x1[i:]
C2 = x1[:i] + x0[i:]


print(C1)
print(C2)
