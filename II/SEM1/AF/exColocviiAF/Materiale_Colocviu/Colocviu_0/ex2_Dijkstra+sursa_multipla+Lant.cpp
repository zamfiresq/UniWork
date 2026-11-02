#include <bits/stdc++.h>

using namespace std;

ifstream fin("graf.in");

const int NMAX = 100, Inf=1e9;
vector<pair<int, int>> G[NMAX + 1];
int d[NMAX], tata[NMAX];
int n,m,k;

void Citire(){
    fin>>n>>m;
    for(int i=1; i<=m; i++){
        int x,y,cost;
        fin>>x>>y>>cost;
        G[x].push_back({y,cost});
    }
    fin>>k;
    for(int i=1; i<=k; i++){
        int s;
        fin>>s;
        G[0].push_back({s,0});
    }
}

void Dijkstra() {
    for(int i=0; i<=n; i++){
        d[i]=-Inf;
        tata[i]=0;
    }
    d[0]=0;

    priority_queue<int> pq;
    pq.push(0);

    while (!pq.empty()) {
        int x = pq.top();
        pq.pop();
        for (const auto& muchie : G[x]) {
            int y = muchie.first;
            int cost = muchie.second;

            if (d[x] + cost > d[y]) {
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
    cout << x << " ";
}

int main()
{
    Citire();
    Dijkstra();

    int vmax=0, nod;

    fin>>k;
    for(int i=1; i<=k; i++){
        int t;
        fin>>t;
        if(d[t]>vmax)
        {
            vmax=d[t];
            nod=t;
        }

    }
    cout<<vmax<<"\n";

    cout<<"Drumul\n";
    Lant(nod);
    return 0;
}
