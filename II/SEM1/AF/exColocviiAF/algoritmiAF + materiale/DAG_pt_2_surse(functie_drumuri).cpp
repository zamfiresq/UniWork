#include <bits/stdc++.h>
using namespace std;
const int NMAX = 1000, INF=1e9;
vector<pair<int, int>> G[NMAX];
vector<int> viz(NMAX, 0);
int d1[NMAX], d2[NMAX];
stack<int> S;
int n, m, s1, s2, u, v, tata[NMAX];
vector<vector<int>> allpaths;

void Citire(){

   cin >> n >> m;

   for(int i = 1; i <= m; i++){
       int x, y, cost;
       cin >> x >> y >> cost;
       G[x].push_back({y, cost});
   }

   cin >> s1 >> s2;
}

void DFS(int x) {
   viz[x] = 1;

   for (auto y : G[x]) {
       if (!viz[y.first]) {
           DFS(y.first);
       }
   }

   S.push(x);
}

void SortTop() {
   for (int i = 1; i <= n; i++) {
       if (!viz[i]) {
           DFS(i);
       }
   }
}

void findAllPaths(int source, int destination, vector<int>& path, vector<vector<int>>& allPaths) {
   path.push_back(source);

   if (source == destination) {
       allPaths.push_back(path);
   } else {
       for (auto& neighbor : G[source]) {
           findAllPaths(neighbor.first, destination, path, allPaths);
       }
   }

   path.pop_back();
}

void DAG(){
   for(int i = 1 ; i <= n; i++)
   {
       d1[i] = INF;
       d2[i] = INF;
   }

   d1[s1] = d2[s2] = 0;

   SortTop();

   while (!S.empty()) {
       int x = S.top();
       for (auto& y : G[x])
       {
           if(d1[x] + y.second < d1[y.first]){
               d1[y.first] = d1[x] + y.second;
               tata[y.first] = x;
           }
           if(d2[x] + y.second < d2[y.first]){
               d2[y.first] = d2[x] + y.second;
           }
       }
       S.pop();
   }
}

int main()
{
   Citire();
   DAG();

   cout << "a)" << endl;
   int nod_egal_departat_de_s1_si_s2 = 1;
   while(d1[nod_egal_departat_de_s1_si_s2] != d2[nod_egal_departat_de_s1_si_s2]) {
       nod_egal_departat_de_s1_si_s2++;
   }
   cout << "v = " << nod_egal_departat_de_s1_si_s2 << endl;

   cout << "b)" << endl;
   vector<int> path;
   vector<vector<int>> allPaths;
   findAllPaths(s1, nod_egal_departat_de_s1_si_s2, path, allPaths);
   int nr_drumuri = 0;
   for(const auto& drum : allPaths) {
       for(auto nod : drum) {
           cout << nod << " ";
       }
       cout << endl;
       nr_drumuri++;
       if(nr_drumuri == 2)
           break;
   }

   return 0;
}