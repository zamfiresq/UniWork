#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int NMAX = 100005;

int n, m;
vector<vector<int>> G(NMAX+1);
vector<vector<int>> GT(NMAX+1);
bool viz[NMAX+1];
stack<int> order;
vector<int> kingdom(NMAX+1);

void dfs1(int v) {
    viz[v]=1;
    for (int u : G[v]) {
        if (!viz[u]) {
            dfs1(u);
        }
    }
    order.push(v);
}

void dfs2(int v, int regat) {
    kingdom[v]=regat;
    for (int u : GT[v]) {
        if (kingdom[u]==-1) {
            dfs2(u, regat);
        }
    }
}

void Kosaraju() {
    fill(viz, viz+NMAX+1, false);

    //Aflam timpii finali si pastram ordinea intr-o stiva
    for (int i=1; i<=n; i++) {
        if (!viz[i]) {
            dfs1(i);
        }
    }

    //Initializam vectorul cu -1
    int regat=0;
    fill(kingdom.begin(), kingdom.begin()+n+1, -1);

    //In functie de ordine, aplicam DFS nodurilor grafului transpus in ordinea din stiva
    while (!order.empty()) {
        int v=order.top();
        order.pop();
        if (kingdom[v]==-1) {
            regat++;
            dfs2(v, regat);
        }
    }

    cout<<regat<<"\n";
    for (int i=1; i<=n; i++) {
        cout<<kingdom[i]<<" ";
    }
}

int main() {
    cin>>n>>m;

    for (int i=0; i<m; i++) {
        int x, y;
        cin>>x>>y;
        G[x].push_back(y);
        GT[y].push_back(x);
    }

    Kosaraju();
    return 0;
}
