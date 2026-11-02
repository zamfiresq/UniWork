#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

ifstream fin("activitati.in");

const int N = 1000, Inf=1e9;
vector<pair<int, int>> G[N];
vector<int> viz(N, 0);
vector<int> cost(N, 0), activitati_critice;
int d[N], tata[N], grad_intern[N], grad_extern[N];
stack<int> S;
int n, m;

void Citire(){
    fin>>n;
    for(int i=1; i<=n; i++)
        fin>>cost[i];
    fin>>m;
    for(int i=1; i<=m; i++){
        int x,y;
        fin>>x>>y;
        G[x].push_back({y,cost[x]});
        grad_intern[y]++;
        grad_extern[x]++;
    }
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

void drum_critic(int x){
    if(x)
    {
        drum_critic(tata[x]);
        cout<<" "<<x;
    }
}
void Rezolva(){
    for(int i=1; i<=n; i++)
    {
        if(grad_intern[i]==0)
            d[i]=0;
        else
            d[i]=-Inf;
        tata[i]=0;
    }
    SortTop();

    while (!S.empty()) {
        int x=S.top();

        for (const auto& y : G[x])
            if(d[x]+y.second>d[y.first]){
                d[y.first]=d[x]+y.second;
                tata[y.first]=x;
            }
        S.pop();
    }
    int vmax=0,t=-1;
    for(int i=1; i<=n; i++)
        if(grad_extern[i]==0 && vmax<d[i]+cost[i])
        {   vmax=d[i]+cost[i];
            t=i;
        }


    for(int i=1; i<=n; i++)
        cout<<i<<" "<<d[i]<<" "<<tata[i]<<"\n";
    cout<<vmax<<"\n";
    cout<<"Activitati critice:";
    drum_critic(t);

    for(int i=1; i<=n; i++)
        cout<<"\nPunct "<<i<<": "<<d[i]<<" "<<d[i]+cost[i];
}
int main()
{
    Citire();
    Rezolva();
    return 0;
}
