#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
ifstream fin("graf.in");

using namespace std;

const int NMAX = 1000, INF=1e9;
int viz[NMAX + 1],d[NMAX+1]={INF}, P[NMAX+1];
int n, s, vmin;
vector<pair<int, int>> G[NMAX + 1];

void Citire()
{
    fin >> n;
    for (int x = 1; x <= n; x++)
    {
        int grad;
        fin>>grad;
        for(int i=1; i<=grad; i++)
        {
            int y, cost;
            fin >> y >> cost;
            G[x].push_back({y,cost});
        }
    }

    fin>>s;
}

void BFS(int x){
    queue <int> q;
    d[x]=INF;
    q.push(x);
    viz[x]=1;

    while(!q.empty()){
        x=q.front();
        q.pop();
        for(auto muchie: G[x]){
            int next=muchie.first;
            int cost=muchie.second;
            if(!viz[next]){
                P[next]=x;
                q.push(next);
                if(cost<d[x])
                    d[next]=cost;
                else
                    d[next]=d[x];
                viz[next]=1;
            }
        }
    }
}

void Lant(int x) {
    if (x == 0) {
        return;
    }
    Lant(P[x]);
    cout << x << " ";
}

int main()
{
    int nod;
    Citire();
    BFS(s);
    d[s]=0;
    vmin=INF;
    nod=0;
    for(int i=1; i<=n; i++)
    {
        cout<<i<<": "<<d[i]<<"\n";
        if(vmin>d[i] && i!=s){
            vmin=d[i];
            nod=i;
        }
    }
    cout<<"Capacitatea minima este "<<vmin<<" pentru lantul ";
    Lant(nod);
    return 0;
}
