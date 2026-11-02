#include <iostream>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;
#define N 10000
const int Inf=1e9;

int n, s, t, m, tata[N], viz[N], vmax;
vector<pair<int, pair<int, int>>> G[N];
vector<pair<pair<int,int>, int>> taieturi;

int gasirenrprim(int flowmax)
{
   bool eprim = false;

   int val = flowmax;

   while (!eprim)
   {
       eprim = true;

       if(val % 2 == 0)
       {
           val--;
           eprim = false;
       }
       else
       {
           for(int i = 3; i * i <= val; i += 2)
               if (val % i == 0)
               {
                   val--;
                   eprim = false;
                   break;
               }
       }
   }

   return val;
}

void Citire(){

    cin>>n>>m;
    for(int i=1; i<=n; i++){
        int grad;
        cin>>grad;
        for(int j=1; j<=grad; j++)
        {
            int y,capacitate;
            cin>>y>>capacitate;
            G[i].push_back({y,{capacitate,0}});
        }
    }
    cin>>s>>t;
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
    return 0;
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

    vmax=flux_de_iesire(s);
    // a) gasirea celui mai mare numar prim k cu proprietatea ca exista un flux de valoare k
    int k = gasirenrprim(vmax);
    cout << k << endl;

    // b) decideti daca exista o s-t taietura in retea de capacitate k si afisati un mesaj corespunzator
    if (k < vmax) {
        cout << "Nu" << endl;
    } else {
        cout << "Da" << endl;
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
    Edmonds_Karp();
    return 0;
}
