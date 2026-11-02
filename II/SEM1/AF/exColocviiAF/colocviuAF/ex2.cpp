//#include <iostream>
//#include <vector>
//#include <stack>
//#include <fstream>
//
//
//// DAG + DFS + sortare topologica + drum maxim
//
//std::ifstream fin("/Users/alexandrazamfirescu/Desktop/exColocviiAF/colocviuAF/grafZamfi.in");
//
//std::vector<std::vector<int>> G; // graful G sub forma de lista de adiacenta
//std::vector<bool> vizitat; // vector de vizitat
//std::vector<int> distanta; // vector de distante
//std::vector<int> parinte; // vector de parinti pentru a retine parintele fiecarui nod
//std::stack<int> stiva; // stiva pentru sortarea topologica
//
//int n, m, k; // n - numarul de noduri, m - numarul de muchii, k - numarul de destinatii
//const int N = 100005;
//
//// functia DFS
//void DFS(int s) {
//    vizitat[s] = true; // marcam nodul ca vizitat
//
//    for (const auto& next : G[s]) { // pentru fiecare vecin al nodului s
//        if (!vizitat[next]) { // daca vecinul nu a fost vizitat
//            DFS(next); // apelam recursiv DFS pentru vecinul respectiv
//        }
//    }
//
//    stiva.push(s); // adaugam nodul s in stiva
//}
//
//// sortare topologica pentru a putea calcula distanta maxima
//void sortareTopologica() {
//    for(int i = 1; i <= n; i++) { // pentru fiecare nod din graf
//        if (!vizitat[i]) { // daca nodul nu a fost vizitat, apelam DFS recursiv
//            DFS(i);
//        }
//    }
//}
//
//// calculam distanta maxima
//void drumMaxim() {
//    for (int i = 1; i <= n; i++) { // initializam distanta fiecarui nod cu 0
//        distanta[i] = 0;
//    }
//
//    while (!stiva.empty()) { // cat timp stiva nu este goala
//        int u = stiva.top(); // extragem nodul din varful stivei
//        stiva.pop();
//
//        for (const auto& v : G[u]) { // pentru fiecare vecin al nodului u
//            if (distanta[v] < distanta[u] + 1) { // daca distanta maxima de la vecin poate fi actualizata
//                distanta[v] = distanta[u] + 1; // actualizam distanta maxima
//                parinte[v] = u; // retinem parintele nodului v
//            }
//        }
//    }
//}
//
//// functie pentru afisarea drumului maxim
//void afisareDrumMaxim(int nod) {
//    if (nod == 0) { // daca nodul nu are parinte, ne oprim
//        return;
//    }
//
//    afisareDrumMaxim(parinte[nod]); // apelam recursiv pentru parintele nodului
//    std::cout << nod << " ";
//}
//
//int main() {
//    fin >> n >> m >> k;
//
//    G.resize(N); // redimensionam graful G pentru a avea N noduri
//    vizitat.resize(N, false);
//    distanta.resize(N, 0);
//    parinte.resize(N, 0);
//
//    std::vector<int> destinatii(k); // vectorul de destinatii
//    for (int i = 0; i < k; i++) { // citim destinatiile
//        fin >> destinatii[i];
//    }
//
//    for (int i = 0; i < m; i++) { // citim muchiile
//        int x, y;
//        fin >> x >> y;
//        G[x].push_back(y);
//    }
//
//    sortareTopologica(); // sortam topologic graful
//
//    drumMaxim(); // calculam distanta maxima
//
//    int maxim = 0;
//    int nod = 0;
//
//    for (const auto& dest : destinatii) { // pentru fiecare destinatie
//        if (distanta[dest] > maxim) { // cautam distanta maxima
//            maxim = distanta[dest];
//            nod = dest;
//        }
//    }
//
//    std::cout << maxim << "\n";
//
//    afisareDrumMaxim(nod); // afisam drumul maxim
//
//    return 0;
//}
