#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
ifstream fin("graf.in");
ofstream fout("graf.out");


const int NMAX = 100000;
int viz[NMAX + 1],distanta[NMAX+1],distanta_nou[NMAX+1];
int d[NMAX+1],P[NMAX+1];
int n, m;
vector<int> G[NMAX + 1];
int f[NMAX+1]={0};

void Citire()
{
    fin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i=1; i<=n; i++)
        distanta[i]=n+1;
}

void BFS(int x){
    queue <int> q;
    distanta_nou[x]=0;
    q.push(x);
    viz[x]=1;

    while(!q.empty()){
        x=q.front();
        q.pop();
        for(auto next: G[x]){
            if(!viz[next]){
                P[next]=x;
                q.push(next);
                distanta_nou[next]=distanta_nou[x]+1;
                viz[next]=1;
            }
        }
    }
}

int main()
{
    int i,x;
    Citire();
    while(fin>>x){
        BFS(x);
        for(i=1; i<=n; i++)
            if(distanta_nou[i]<distanta[i])
                distanta[i]=distanta_nou[i];
        for(i=1; i<=n; i++)
            viz[i]=0;
    }

    for(i=1; i<=n; i++)
        fout<<distanta[i]<<" ";
    return 0;
}
