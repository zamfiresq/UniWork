#include<iostream>
#include<vector>
#include<queue>




// exercitiul 1
// arbori binari
struct nod{
    int data;
    nod* left;
    nod *right;
};


nod* newNode(int data) // creare nod
{
    nod* nod1 = new nod();
    nod1->data = data;
    nod1->left = NULL;
    nod1->right = NULL;

    return (nod1);
}

// in acest caz, pentru fiecare apel recursiv, nivelul este decrementat
void printLevel(nod* root, int leveleDeCoborat) {
    if(root == NULL)
        return;

    if(leveleDeCoborat == 0)
        std::cout<<root->data<<" ";
    else{
        printLevel(root->left, leveleDeCoborat-1);
        printLevel(root->right, leveleDeCoborat-1);
    }

}


void pb1() {
    nod *root = newNode(20);
    root->left = newNode(8);
    root->right = newNode(22);
    root->left->left = newNode(4);
    root->left->right = newNode(12);
    root->left->right->left = newNode(10);
    root->left->right->right = newNode(14);
    printLevel(root, 2); //se va afisa 4 12

}





// exercitiul 2
// implementare lista dublu inlantuita

struct nodLista{
    int data;
    nodLista* next;
    nodLista* prev;
};

// inserarea datelor la inecputul listei
void pushL(nodLista** nodStart, int dataNou){ // push left
    nodLista *nodNou = new nodLista(); // crearea unui nod nou
    nodNou->data = dataNou;
    nodNou->next = (*nodStart);
    nodNou->prev = nullptr;

    if ((*nodStart) != nullptr)
        (*nodStart)->prev = nodNou;

    (*nodStart) = nodNou;

}

// inserarea datelor la sfarsitul listei
void pushR(nodLista** nodStart, int dataNou) { // push right
    nodLista* nodNou = new nodLista();
    nodNou->data = dataNou;
    nodNou->next = nullptr;
    nodNou->prev = nullptr;

    if ((*nodStart) == nullptr) {
        (*nodStart) = nodNou;
    } else {

        nodLista* curent = (*nodStart); // cream un nod curent care are ca valoare nodul de start
        while (curent->next != nullptr) {
            curent = curent->next;
        }
        curent->next = nodNou;
        nodNou->prev = curent;
    }
}

// stergerea datelor de la inceputul listei
int popL(nodLista** nodStart) {
    if ((*nodStart) == nullptr) {
        std::cout << "Acest deque este gol!\n";
        return -1;
    }

    int valoareFata = (*nodStart)->data; // initializam valoarea fata cu valoarea nodului de start
    nodLista* temporar = (*nodStart); // crearea unui nod temporar

    (*nodStart) = (*nodStart)->next;
    if ((*nodStart) != nullptr) {
        (*nodStart)->prev = nullptr;
    }

    delete temporar;
    return valoareFata;
}

// stergerea datelor de la sfarsitul listei
int popR(nodLista** nodStart) {
    if ((*nodStart) == nullptr) {
        std::cout << "Deque este gol!\n";
        return -1;
    }

    nodLista* curent = (*nodStart);
    while (curent->next != nullptr) {
        curent = curent->next;
    }

    int valoareSfarsit = curent->data; // initializam valoare sfarsit cu valoarea nodului curent

    if (curent->prev != nullptr) {
        curent->prev->next = nullptr;
    } else {
        (*nodStart) = nullptr;
    }

    delete curent;
    return valoareSfarsit;
}

// afisarea listei
void printDequeue(nodLista* nodStart) {
    if (nodStart == nullptr) {
        std::cout << "Deque nu are niciun element.\n";
        return;
    }

    std::cout << "Afisare deque:\n";
    nodLista* curent = nodStart;

    while (curent->next != nullptr) {
        std::cout << curent->data << " ";
        curent = curent->next;
    }
    std::cout << curent->data << "\n";

    std::cout << "Afisare deque in sens invers:\n";

    while (curent->prev != nullptr) {
        std::cout << curent->data << " ";
        curent = curent->prev;
    }
    std::cout << curent->data << "\n";
}


void pb2(){

    nodLista* start = nullptr;

// se va afisa deque-ul in ordinea 6, 5, 2, 1
// invers 1, 2, 5, 6

    pushL(&start, 5);
    pushR(&start, 2);
    pushL(&start, 6);
    pushR(&start, 1);

    printDequeue(start);

    int fata = popL(&start);
    int capat = popR(&start);


    std::cout << "Element extras de la inceput: " << fata << "\n";
    std::cout << "Element extras de la sfarsit: " << capat << "\n";
}





// exercitiul 3
// priority queue
// creare nod cu prioritate
struct nodPrioritate{
    int prioritate;
    int valoare;

    //constructor
    nodPrioritate(int val, int prioritate){
        this->valoare = val;
        this->prioritate = prioritate;
    }

    //operator <, >
    bool operator<(const nodPrioritate& nod) const{
        return (prioritate < nod.prioritate);
    }

    bool operator>(const nodPrioritate& nod) const{
        return (prioritate > nod.prioritate);
    }


