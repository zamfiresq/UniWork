#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int> > G; // graful sub forma de lista de adiacenta
std::vector<bool> vizitat; // vector pt noduri vizitate
std::vector<std::pair<int, int> > muchii; // vector de perechi pt muchii

int n, m;

// graf orientat
std::vector<std::vector<int> > GO; // graful sub forma de lista de adiacenta

// vom avea nevoie de un vector in care sa retinem componentele conexe
std::vector<int> componente;


// DFS pentru a determina componentele conexe
void DFS(int s) {
   vizitat[s] = true;

   for(auto next : G[s]){
       if(!vizitat[next]){
           DFS(next);
       }else {
           if (GO[s][next] == 1) {
               std::pair<int, int> muchie = std::make_pair(s, next);
               muchii.push_back(muchie);
           }
       }
   }
}


int main() {
   // citirea datelor
   int conex = 0;
   std::cin >> n >> m;

   G.resize(n + 1);
   GO.resize(n + 1, std::vector<int>(n + 1, 0));
   vizitat.resize(n + 1, false);

   for(int i = 1; i <= m; i++) {
       int x, y;
       std::cin >> x >> y;
       G[x].push_back(y);
       G[y].push_back(x);

       // pentru graful orientat
       GO[y][x] = 1;
   }

   for(int i = 1; i <= n; i++) {
       if(!vizitat[i]) {
           DFS(i);
           componente.push_back(i);
           conex++;
       }
   }

   int nrMuchiiScoase= muchii.size();

   if(nrMuchiiScoase < conex) {
       std::cout << "NU E POSIBIL";
   } else {
       std::cout << "k = " << conex - 1 << "\n";

       std::cout << "k-stergere a arcelor\n";
       for(int i = 0; i < conex - 1; i++) {
           std::cout << muchii[i].first << " " << muchii[i].second << "\n";
       }

       std::cout << "k-adaugare a arcelor\n";
       for(int i = 0; i < componente.size() - 1; i++) {
           std::cout << componente[i] << " " << componente[i + 1] << "\n";
       }
   }

   return 0;

}