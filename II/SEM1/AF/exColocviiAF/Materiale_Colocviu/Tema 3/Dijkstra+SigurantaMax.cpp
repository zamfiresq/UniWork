#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;
ifstream fin("retea.in");

const int N = 1000, Inf=1e9;
vector<pair<int, int>> G[N];
int d[N], tata[N];
int n, m, s, t;

void Citire(){

    fin>>n>>m;
    for(int i=1; i<=m; i++){
        int x,y,cost;
        fin>>x>>y>>cost;
        G[x].push_back({y,cost});
    }
    cout<<"Dati nodul sursa: "; cin>>s;
    cout<<"\nDati nodul destinatie: "; cin>>t;
    cout<<"\nDrumul de siguranta maxima de la "<<s<<" la "<<t<<" este ";
}

void Dijkstra(){
    for(int i=1; i<=n; i++){
        d[i]=Inf;
        tata[i]=0;
    }
    d[s]=0;

    priority_queue<int> pq;
    pq.push(s);

    while (!pq.empty()) {
        int x = pq.top();
        pq.pop();

        for (const auto& muchie : G[x]) {
            int y = muchie.first;
            int cost = muchie.second;

            if (d[x] + cost < d[y]) {
                d[y] = d[x] + cost;
                pq.push(y);
                tata[y] = x;
            }
        }
    }
}

void Lant(int x) {
    if (x == 0) {
        return;
    }
    Lant(tata[x]);
    cout<<x<<" ";
}

int main()
{
    Citire();
    Dijkstra();
    Lant(t);
    cout<<". Siguranta acestui drum este 2^(-"<<d[t]<<")\n";
    return 0;
}