    //operator =
    const nodPrioritate &operator=(const nodPrioritate& nod){
        this->valoare = nod.valoare;
        this->prioritate = nod.prioritate;
        return *this;
    }

};


// declaram coadaPrioritate care are elemente de tipul nodPrioritate
std::priority_queue<nodPrioritate, std::vector<nodPrioritate>, std::less<> > coadaPrioritate;

// functie pentru a insera un element in coadaPrioritate
void insert(int val, int prioritate) {
    nodPrioritate nod(val, prioritate);
    coadaPrioritate.push(nod);
}


// functie pentru a extrage elementul maxim din coadaPrioritate
int extragereMax() {
    if (coadaPrioritate.empty()) {
        return -1;
    }
    int val = coadaPrioritate.top().valoare; // extragem valoarea elementului maxim cu top()
    coadaPrioritate.pop();
    return val;
}

// functie pentru a schimba prioritatea unui element
void changePriority(int val, int pr) {
    std::vector<nodPrioritate> nod1; // facem un nod pentru a retine nodul cu prioritatea schimbata

    while (!coadaPrioritate.empty()) {
        nodPrioritate nod = coadaPrioritate.top(); // extragem elementul maxim
        coadaPrioritate.pop();

        //daca am gasit elementul cautat schimbam prioritatea
        if (nod.valoare == val) {
            nod.prioritate = pr;
        }

        nod1.push_back(nod);
    }

    // refacem coadaPrioritate cu elementul cu prioritatea schimbata
    for (const nodPrioritate& nod : nod1) {
        coadaPrioritate.push(nod);
    }
}

// getter pentru a returna elementul maxim din coadaPrioritate
int getMax() {
    return coadaPrioritate.top().valoare;
}

// afisare
void afisareCoadaPrioritati() {
//    std::cout << "Priority queue:\n ";
    std::priority_queue<nodPrioritate, std::vector<nodPrioritate>, std::less<>> tempQueue = coadaPrioritate; // facem o copie a cozii
    while (!tempQueue.empty()) {
        nodPrioritate nod = tempQueue.top();
        std::cout << "(" << nod.valoare << ", " << nod.prioritate << ") ";
        tempQueue.pop();
    }
    std::cout << "\n";
}

// test
void pb3() {
    std::priority_queue<nodPrioritate> coadaPrioritate;

    // inseram elementele in coada de prioritati
    insert(45, 5);
    insert(20, 4);
    insert(14, 5);
    insert(12, 4);
    insert(31, 2);
    insert(7, 2);
    insert(11, 5);
    insert(13, 1);
    insert(7, 3);

    std::cout<<"Coada prioritati: \n";
    afisareCoadaPrioritati();
    std::cout << "\n";

    std::cout<<"Nodul cu prioritatea cea mai mare: "<<getMax()<<"\n";
    std::cout<<"\n";

    std::cout<<"Coada dupa extragerea elementului cu prioritatea cea mai mare: \n";
    int max = extragereMax();
    afisareCoadaPrioritati();
    std::cout<<"\n";

    changePriority(31, 6);
    changePriority(20,2);
    std::cout<<"Coada dupa schimbarea prioritatii: \n";
    afisareCoadaPrioritati();

    std::cout<<"\n";
}





// exercitiul 4
bool verificare(const std::vector<int>& tarusi) {
    int n = tarusi.size();
    std::unordered_map<int, std::vector<int>> pozitii;

    // pozitiile fiecarui id
    for (int i = 0; i < n; ++i) {
        pozitii[tarusi[i]].push_back(i);
    }

    std::vector<std::pair<int, int>> fire;

    // generarea perechilor (idx1, idx2) pentru fiecare fir
    for (auto& p : pozitii) {
        if (p.second.size() != 2) {
            return false; // fiecare id trebuie sa apara doar de doua ori
        }
        int a = p.second[0], b = p.second[1];
        if (a > b) std::swap(a, b);
        fire.push_back({a, b});
    }

    // verificam daca exista intersectii intre fire
    for (int i = 0; i < fire.size(); ++i) {
        for (int j = i + 1; j < fire.size(); ++j) {
            int a1 = fire[i].first, a2 = fire[i].second;
            int b1 = fire[j].first, b2 = fire[j].second;
            if ((a1 < b1 && b1 < a2 && a2 < b2) ||
                (b1 < a1 && a1 < b2 && b2 < a2)) {
                return false; // intersectie
            }
        }
    }

    return true; // nu exista intersectii
}

void pb4(){
    std::vector<int> tarusi1 = {1, 2, 2, 1, 3, 3, 4, 4}; // valid
    for (int x : tarusi1) std::cout << x << " ";
    std::cout << (verificare(tarusi1) ? " - Configuratie valida\n" : " - Configuratie invalida\n");

    std::vector<int> tarusi2 = {1, 2, 2, 3, 1, 4, 3, 4}; // invalid
    for (int x : tarusi2) std::cout << x << " ";
    std::cout << (verificare(tarusi2) ? " - Configuratie valida\n" : " - Configuratie invalida\n");
}



int main() {
//    pb1();
//    pb2();
//    pb3();
//    pb4(); 


    return 0;
}