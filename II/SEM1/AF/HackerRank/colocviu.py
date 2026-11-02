# subiectul 1

# Se consideră un arbore cu n noduri și rădăcină r. Se dau două noduri c1, c2. Să se determine descendenții comuni ai celor două noduri. Complexitate: O(n)

# Input format
# Pe prima linie se află 4 valori: n, r, c1, c2, reprezentând numărul de noduri, rădăcina arborelui și nodurile pentru care trebuie afișați descendenții comuni. Pe următoarele n-1 linii se află câte o pereche de valori reprezentând muchiile arborelui. 

# Output format:
# Pe prima linie se afișează descendenții comuni ai nodurilor c1, c2. În cazul în care acestea nu au niciun descendent comun se afișează valoarea 0. Descendenții pot fi afișați în orice ordine.

# tehnica: DFS

def dfs(node, parent, G, descendants):
    # Adaugăm descendenții în set
    for neighbor in G[node]:
        if neighbor != parent:
            descendants.add(neighbor)
            dfs(neighbor, node, G, descendants)

n, r, c1, c2 = map(int, input().split())

# Construirea listei de adiacență pentru arbore
G = [[] for _ in range(n + 1)]
for _ in range(n - 1):
    x, y = map(int, input().split())
    G[x].append(y)
    G[y].append(x)

# Găsim descendenții lui c1 și c2 folosind DFS
descendants_c1 = set()
descendants_c2 = set()

# Parcurgem arborele pentru c1 și c2
dfs(c1, -1, G, descendants_c1)
dfs(c2, -1, G, descendants_c2)

# Găsim intersecția descendenților
common_descendants = descendants_c1.intersection(descendants_c2)

# Afișăm rezultatul
if common_descendants:
    print(" ".join(map(str, common_descendants)))
else:
    print(0)


