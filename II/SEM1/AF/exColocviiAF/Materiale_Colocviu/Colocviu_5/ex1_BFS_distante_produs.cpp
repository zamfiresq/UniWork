#include <bits/stdc++.h>
using namespace std;
ifstream fin("graf.in");

const int NMAX = 1000, INF=1e9;
int viz[NMAX + 1],d1[NMAX+1]={INF}, d2[NMAX+1]={INF}, P1[NMAX+1], P2[NMAX+1];
int n,m,s, vmin;
vector<pair<int,int>> G[NMAX + 1], T1[NMAX + 1], T2[NMAX + 1];

void Citire()
{
    fin>>n>>m;
    for(int i=1; i<=m; i++)
    {
        int x,y,cost;
        fin>>x>>y>>cost;
        G[x].push_back({y,cost});
        G[y].push_back({x,cost});
    }
    fin>>s;
}

void BFS(int x){
    queue <int> q;
    q.push(x);
    viz[x]=1;

    d1[x]=1;

    while(!q.empty()){
        x=q.front();
        q.pop();
        for(auto next: G[x]){
            if(!viz[next.first]){
                P1[next.first]=x;
                q.push(next.first);
                viz[next.first]=1;
                d1[next.first]=d1[x]*next.second;
                T1[x].push_back({next.first, next.second});
            }
        }
    }
}

int main()
{
    Citire();
    BFS(s);
    d1[s]=0;
    bool ok=0;
    if(m==n-1)
        cout<<"Este arbore\n";
    else
        cout<<"Nu este arbore!\n";
    for(int i=1; i<=n; i++)
        cout<<i<<": "<<d1[i]<<"\n";
    return 0;
}
