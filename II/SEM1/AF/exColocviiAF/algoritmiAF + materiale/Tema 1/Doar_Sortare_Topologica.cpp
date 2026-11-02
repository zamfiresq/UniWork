#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
//ifstream fin("topsort.in");
//ofstream fout("topsort.out");


const int NMAX = 100000;
int viz[NMAX + 1],vizT[NMAX+1],vizST[NMAX+1];
int C[NMAX],k,CST[NMAX],kST;
int n, m;
vector<int> G[NMAX + 1],GT[NMAX+1];
int CTC;
int Comp[NMAX+1];
int f[NMAX+1]={0};

void Citire()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        GT[y].push_back(x);

    }

}


//PARTE SORTARE
void DFSST(int x)
{
    vizST[x]=1;
    for(auto next: G[x]){
        if(!vizST[next]){
            DFSST(next);
        }
    }
    CST[++kST]=x;
}

void SortareTopologica()
{
    int i;
    for(i=1; i<=n; i++)
        if(!vizST[i]) DFSST(i);
    for(i=kST;i>=1; i--)
        cout<<CST[i]<<" ";
}

//PARTE CICLU
void DFS(int x)
{
    viz[x]=1;
    for(auto next: G[x]){
        if(!viz[next]){
            DFS(next);
        }
    }
    C[++k]=x;
}

void StabilireTimpiFinali()
{
    for(int i=1; i<=n; i++)
        if(viz[i]==0) DFS(i);
}
void DFST(int x)
{
    vizT[x]=1; Comp[x]=CTC;
    for(auto next: GT[x]){
        if(!vizT[next]){
            Comp[next]=CTC; DFST(next);
        }
    }
}
void Kosaraju()
{
    int i;
    StabilireTimpiFinali();
    for(i=k; i>=1; i--)
        if(vizT[C[i]]==0)
    {
        CTC++;
        DFST(C[i]);
    }
}

int main()
{
    int i,nr,ct=0;
    Citire();

    //pentru a determina elementele tare conexe (pentru cicluri) folosim Kosaraju
    Kosaraju();
    for(i=1;i<=n; i++)
       f[Comp[i]]++;

    int vmax=-1, val;
    for(int i=1; i<=CTC; i++)
    {
        if(f[i]>vmax) {vmax=f[i]; val=i;}
    }

    bool ok=0;
    if(vmax==1){
        for(int i=1; i<=n; i++)
            if(f[Comp[i]]==1){
                for(auto next: G[i])
                    if(i==next) ok=1;
            }
    }
    if(ok==0&&vmax==1)
        SortareTopologica();
    else {
        cout<<"IMPOSSIBLE";
    }
    return 0;
}
