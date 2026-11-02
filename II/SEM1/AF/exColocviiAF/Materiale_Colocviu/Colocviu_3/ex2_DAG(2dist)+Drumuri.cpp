#include <bits/stdc++.h>
using namespace std;
ifstream fin("graf.in");
const int N = 1000, Inf=1e9;
vector<pair<int, int>> G[N];
vector<int> viz(N, 0);
vector<int> cost(N, 0), activitati_critice;
int d[N], d2[N], tata[N], tata2[N], grad_intern[N], grad_extern[N];
stack<int> S;
int n, m, s1,s2;

void Citire(){

    fin>>n>>m;
    for(int i=1; i<=m; i++){
        int x,y,cost;
        fin>>x>>y>>cost;
        G[x].push_back({y,cost});
    }
    fin>>s1>>s2;
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
        d2[i]=Inf;
        tata[i]=0;
        tata2[i]=0;
    }

    d[s1]=d2[s2]=0;

    SortTop();

    while (!S.empty()) {
        int x=S.top();
        for (const auto& y : G[x])
        {
            if(d[x]+y.second<d[y.first]){
                d[y.first]=d[x]+y.second;
                tata[y.first]=x;
            }
            if(d2[x]+y.second<d2[y.first]){
                d2[y.first]=d2[x]+y.second;
                tata2[y.first]=x;
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
    cout << x << " ";
}

int main()
{
    Citire();
    DAG();
    int vmin=Inf, v=-1;
    for(int i=1; i<=n; i++)
        if(d[i]==d2[i] && vmin>d[i]){
            vmin=d[i];
            v=i;
        }
    cout<<"a)\n";
    if(v==-1)
        cout<<"nu exista un astfel de nod";
    else{
        cout<<"v="<<v<<"\n";
        Lant(v, tata);
        cout<<"\n";
        Lant(v, tata2);
        cout<<"\n";
        for(int i=1; i<=n; i++)
            cout<<i<<" "<<tata[i]<<" "<<tata2[i]<<"\n";
        int ct=0;
        cout<<"\n\n";
        for(int x=1; x<=n; x++)
            for (auto y : G[x])
                if(y.first==v )
            {
                ct++;
                cout<<x<<" "<<d[x]<<"\n";
                //Lant(x, tata);
            }
    }

    return 0;
}
