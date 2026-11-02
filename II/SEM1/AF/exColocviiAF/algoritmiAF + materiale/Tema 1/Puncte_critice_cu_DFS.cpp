#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1e5;
vector<int> G[NMAX+1];
int d[NMAX+1], low[NMAX+1], cnt, sol;
int art[NMAX+1], h, vis[NMAX+1], r;

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
            if(x==r) {
                cnt++;
            } else {
                if(low[next]>=d[x]) {
                    art[x]=1;
                }
            }
        } else {
            if(next!=p) {
                low[x] = min(low[x], d[next]);
            }
        }
    }
}

int main() {
    while(true) {
        int n, m;
        cin>>n>>m;
        if(n==0 && m==0) {
            break;
        }

        for(int i=0; i<m; i++) {
            int x, y;
            cin>>x>>y;
            G[x].push_back(y);
            G[y].push_back(x);
        }

        //Radacina e 1
        r=1;
        sol=cnt=h=0;

        //Se aplica DFS pentru radacina si parintele ei 0
        dfs(r, 0);

        //Daca radacina are cel putin 2 fii in DF, ea e nod de articulatie
        if(cnt>=2) {
            art[1] = 1;
        }

        //Numaram numarul punctelor de articulatie
        for(int i=1; i<=n; i++) {
            if(art[i]==1) {
                sol++;
            }
        }
        for(int i=1; i<=n; i++) {
            G[i].clear();
            art[i]=vis[i]=d[i]=low[i]=0;
        }
        cout<<sol<<'\n';
    }
    return 0;
}
