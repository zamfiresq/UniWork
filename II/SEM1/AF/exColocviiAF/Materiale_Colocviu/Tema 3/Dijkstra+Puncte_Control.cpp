#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;
ifstream fin("grafpond.in");
ofstream fout("grafpond.out");

const int N = 1000, Inf=1e9;
vector<pair<int, int>> G[N];
vector<int> viz(N, 0);
int d[N], tata[N];
int n, m, k, s;
vector<int> pct_control;
int ct;

void Citire(){

    fin>>n>>m;
    for(int i=1; i<=m; i++){
        int x,y,cost;
        fin>>x>>y>>cost;
        G[x].push_back({y,cost});
        G[y].push_back({x,cost});
    }
    fin>>k;
    for(int i=1; i<=k; i++){
        int x;
        fin>>x;
        pct_control.push_back(x);
    }
    fin>>s;
}


void Dijkstra() {
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

int cmaPctControl() {
    int cmaPctControl = pct_control[0];
    for (int i=1; i<pct_control.size(); ++i) {
        if (d[pct_control[i]] < d[cmaPctControl]) {
            cmaPctControl = pct_control[i];
        }
    }
    return cmaPctControl;
}

void Lant(int x) {
    if (x == 0) {
        return;
    }
    Lant(tata[x]);
    fout << x << " ";
}

int main() {

    Citire();

    Dijkstra();

    int punct_control_cautat = cmaPctControl();

    fout<<s<<endl;
    Lant(punct_control_cautat);
    fout << endl;

    return 0;
}

