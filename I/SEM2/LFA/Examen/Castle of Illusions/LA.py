# Zamfirescu Alexandra
# Vizinteanu Teodora
# grupa 141


from typing import List, TextIO

import argparse
parser = argparse.ArgumentParser(description='DFA generation and check script')
parser.add_argument('input', help = 'The name of the dfa_config_file')
parser.add_argument('filename', help = 'The name of your input_string file')
args = parser.parse_args()

def get_sigma(file_name: TextIO) -> List[str]:    # returneaza sigma, parcurgand linie cu line
    with open(file_name, 'r') as f:
        sigma = []    # initializare lista sigma returnata la final

        for line in f:   # parcurgere linie cu linie
            if line.startswith('Sigma'):    # daca am ajuns la blocul Sigma
                line = f.readline()     # trecem la linia urmatoare (sa nu prelucram si linia 'Sigma :')
                while line.split()[0] != 'End':   # prelucram pana se termina blocul Sigma
                    if line.startswith('#'):     # daca exista comentarii
                        while line.startswith('#'):    # cat timp exista comentarii
                            line = f.readline() #   linie noua, le omitem, nu prelucram
                    sigma.extend(line.split())   # adaugam elementul sigma la lista
                    line = f.readline()    # trecem la linie noua
        return sigma


def get_list_sigma(file_name: TextIO) -> List[str]:    # returneaza sigma, parcurgand linie cu line
    with open(file_name, 'r') as f:
        sigma = []    # initializare lista sigma returnata la final

        for line in f:   # parcurgere linie cu linie
            if line.startswith('List Sigma'):    # daca am ajuns la blocul Sigma
                line = f.readline()     # trecem la linia urmatoare (sa nu prelucram si linia 'Sigma :')
                while line.split()[0] != 'End':   # prelucram pana se termina blocul Sigma
                    if line.startswith('#'):     # daca exista comentarii
                        while line.startswith('#'):    # cat timp exista comentarii
                            line = f.readline() #   linie noua, le omitem, nu prelucram
                    sigma.extend(line.split())   # adaugam elementul sigma la lista
                    line = f.readline()    # trecem la linie noua
        return sigma



def get_states(file_name: TextIO) -> List[str]:   # returneaza states
    with open(file_name, 'r') as f:
        states = []    # initializare lista cu states, care va fi returnata

        for line in f:
            if line.startswith('States'):     # daca ajungem la blocul States
                line = f.readline()       # trecem la linie nous pentru nu a prelucra linia cu 'States :'
                while line.split()[0] != 'End':      # cat timp nu am ajuns la final
                    if line.startswith('#'):     # daca avem comentarii
                        while line.startswith('#'):     # cat timp avem comentarii
                            line = f.readline()      # linie noua, le omitem
                    ls_states = line.split()      # ne folosim de o lista auxiliara pentru readability si pentru determinarea lungimii liniei (numarului de proprietati)
                    if len(ls_states) == 1:     # daca avem doar un state, fara nicio proprietate
                        states.append(tuple(ls_states))    # doar adaugam state-ul
                    if len(ls_states) == 2:    #   daca state-ul are o proprietate
                        states.append((ls_states[0].strip(','), ls_states[1].strip(',')))     # adaugam un tuplu (state, property1) (!!!AVEM GRIJA LA VIRGULE)
                    if len(ls_states) == 3:      #   daca state-ul are doua proprietati
                        states.append((ls_states[0].strip(','), ls_states[1].strip(','), ls_states[2].strip(',')))     # adaugam un tuplu (state, property1, property2) (!!!VIRGULE)
                    line = f.readline()    # linie noua
        return states



def get_transitions(file_name: TextIO) -> List[str]:    # returneaza transitions
    with open(file_name, 'r') as f:
        transitions = {}   # initializare lista transitions

        for line in f:    # parcurgere linie cu linie
            if line.startswith('Transitions'):   # ajungem la blocul Transitions
                line = f.readline()   # linie noua, nu prelucram linia 'Transitions :'
                while line.split()[0] != 'End':   # cat timp nu am ajuns la finalul blocului
                    if line.startswith('#'):   # daca avem comentarii, le omitem
                        while line.startswith('#'):
                            line = f.readline()
                    ls_transitions = line.split(' -> ')  # lista auxiliara pentru readability
                    first_part = ls_transitions[0].split(',')
                    second_part = ls_transitions[1].split(',')
                    second_part[-1] = second_part[-1].rstrip('\n')
                    transitions[tuple(first_part)] = tuple(second_part)
                    line = f.readline()  #linie noua
        return transitions



