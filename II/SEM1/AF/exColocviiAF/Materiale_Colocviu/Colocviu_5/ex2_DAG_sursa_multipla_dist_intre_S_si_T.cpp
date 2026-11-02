#include <bits/stdc++.h>
using namespace std;
ifstream fin("graf.in");
const int N = 1000, Inf=1e9;

vector<pair<int, int>> G[N];
vector<int> viz(N, 0);
vector<int> cost(N, 0), activitati_critice;
int d[N], d2[N], tata[N], tata2[N], grad_intern[N], grad_extern[N];
stack<int> S;
int n, m, t1,t2, k, t,s;

void Citire(){

    fin>>n>>m;
    for(int i=1; i<=m; i++){
        int x,y,cost;
        fin>>x>>y>>cost;
        G[x].push_back({y,cost});
    }
    s=n+1;
    fin>>k;
    for(int i=1; i<=k; i++)
        G[s].push_back({i,0});
    fin>>t1>>t2;
    t=n+2;
    G[t1].push_back({t,0});
    G[t2].push_back({t,0});
    n+=2;
}

void DFS(int x) {
    viz[x] = 1;

    for (const auto y : G[x]) {
        if (!viz[y.first]) {
            DFS(y.first);
        }
    }

    S.push(x);
}

void SortTop() {
    for (int i=1; i<=n; ++i) {
        if (!viz[i]) {
            DFS(i);
        }
    }
}

void DAG(){
    for(int i=1; i<=n; i++)
    {
        d[i]=Inf;
        tata[i]=0;
    }

    d[s]=0;

    while (!S.empty()) {
        int x=S.top();
        for (const auto& y : G[x])
        {
            if(d[x]+y.second<d[y.first]){
                d[y.first]=d[x]+y.second;
                tata[y.first]=x;
            }
        }
        S.pop();
    }

}
void Lant(int x, int par[]) {
    if (x == 0) {
        return;
    }
    Lant(par[x], par);
    if(x!=s)
        cout << x << " ";
}

int nod1, nod2;

void Lant1(int x, int par[]) {
    if (x == s) {
        return;
    }
    Lant1(par[x], par);
    if(nod2==0)
        nod2=x;
    nod1=x;
}
int main()
{
    Citire();
    SortTop();
    if(S.size()!=n)
        {
            cout<<"Graful are circuite!";
            return 0;
        }
    DAG();
    cout<<"distanta intre multimi = "<<d[t]<<"\n";;

    Lant1(tata[t],tata);
    cout<<"s="<<nod2<<" t="<<nod1<<"\n";
    cout<<"drum minim: ";
    Lant(tata[t],tata);

    return 0;
}
