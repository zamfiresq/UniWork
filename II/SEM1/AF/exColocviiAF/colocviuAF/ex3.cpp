//#include <iostream>
//#include <vector>
//#include <queue>
//
//// flux maxim + ford fulkerson / edmonds karp
//
//std::vector<std::vector<int>> G; // graful G sub forma de lista de adiacenta
//std::vector<std::vector<int>> C; // matricea de capacitati
//std::vector<std::vector<int>> F; // matricea de fluxuri
//std::vector<bool> vizitat; // vector de vizitat
//std::vector<int> parinte; // vector de parinti pentru a retine parintele fiecarui nod
//std::queue<int> coada; // coada pentru BFS
//
//int n, m; // n - numarul de noduri, m - numarul de muchii
//int s, t; // s - nodul sursa, t - nodul destinatie
//const int N = 100005;
//
//
//// edmonds karp
//
//// functie de flux de intrare
//int fluxIntrare(int nod){
//    int s = 0;
//    for(int i = 1; i <= n; i++){
//        s += F[i][nod];
//    }
//    return s;
//}
//
//// functie de flux de iesire
//int fluxIesire(int nod){
//    int s = 0;
//    for(int i = 1; i <= n; i++){
//        s += F[nod][i];
//    }
//    return s;
//}
//
//// functie pentru a verifica daca fluxul este corect
//bool fluxCorect(){
//    for(int i = 1; i <= n; i++){
//        if(fluxIntrare(i) != fluxIesire(i)){
//            return false;
//        }
//    }
//    return true;
//}
//
//// functie pentru BFS pentru a construi drumul de crestere
//bool BFS(){
//    for(int i = 1; i <= n; i++){
//        vizitat[i] = false;
//    }
//
//    coada.push(s);
//    vizitat[s] = true;
//    parinte[s] = 0;
//
//    while(!coada.empty()){
//        int u = coada.front();
//        coada.pop();
//
//        for(int v = 1; v <= n; v++){
//            if(!vizitat[v] && C[u][v] - F[u][v] > 0){
//                coada.push(v);
//                parinte[v] = u;
//                vizitat[v] = true;
//            }
//        }
//    }
//
//    return vizitat[t];
//}
//
//// functie pentru a calcula fluxul maxim
//int fluxMaxim(){
//    int fluxMaxim = 0;
//
//    while(BFS()){
//        int fluxCurent = INT_MAX;
//
//        for(int v = t; v != s; v = parinte[v]){
//            int u = parinte[v];
//            fluxCurent = std::min(fluxCurent, C[u][v] - F[u][v]);
//        }
//
//        for(int v = t; v != s; v = parinte[v]){
//            int u = parinte[v];
//            F[u][v] += fluxCurent;
//            F[v][u] -= fluxCurent;
//        }
//
//        fluxMaxim += fluxCurent;
//    }
//
//    return fluxMaxim;
//}
//
//int main(){
//    std::cin >> n >> m; // citim numarul de noduri si numarul de muchii
//
//    G.resize(N); // redimensionam graful G pentru a avea N noduri
//    C.resize(N, std::vector<int>(N, 0)); // redimensionam matricea de capacitati pentru a avea N noduri
//    F.resize(N, std::vector<int>(N, 0)); // redimensionam matricea de fluxuri pentru a avea N noduri
//    vizitat.resize(N, false); // redimensionam vectorul de vizitat pentru a avea N noduri
//    parinte.resize(N, 0); // redimensionam vectorul de parinte pentru a avea N noduri
//
//    std::cin >> s >> t; // citim nodul sursa si nodul destinatie
//
//    for(int i = 1; i <= m; i++){ // citim muchiile
//        int x, y, c;
//        std::cin >> x >> y >> c;
//        G[x].push_back(y);
//        G[y].push_back(x);
//        C[x][y] = c;
//    }
//
//    std::cout << fluxMaxim() << "\n"; // afisam fluxul maxim
//
//    return 0;
//}