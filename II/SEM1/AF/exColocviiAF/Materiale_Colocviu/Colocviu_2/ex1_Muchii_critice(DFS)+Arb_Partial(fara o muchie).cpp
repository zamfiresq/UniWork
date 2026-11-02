#include <bits/stdc++.h>
using namespace std;
fstream fin("graf.in");
const int NMAX = 1e5;
vector<int> G[NMAX+1];
vector<int> G2[NMAX+1];
vector<int> T[NMAX+1];
int d[NMAX+1], low[NMAX+1], cnt, sol;
int h, vis[NMAX+1], r;
int v;
int nod1, nod2;

bool ok;

void dfs(int x, int p) {
    vis[x] = 1;
    h++;
    d[x]=low[x]=h;
    for(auto next : G[x]) {
        if(!vis[next]) {

            //Aplicam dfs pentru fiecare nod
            dfs(next, x);
            //Calculam vectorul low pentru fiecare nod
            low[x] = min(low[x], low[next]);

            if(low[next]>d[x] && (x==v || next==x)) {
                    cout<<x<<" "<<next<<"\n";
                    cnt++;
                }
            else if(x==v || next==x)
            {
                nod1=x;
                nod2=next;
            }
        } else {
            if(next!=p) {
                low[x] = min(low[x], d[next]);
            }
        }
    }
}
void DFS2(int x){
    vis[x]=1;
    for(auto y: G2[x])
        if(vis[y]==0){
            T[x].push_back(y);
            T[y].push_back(x);
            DFS2(y);
        }
}
int main() {

    int n, m;
    fin>>n>>m;

    for(int i=0; i<m; i++) {
        int x, y;
        fin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    cin>>v;
    cnt=h=0;
    cout<<"muchii critice:\n";
    dfs(1, 0);
    if(cnt==0)
        cout<<"nu exista\n";

    if(nod1!=0&&nod2!=0)
    {
        for(int x=1; x<=n; x++){
            for(auto y: G[x])
                if((x!=nod1 || y!=nod2) && (x!=nod2 || y!=nod1))
                    G2[x].push_back(y);
        }
        for(int x=1; x<=n; x++)
            vis[x]=0;
        DFS2(1);
        cout<<"Arbore:\n";
        for(int x=1; x<=n; x++){
            cout<<x<<":";
            for(auto y: T[x])
                cout<<" "<<y;
            cout<<"\n";
        }
    }

    return 0;
}
