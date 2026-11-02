#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("calculatoare.in");
#define N 10000
const int Inf=1e9;

int n, s, t, m, tata[N], viz[N];
vector<pair<int, pair<int, int>>> G[N];
int studenti;

void Citire(){


    fin>>n>>m;
    s=n+m+1;
    t=n+m+2;
    for(int i=1; i<=n; i++)
    {
        int g;
        fin>>g;
        G[s].push_back({i,{g,0}});
        studenti+=g;
    }

    for(int i=1; i<=m; i++)
    {
        int c;
        fin>>c;
        G[n+i].push_back({t,{c,0}});
    }

    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
        {
            int c;
            fin>>c;
            G[i].push_back({n+j,{c,0}});
        }
}
int flux_de_intrare(int nod){
    int s=0;
    for(int i=1; i<=t; i++)
        for (const auto& muchie : G[i])
            if(muchie.first==nod)
                s+=muchie.second.second;
    return s;
}
int flux_de_iesire(int nod){
    int s=0;
    for (const auto& muchie : G[nod]){
        s+=muchie.second.second;
    }
    return s;
}

bool flux_corect()
{
    for(int i=1; i<=t; i++)
        for (const auto& muchie : G[i])
    {
        int f=muchie.second.second, c=muchie.second.first;
        if(c<0||f<0||f>c)
            return false;
    }
    for(int i=1; i<=t; i++)
        if(i!=s && i!=t && flux_de_intrare(i)!=flux_de_iesire(i))
            return false;
    if(flux_de_iesire(s)!=flux_de_intrare(t))
        return false;
    return true;
}
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

void Edmonds_Karp(){
    while(construieste_st_lant_nesat_BF())
    {
        revizuieste_flux_lant();
    }
}

int main()
{

    Citire();
    Edmonds_Karp();

    if(flux_corect()==0 || flux_de_intrare(t)!=studenti)
    {
        cout<<"NU\n";
        for(int x=1; x<=t; x++)
            for (auto& muchie : G[x]){
                muchie.second.second=0;
                if(x>=n&&x<=n+m)
                    muchie.second.first+=1;
            }

        Edmonds_Karp();

        if(flux_de_intrare(t)!=studenti)
            cout<<"NU";
        else
        {
            cout<<"DA"<<"\n";
        for(int x=1; x<=n; x++)
        {
            cout<<"Grupa "<<x<<": ";
            for (const auto& muchie : G[x]){
                int flux=muchie.second.second;
                cout<<flux<<" ";
            }
            cout<<"\n";
            }
        }

    }
    else if(flux_de_intrare(t)==studenti)
    {
        cout<<"DA"<<"\n";
        for(int x=1; x<=n; x++)
        {
            cout<<"Grupa "<<x<<": ";
            for (const auto& muchie : G[x]){
                int flux=muchie.second.second;
                cout<<flux<<" ";
            }
            cout<<"\n";
        }
    }
    /*
    exemplu 1
    3 3
    7 8 1
    7 9 2
    1 7 2
    6 7 2
    0 1 1

    */

    /*
    exemplu 2
    2 2
    5 5
    5 5
    5 0
    1 4
    */
    return 0;
}

