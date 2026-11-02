#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

const int Infinit = 10000000;
const int NMAX = 200000;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
vector<pair<int, int>> G[NMAX + 1];
int d[NMAX + 1], tata[NMAX + 1], viz[NMAX + 1];

ifstream f("grafpond.in");
ofstream g("prim.out");


int main() {
   int n, m;
   f >> n >> m;

   for (int i = 1; i <= m; i++) {
       int x, y, c;
       f >> x >> y >> c;
       G[x].push_back({y, c});
       G[y].push_back({x, c});
   }

   for (int i = 1; i <= n; i++) {
       d[i] = Infinit;
       viz[i] = 0;
   }

   d[1] = 0;
   pq.push({d[1], 1});

   int s = 0, nr_muchii = 0;

   while (!pq.empty()) {
       int x = pq.top().second;
       int cost = pq.top().first;
       pq.pop();

       if (viz[x]) {
           continue;
       }
       viz[x] = 1;
       s += cost;
       nr_muchii++;

       for (auto next : G[x]) {
           if (viz[next.first] == 0 && d[next.first] > next.second) {
               d[next.first] = next.second;
               tata[next.first] = x;
               pq.push({d[next.first], next.first});
           }
       }
   }

   g << s << endl;
   g << nr_muchii - 1 << endl;
   for (int i = 2; i <= n; i++) {
       g << tata[i] << " " << i << endl;
   }

   return 0;
}