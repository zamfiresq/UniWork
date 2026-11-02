#include <bits/stdc++.h>

using namespace std;

const int INF = 1e4;
const int NMAX = 201;

int N, M, K, capacitate[NMAX][NMAX], flux[NMAX][NMAX], tata[NMAX], indice;
vector <int> G[NMAX];

int EdmondsKarp(int src, int dest) {
   //BFS
   queue<int> q;
   indice = 0;
   int vis[NMAX] = {0};
   int flow = INF;
   bool reachesDest = false;

   q.push(src);
   vis[src] = 1;

   while(!q.empty()) {
       int nod = q.front();
       q.pop();

       for(auto next : G[nod]) {
           //daca putem continua lantul nesaturat elementar prin next
           if(capacitate[nod][next] - flux[nod][next] > 0 && !vis[next]) {
               tata[next] = nod;
               q.push(next);
               vis[next] = 1;

               if(next == dest) {
                   reachesDest = true;
               }
           }
           else if(flux[next][nod] > 0 && !vis[next]) {
               tata[next] = nod;
               q.push(next);
               vis[next] = 1;

               if(next == dest)
                   reachesDest = true;
           }
       }
   }

   if(!reachesDest)
       return 0;

   int current = tata[dest];

   while(current != 0)
   {
       if(capacitate[current][dest] != 0)
           flow = min(flow, capacitate[current][dest] - flux[current][dest]);
       else
       if (capacitate[dest][current] != 0)
           flow = min(flow, flux[dest][current]);

       dest = current;
       current = tata[current];
   }

   return flow;
}

int maxFlow(int src, int dest) {
   int suma = 0;

   for(auto next : G[src]) {
       suma += flux[src][next];
   }

   while(true) {
       //determinam lanturi s-t nesaturate de lungime minima
       int fl = EdmondsKarp(src, dest);
       suma = suma + fl;

       //daca nu am mai gasit lant, acesta este fluxul maxim
       if(fl == 0)
           break;
       else {
           //ne intoarcem pe lantul s-t, actualizand fluxurile
           int destinatia_curenta = dest, sursa_curenta = src;
           while(destinatia_curenta != sursa_curenta) {
               flux[tata[destinatia_curenta]][destinatia_curenta] += fl;
               flux[destinatia_curenta][tata[destinatia_curenta]] -= fl;
               destinatia_curenta = tata[destinatia_curenta];
           }
       }
   }
   return suma;
}

int gasireNrPrim(int flowMax)
{
   bool ePrim = false;

   int val = flowMax;

   while (!ePrim)
   {
       ePrim = true;

       if(val % 2 == 0)
       {
           val--;
           ePrim = false;
       }
       else
       {
           for(int i = 3; i * i <= val; i += 2)
               if (val % i == 0)
               {
                   val--;
                   ePrim = false;
                   break;
               }
       }
   }

   return val;
}

int main() {

   cin >> N >> M;

   for(int nod = 1; nod <= N; nod++)
   {
       int lungime;

       cin >> lungime;

       for(int j = 0; j < lungime; j++)
       {
           int next, capacity;

           cin >> next >> capacity;

           capacitate[nod][next] = capacity;
           G[nod].push_back(next);
           G[next].push_back(nod);
       }
   }

   int s, t; // nodurile de start & finish
   cin >> s >> t;

   int flux_maxim = maxFlow(s, t);

   // a) Gasirea celui mai mare numar prim k cu proprietatea ca exista un flux de valoare k
   K = gasireNrPrim(flux_maxim);
   cout << K << endl;

   // b) Decideti daca exista o s-t taietura in retea de capacitate k si afisati un mesaj corespunzator
   if (K < flux_maxim) {
       cout << "Nu" << endl;
   } else {
       cout << "Da" << endl;
   }

   return 0;
}