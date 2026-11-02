#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("graf.in");
ofstream fout("graf.out");

const int N=1000;

vector<int> C;
vector <int> G[N];
int n,m;
int viz[N];

void Citire(){

    fin>>n>>m;
    for(int i=1; i<=m; i++){
        int x,y;
        fin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
}
void sterge_muchia(int u, int v) {
    for (int i=0; i<G[u].size(); ++i) {
        if (G[u][i] == v) {
            G[u].erase(G[u].begin() + i);
            break;
        }
    }

    for (int i = 0; i < G[v].size(); ++i) {
        if (G[v][i] == u) {
            G[v].erase(G[v].begin() + i);
            break;
        }
    }
}
void euler(int v) {
    while (!G[v].empty()) {
        int w = G[v].back();
        sterge_muchia(v, w);
        euler(w);
    }
    C.push_back(v);
}
void DFS(int x){
    viz[x]=1;
    for(auto y: G[x])
        if(viz[y]==0)
            DFS(y);
}

bool verifica_condtii()
{
    for(int i=1; i<=n; i++)
        if((G[i].size())%2!=0)
            return 0;
    for(int i=1; i<=n; i++)
        if(G[i].size()!=0)
    {
        DFS(i);
        for(int j=1; j<=n; j++)
            if(G[j].size()!=0 && viz[j]==0)
                return 0;
        return 1;
    }
    return 1;
}
int main()
{
    Citire();
    if(verifica_condtii()==0)
    {
        fout<<"Graful nu este eulerian!";
        return 0;
    }
    euler(1);
    for(auto v: C)
        fout<<v<<" ";
    return 0;
}
