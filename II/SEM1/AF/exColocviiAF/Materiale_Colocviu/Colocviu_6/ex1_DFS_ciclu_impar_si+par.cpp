#include <bits/stdc++.h>
using namespace std;
ifstream fin("graf.in");

const int NMAX = 1000, Inf=1e9;
vector<int> G[NMAX+1];
int viz[NMAX+1], nivel[NMAX +1], tata[NMAX+1];
int n,m;

void Citire()
{
    fin>>n>>m;
    int x,y;
    for(int i=1; i<=m; i++){
        fin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
}

int nod1, nod2, nod11, nod22;
void dfs(int x) {
    viz[x] = 1;
    for(auto next : G[x]) {
        if(!viz[next]) {

            nivel[next]=nivel[x]+1;
            tata[next]=x;
            dfs(next);

        }
        else
        {
            if((nivel[next]-nivel[x])%2==0 && nod1==0 && nivel[next]-nivel[x]>0)
            {
                nod1=next;
                nod11=x;
            }
            if(nod2==0 && next!=nod11 && nivel[next]-nivel[x]>0)
                nod2=next;
                nod22=x;
        }
    }
}
int copie;
void Lant(int x, int par[], int stop) {
    copie=x;
    if (x == stop) {
        return;
    }

    Lant(par[x], par, stop);
    cout << x << " "<<par[x]<<"\n";
}

int main()
{
    Citire();
    dfs(1);
    cout<<"a)\n";
    Lant(nod1, tata, nod11);
    cout<<copie<<" "<<nod1<<"\n";
    cout<<"b)\n";
    if(nod2!=0)
    {
        Lant(nod2, tata, nod22);
        cout<<copie<<" "<<nod2<<"\n";
    }

    else
        cout<<"Nu mai exista alt ciclu";
    return 0;
}
