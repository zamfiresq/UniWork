# intersectii semiplane orizontale si verticale

n = int(input().strip())

# limitele extreme 
x_negativ = float('-inf')
x_pozitiv = float('inf')
y_negativ = float('-inf')
y_pozitiv = float('inf')

for i in range(n):
    a, b, c = map(float, input().split())
    if a == 0: # daca semiplanul este orizontal
        limita = -c / b 
        if b > 0: # daca semiplanul este deasupra axei OX
            y_pozitiv = min(y_pozitiv, limita) # am inversat aici
        else:
            y_negativ = max(y_negativ, limita)
    else: # daca semiplanul este vertical
        limita = -c / a
        if a > 0: 
            x_pozitiv = min(x_pozitiv, limita) # am inversat aici 
        else:
            x_negativ = max(x_negativ, limita)

# verificam daca exista intersectie
if x_negativ > x_pozitiv or y_negativ > y_pozitiv:
    print('VOID')
elif x_negativ == float('-inf') or x_pozitiv == float('inf') or y_negativ == float('-inf') or y_pozitiv == float('inf'):
    print('UNBOUNDED')
else:
    print('BOUNDED')