def verify_valid(sigma: List[str], list_sigma: List[str], states: List[str], transitions: List[str]) -> bool:
    verifyS = 0   # counter pentru 'S'
    verifyF = 0 # counter pentru F
    for currentState in states:    # parcurgere states
        if 'S' in currentState:    # daca gasim 'S'
            verifyS += 1   # incrementam counter
            if verifyS > 1:   # mai mare decat 1? date nevalide => False
                return False
    if verifyS == 0:
        return False

    for currentState in states:
        if 'F' in currentState:
            verifyF += 1

    if verifyF == 0:
        return False

    strippedStates = []  # lista pentru determinarea states, fara proprietatile aferente
    for currentState in states:
        strippedStates.append(currentState[0])  # adugam fiecare state in parte

    valid = True  # variabila de semnalizare

    for currentTransition in transitions:
        if ((currentTransition[0] not in strippedStates) or (currentTransition[1] not in sigma) or (
                currentTransition[2] not in sigma and currentTransition[2] != 'epsilon')):  # verificare conditii
            valid = False
            break  # opriți bucla în caz de eroare
        elif (transitions[currentTransition][0] not in strippedStates or (
                transitions[currentTransition][1] not in sigma and transitions[currentTransition][1] != 'epsilon') or (
                      transitions[currentTransition][2] not in sigma and transitions[currentTransition][
                  2] != 'epsilon')):  # conditii verificare
            valid = False
            break  # opriți bucla în caz de eroare

    return valid  # returnați rezultatul final


def get_start_state(states): # Pentru a cauta mai usor starea de inceput
    for currentState in states:
        if 'S' in currentState:
            return currentState[0]


def get_final_states(states): # pentru a cauta pe parcurs mult mai usor starile finale
    final_states = []
    for currentState in states:
        if 'F' in currentState:
            final_states.append(currentState[0])
    return final_states




def emulateLA(sigma, list_sigma, states, transitions, input_string):
    start_state = get_start_state(states) # stari de incpeut
    final_states = get_final_states(states) # stari de final
    for element in input_string: # pargurgem inputul element cu element
        for currentTransition in transitions: # parcurgem fiecare transition in parte
            if currentTransition[0] == start_state and currentTransition[1] == element and (currentTransition[2] in list_sigma or currentTransition[2] == 'epsilon'): # verific daca starea la care am ajuns este egala cu starea tranzitiei la care am ajuns prin parcurgere, daca am citit din fisier valoarea necesara pentru a continua la alta stare sau daca este epsilon, iar apoi trecem la cealalta stare daca e ok si stergem si adaugam (daca sunt diferite de epsilon)
                start_state = transitions[currentTransition][0]
                if (transitions[currentTransition][1] in list_sigma and transitions[currentTransition][1] != 'epsilon'): # am explicat mai sus
                    list_sigma.remove(transitions[currentTransition][1]) # stergem, daca exista
                if (transitions[currentTransition][2] not in list_sigma and transitions[currentTransition][2] != 'epsilon'): # am explicat mai sus
                    list_sigma.append(transitions[currentTransition][2]) # adaugam element, dar verificam mai intai daca exista in fisier ca sa nu avem duplicate

with open(args.filename) as f:
    f.readline()
    input_string = f.readline().split()


#VERIFICARI
sigma = get_sigma(args.input)
states = get_states(args.input)
list_sigma = get_list_sigma(args.input)
transitions = get_transitions(args.input)

print(transitions)
print(states)
print(list_sigma)
print(sigma)

print(verify_valid(sigma, list_sigma, states, transitions))

print(get_final_states(states))
print(get_start_state(states))

if (verify_valid(sigma, list_sigma, states, transitions)):
    emulateLA(sigma, list_sigma, states, transitions, input_string)

print(list_sigma)






