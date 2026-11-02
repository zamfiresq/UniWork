//#include <iostream>
//#include <vector>
//#include <queue>
//#include <stack>
//
//// BFS + DFS pentru a determina daca un graf are cel putin 2 arbori partiali
//
//const int N = 100005, INF=1e9;
//
//// vector de vizitatEx1 pentru BFS si DFS
//std::vector<int> vizitatEx1;
//
//// vectori pentru a retine parintii fiecarui nod
//std::vector<int> parinte1, parinte2;
//
//// listele de adiacenta pentru arborele partial 1 si arborele partial 2
//std::vector<std::vector<int> > adiacenta1, adiacenta2;
//
//// graf sub forma de lista de adiacenta
//std::vector<std::vector<int> > Graf1;
//
//// stack si queue pentru BFS1 si DFS1
//std::stack<int> stivaEx1;
//std::queue<int> coada;
//
//// numarul de noduri si numarul de muchii
//int n, m;
//
//
//
//// functia BFS1
//void BFS1(int s){
//    coada.push(s); // adaugam nodul s in coada
//    vizitatEx1[s] = 1; // marcam nodul ca vizitatEx1
//
//    while(!coada.empty()){ // cat timp coada nu este goala
//        int u = coada.front(); // extragem nodul din fata cozii
//        coada.pop(); // eliminam nodul din fata cozii
//
//        for(auto next : Graf1[u]){ // pentru fiecare vecin al nodului u
//            if(!vizitatEx1[next]){ // daca vecinul nu a fost vizitatEx1
//                coada.push(next); // adaugam vecinul in coada
//                parinte1[next] = u; // retinem parintele nodului v
//                vizitatEx1[next] = 1; // marcam vecinul ca vizitatEx1
//                adiacenta1[u].push_back(next); // retinem adiacenta pentru arborele partial 1
//                adiacenta1[next].push_back(u); // retinem adiacenta pentru arborele partial 1
//            }
//        }
//    }
//}
//
//// functia DFS1
//void DFS1(int s){
//vizitatEx1[s] = 1; // marcam nodul ca vizitatEx1
//
//    for(auto next : Graf1[s]){ // pentru fiecare vecin al nodului s
//        if(!vizitatEx1[next]){ // daca vecinul nu a fost vizitatEx1
//            parinte2[next] = s; // retinem parintele nodului v
//            adiacenta2[s].push_back(next); // retinem adiacenta pentru arborele partial 2
//            adiacenta2[next].push_back(s); // retinem adiacenta pentru arborele partial 2
//            DFS1(next); // apelam recursiv DFS1 pentru vecinul respectiv
//        }
//    }
//}
//
//
//int main(){
//    // citim numarul de noduri si numarul de muchii
//    std::cin >> n >> m;
//
//    // redimensionam vectorii
//    vizitatEx1.resize(N, 0);
//    parinte1.resize(N, 0);
//    parinte2.resize(N, 0);
//    Graf1.resize(N);
//    adiacenta1.resize(N);
//    adiacenta2.resize(N);
//
//    // citim muchiile
//    for(int i = 1; i <= m; i++){
//        int x, y;
//        std::cin >> x >> y;
//        Graf1[x].push_back(y);
//        Graf1[y].push_back(x); // graf neorientat
//    }
//
//    // apelare bfs
//    BFS1(1);
//    for (int i = 1; i <= n; i++)
//        vizitatEx1[i] = 0;
//
//    // apelare dfs
//    DFS1(1);
//    for(int i = 1; i <= n; i++)
//        if(vizitatEx1[i] == 0){
//            std::cout<< "Nu\n";
//            return 0;
//        }
//        bool OK = 0;
//
//        for(int i = 1; i <= n; i++)
//            if(parinte1[i] != parinte2[i]){
//                OK = 1;
//                //break;
//            }
//
//            if(OK == 0){
//                std::cout << "Nu\n";
//            }else{
//                std::cout << "Da\n";
//
//                // afisare arbori partiali
//                for(int i = 1; i <= n; i++){
//                    for(auto y : adiacenta1[i]){
//                        std::cout << y << " ";
//                    }
//                    std::cout << "\n";
//                }
//
//                for(int i = 1; i <= n; i++){
//                    for(auto y : adiacenta2[i]){
//                        std::cout << y << " ";
//                    }
//                    std::cout << "\n";
//                }
//    }
//
//
//    return 0;
//}