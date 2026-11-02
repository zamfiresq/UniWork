#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#define N 100005
using namespace std;
ifstream fin("graf.in");

const int Inf=1e9;
int echipa[N+1];
int viz[N+1];
int n,m;
vector<int> graf[N+1];
//pentru flux
int t, s,tata[N], parent[N], cv;
vector<pair<int, pair<int, int>>> G[N];
vector<int> cycle;
bool stop;

void Citire()
{
    fin>>n>>m;
    int x,y;
    while(fin>>x>>y){
        G[x].push_back({y+n,{1,0}});
    }
}

bool bipartit(int x, int dif) {
    viz[x]=1;
    echipa[x]=dif;
    for (auto next : graf[x]) {
        if(echipa[next]==dif)
            return 0;
        if (echipa[next]==0&&!bipartit(next, 3-dif))
            return 0;
    }
    return 1;
}

bool graf_bipartit()
{
    bool ok=1;
    for (int i=1; i<=n; i++)
        if (!viz[i] && ! bipartit(i, 1))
        {
            cv=i;
            return 0;
        }

    return 1;
}
void Construieste_Graf()
{
    s=n+m+1;
    t=n+m+2;
    for(int i=1; i<=n; i++)
        G[s].push_back({i,{2,0}});
    for(int i=1; i<=m; i++)
        G[n+i].push_back({t,{2,0}});


}

//flux pentru noul graf

bool construieste_st_lant_nesat_BF()
{
    for(int i=1; i<=t; i++){
        tata[i]=viz[i]=0;
    }
    queue<int> pq;
    pq.push(s);
    viz[s]=1;

    while (!pq.empty())
    {
        int x = pq.front();
        pq.pop();

        for (const auto& muchie : G[x]) {
            int y = muchie.first;
            int capacitate = muchie.second.first;
            int flux = muchie.second.second;

            if(viz[y]==0 && capacitate-flux>0){
                pq.push(y);
                viz[y]=1;
                tata[y]=x;
                if(y==t)
                    return true;
            }
        }
        for(int y=1; y<=t; y++)
            for (const auto& muchie : G[y])
                if(muchie.first==x)
                {
                    int capacitate = muchie.second.first;
                    int flux = muchie.second.second;

                    if(viz[y]==0 && flux>0){
                        pq.push(y);
                        viz[y]=1;
                        tata[y]=-x;
                        if(y==t)
                            return true;
                    }
                }

    }
    return false;
}
int calc_ip(int nod) {
    if (tata[nod] == 0) {
        return Inf;
    }
    else if (tata[nod]>0){
        int x=tata[nod], y=nod;
        for (const auto& muchie : G[x])
            if(muchie.first==y){
                int c=muchie.second.first-muchie.second.second;
                return min(c, calc_ip(x));
            }
    }
    else if(tata[nod]<0)
    {
        int y=-tata[nod], x=nod;
        for (const auto& muchie : G[x])
            if(muchie.first==y)
                return min(muchie.second.second, calc_ip(y));
    }
}

void revizuieste_flux_lant(){
    int iP=calc_ip(t);
    int nod=t;
    while(tata[nod]!=0)
    {
        if(tata[nod]>0){
            int x=tata[nod], y=nod;
            for (auto& muchie : G[x])
                if(muchie.first==y){
                    muchie.second.second+=iP;
                }

            nod=x;

        }
        else if(tata[nod]<0){
            int y=-tata[nod], x=nod;
            for (auto& muchie : G[x])
                if(muchie.first==y)
                {
                    muchie.second.second-=iP;
                }

            nod=y;
        }

    }
}
void afiseaza_flux()
{
    for(int i=1; i<=n+m; i++)
        for (auto muchie : G[i])
            if(muchie.second.first==muchie.second.second && muchie.first!=t)
                cout<<i<<" "<<muchie.first-n<<"\n";
}
void Edmonds_Karp(){
    while(construieste_st_lant_nesat_BF())
    {
        revizuieste_flux_lant();
    }
}


int main()
{
    Citire();

    if(graf_bipartit()==0)
    {
        cout<<"Graful nu este bipartit!\n";
    }
    else{
        Construieste_Graf();
        Edmonds_Karp();

        bool ok=1;

        for(int i=1; i<=m; i++)
            for(auto muchie: G[n+i])
                if(muchie.first==t&&muchie.second.first!=muchie.second.second)
                    ok=0;


        if(ok==0)
            cout<<"nu este posibil";
        else
            afiseaza_flux();

    }
    return 0;
}
