#include <bits/stdc++.h>
using namespace std;
ifstream fin("graf.in");
const int N = 1000, Inf=1e9;
vector<pair<int, int>> G[N];
vector<int> viz(N, 0);
vector<int> cost(N, 0), activitati_critice;
int d[N], d2[N], tata[N], grad_intern[N], grad_extern[N];
stack<int> S;
int n, m, s, t, u, v;

void Citire(){

    fin>>n>>m;
    for(int i=1; i<=m; i++){
        int x,y,cost;
        fin>>x>>y>>cost;
        G[x].push_back({y,cost});
    }
    fin>>s>>t;
    fin>>u>>v;
}

void DFS(int x) {
    viz[x] = 1;

    for (const auto y : G[x]) {
        if (!viz[y.first]) {
            DFS(y.first);
        }
    }

    S.push(x);
}

void SortTop() {
    for (int i=1; i<=n; ++i) {
        if (!viz[i]) {
            DFS(i);
        }
    }
}

void DAG(){
    for(int i=1; i<=n; i++)
    {
        d[i]=-Inf;
        d2[i]=Inf;
        tata[i]=0;
    }

    d[s]=d2[t]=0;

    SortTop();

    while (!S.empty()) {
        int x=S.top();
        for (const auto& y : G[x])
        {
            if(d[x]+y.second>d[y.first]){
                d[y.first]=d[x]+y.second;
                tata[y.first]=x;
            }
            if(d2[x]+y.second<d2[y.first]){
                d2[y.first]=d2[x]+y.second;
            }
        }
        S.pop();
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
    DAG();

    cout<<d[t]+d2[v]<<"\n";
    Lant(v);
    return 0;
}
