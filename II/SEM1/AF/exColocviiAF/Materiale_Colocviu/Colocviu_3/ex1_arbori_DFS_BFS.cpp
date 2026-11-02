#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
ifstream fin("graf.in");

using namespace std;

const int NMAX = 1000, INF=1e9;
int viz[NMAX + 1],d1[NMAX+1]={INF}, d2[NMAX+1]={INF}, P1[NMAX+1], P2[NMAX+1];
int n,m,s, vmin;
vector<int> G[NMAX + 1], T1[NMAX + 1], T2[NMAX + 1];

void Citire()
{
    fin>>n>>m;
    for(int i=1; i<=m; i++)
    {
        int y, x;
        fin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    fin>>s;
}

void BFS(int x){
    queue <int> q;
    q.push(x);
    viz[x]=1;
    d1[x]=0;

    while(!q.empty()){
        x=q.front();
        q.pop();
        for(auto next: G[x]){
            if(!viz[next]){
                P1[next]=x;
                q.push(next);
                viz[next]=1;
                d1[next]=d1[x]+1;
                T1[x].push_back(next);
            }
        }
    }
}

void DFS(int x)
{
    viz[x]=1;

    for(auto y: G[x])
        if(viz[y]==0)
        {
            P2[y]=x;
            T2[x].push_back(y);
            d2[y]=d2[x]+1;
            DFS(y);
        }
}
int main()
{
    Citire();
    BFS(s);
    for(int i=1; i<=n; i++)
        viz[i]=0;
    d2[s]=0;
    DFS(s);

    cout<<"T1:\n";
    for(int x=1; x<=n; x++)
        for(auto y: T1[x])
            cout<<x<<" "<<y<<"\n";
    cout<<"T2:\n";
    for(int x=1; x<=n; x++)
        for(auto y: T2[x])
            cout<<x<<" "<<y<<"\n";

    for(int x=1; x<=n; x++)
        if(d1[x]!=d2[x]){
            cout<<"u = "<<x;
            return 0;
        }

    return 0;
}
