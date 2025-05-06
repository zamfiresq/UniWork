# ex 1 - translator finit nedeterminist cu lambda-tranzitii (NFA)


# definire translator:
stari = set()
stare_initiala = None
stari_finale = set()
alfabet_initial = set()
alfabet_final = set()
tranzitii = dict()  # (stare, simbol) -> lista de (stare_finala, simbol_iesire)


# citire NFA
def citire_nfa(filename):
    global stare_initiala, stari_finale, alfabet_initial, alfabet_final, tranzitii, stari
    
    # resetare variabilele globale pt a permite multiple executii
    stari = set()
    stari_finale = set()
    alfabet_initial = set()
    alfabet_final = set()
    tranzitii = dict()
    
    with open(filename, 'r') as f:
        lines = f.read().splitlines()

    idx = 0

    # citire stari
    n = int(lines[idx])
    idx += 1
    stari = []
    for _ in range(n):
        stari.append(lines[idx])
        idx += 1

    # citire stare initiala
    stare_initiala = lines[idx]
    idx += 1

    # citire stari finale
    m = int(lines[idx]) # nr stari finale
    idx += 1
    for _ in range(m):
        stari_finale.add(lines[idx])
        idx += 1

    # citire alfabet de intrare
    alfabet_initial = []
    n = int(lines[idx]) # nr simboluri alfabet intrare
    idx += 1
    for _ in range(n):
        alfabet_initial.append(lines[idx])
        idx += 1

    # citire alfabet de iesire
    alfabet_final = []
    n = int(lines[idx])
    idx += 1
    for _ in range(n):
        alfabet_final.append(lines[idx])
        idx += 1

    # initializare dictionar de tranzitii
    for stare in stari:
        for simbol in alfabet_initial + ['']:
            tranzitii[(stare, simbol)] = [] # tranzitii posibile

    # citire tranzitii normale
    for stare in stari:
        for simbol in alfabet_initial:
            if idx >= len(lines):
                break
            m = int(lines[idx])  # numar de tranzitii pentru (stare, simbol)
            idx += 1
            # print("debugging", stare, simbol, m, idx)
            for _ in range(m):
                if idx >= len(lines):
                    break
                parts = lines[idx].split()
                if len(parts) >= 2:
                    stare_finala = parts[0]
                    simbol_iesire = parts[1]
                    tranzitii[(stare, simbol)].append((stare_finala, simbol_iesire))
                idx += 1

    # citire tranzitii lambda
    for stare in stari:
        if idx >= len(lines):
            break
        m = int(lines[idx])  # numar de lambda-tranzitii pt starea respectiva
        idx += 1
        for _ in range(m):
            if idx >= len(lines):
                break
            parts = lines[idx].split()
            if len(parts) >= 2:
                stare_finala = parts[0]
                simbol_iesire = parts[1]
                tranzitii[(stare, '')].append((stare_finala, simbol_iesire))
            idx += 1

# functie pt simularea NFA (cu lambda-tranzitii)
def simulare_nfa(input_string):
    rezultate = set() # stocarea iesirilor posibile

    def bkt(stare_curenta, index_input, iesire_curenta, visited_lambda):
        # iesire daca suntem in stare finala si am consumat tot inputul
        if index_input == len(input_string) and stare_curenta in stari_finale:
            rezultate.add(iesire_curenta.replace('λ', ''))

        # aplicare lambda-tranzitii
        for next_state, output_symbol in tranzitii.get((stare_curenta, ''), []):
            if (stare_curenta, next_state) not in visited_lambda:
                visited_lambda.add((stare_curenta, next_state))
                bkt(next_state, index_input, iesire_curenta + output_symbol, visited_lambda)
                visited_lambda.remove((stare_curenta, next_state))

        # aplicare tranzitii normale
        if index_input < len(input_string):
            simbol_curent = input_string[index_input]
            for next_state, output_symbol in tranzitii.get((stare_curenta, simbol_curent), []):
                bkt(next_state, index_input + 1, iesire_curenta + output_symbol, set())

    bkt(stare_initiala, 0, "", set())
    return list(rezultate)




# testare
if __name__ == "__main__":
    filename = 'tema2/input.txt'
    citire_nfa(filename)
    
    print("\nDetalii translator:")
    print(f"Stari: {stari}")
    print(f"Stare initiala: {stare_initiala}")
    print(f"Stari finale: {stari_finale}")
    print(f"Alfabet intrare: {alfabet_initial}")
    print(f"Alfabet iesire: {alfabet_final}")
    print(f"Tranzitii:")
    for key, value in tranzitii.items():
        if value:  # doar tranzitii cu iesiri
            stare, simbol = key
            simbol_display = 'λ' if simbol == '' else simbol
            print(f"  ({stare}, {simbol_display}) -> {value}")
    
    n = int(input("\nNumarul de siruri de testat: "))
    for i in range(n):
        sir = input(f"Sirul #{i+1}: ")
        rezultate = simulare_nfa(sir)
        
        print(f"Sirul '{sir}':", end=" ")
        if rezultate:
            print(f"este acceptat. Iesiri posibile ({len(rezultate)}): {', '.join(rezultate)}")
        else:
            print("nu este acceptat.")