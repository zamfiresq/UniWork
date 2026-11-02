#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("secvente.in");
#define N 10000
const int Inf=1e9;

int n, s, t, m, tata[N], viz[N], nr_vf, suma_gradelor;
vector<pair<int, pair<int, int>>> G[N];
bool grade=1;

void Construieste_Graf()
{
    s=2*n+1;
    t=2*n+2;
    for(int i=1; i<=n; i++)
    {
        for(int j=n+1; j<=2*n; j++)
            if(j!=n+i)
                G[i].push_back({j,{1,0}});
    }
}
void Citire(){

    fin>>n;
    if(n<=2)
        grade=0;
    nr_vf=n;
    Construieste_Graf();
    int suma=0;
    for(int i=1; i<=n; i++){
        int grad_int;
        fin>>grad_int;
        G[n+i].push_back({t,{grad_int,0}});
        suma+=grad_int;
        if(grad_int>=n)
            grade=0;
    }
    suma_gradelor=suma;
    if(suma>n*(n-1))
        grade=0;
    for(int i=1; i<=n; i++){
        int grad_ext;
        fin>>grad_ext;
        G[s].push_back({i,{grad_ext,0}});
        suma-=grad_ext;
        if(grad_ext>=n)
            grade=0;
    }
    if(suma!=0)
        grade=0;
    n=n*2+2;
}
int flux_de_intrare(int nod){
    int s=0;
    for(int i=1; i<=n; i++)
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
    for(int i=1; i<=n; i++)
        for (const auto& muchie : G[i])
    {
        int f=muchie.second.second, c=muchie.second.first;
        if(c<0||f<0||f>c)
            return false;
    }
    for(int i=1; i<=n; i++)
        if(i!=s && i!=t && flux_de_intrare(i)!=flux_de_iesire(i))
            return false;
    if(flux_de_iesire(s)!=flux_de_intrare(t))
        return false;
    return true;
}
bool construieste_st_lant_nesat_BF()
{
    for(int i=1; i<=n; i++){
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
        for(int y=1; y<=n; y++)
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

void afiseaza_flux(){
    if(flux_corect()==0 || suma_gradelor>flux_de_iesire(s))
        cout<<"NU";
    else
    {
        for(int x=1; x<=n-2; x++)
            for (const auto& muchie : G[x])
                if(muchie.second.second==1 && muchie.first!=t)
                {
                    int y=muchie.first;
                    cout<<x<<" "<<y-nr_vf<<"\n";
                }
    }

}
void Edmonds_Karp(){
    while(construieste_st_lant_nesat_BF())
    {
        revizuieste_flux_lant();
    }
    afiseaza_flux();
}

int main()
{

    Citire();
    if(grade==1)
        Edmonds_Karp();
    else
        cout<<"NU";
    return 0;
}
