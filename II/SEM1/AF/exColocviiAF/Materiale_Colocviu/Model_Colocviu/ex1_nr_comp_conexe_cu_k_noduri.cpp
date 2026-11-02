#include <iostream>
#include <vector>
using namespace std;

const int NMAX=100005;
int viz[NMAX+1];
vector<int> G[NMAX+1];
int contor, nr_noduri;
int n,m,k;

void DFS(int x) {
    viz[x]=1;
    nr_noduri++;
    for (auto next : G[x]) {
        if(viz[next]==0)
            DFS(next);
    }
}
void Citire()
{
    cin>>n>>m>>k;
    for(int i=1; i<=m; i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
}
int main()
{
    Citire();
    contor=0;
    for(int i=1; i<=n; i++)
        if(!viz[i])
        {
            nr_noduri=0;
            DFS(i);
            if(nr_noduri>=k)
                contor++;
        }
    cout<<contor;
    return 0;
}
