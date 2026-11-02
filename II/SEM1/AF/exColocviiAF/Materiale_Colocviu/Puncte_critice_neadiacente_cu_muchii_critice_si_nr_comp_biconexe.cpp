#include <bits/stdc++.h>
using namespace std;

const int NMAX = 10000;
vector<int> G[NMAX + 1];
int viz[NMAX + 1], a[NMAX + 1], niv[NMAX + 1], low[NMAX + 1];

void dfs_noduri_critice(int nod, int tata) {
    viz[nod] = 1;
    niv[nod] = niv[tata] + 1;
    low[nod] = niv[nod];

    for (auto next : G[nod]) {
        if (viz[next] == 1) {
            if (next != tata) {
                low[nod] = min(low[nod], niv[next]);
            }
        }
        else {
            dfs_noduri_critice(next, nod);
            if (low[next] == niv[nod]) {
                a[nod] = 1;
            }
            low[nod] = min(low[nod], low[next]);
        }
    }
}

void dfs_normal(int nod_critic, int nod, int &numarComponenteBiconexe) {
    viz[nod] = 1;

    for (auto next : G[nod]) {
        if (!viz[next]) {
            if(nod == nod_critic)
                numarComponenteBiconexe++;
            dfs_normal(nod_critic, next, numarComponenteBiconexe);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        G[i].clear();
        viz[i] = 0;
        a[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (viz[i] == 0) {
            dfs_noduri_critice(i, 0);
        }
    }

    vector<int> noduri_critice_neadiacente_cu_muchii_critice;
    for (int nod = 1; nod <= n; nod++) {
        if (a[nod] == 1) {
            noduri_critice_neadiacente_cu_muchii_critice.push_back(nod);
        }
    }

    for (auto nod : noduri_critice_neadiacente_cu_muchii_critice) {
        int numarComponenteBiconexe = 0;
        fill(viz, viz + NMAX + 1, 0);
        dfs_normal(nod, nod, numarComponenteBiconexe);
        cout << "Punct critic: " << nod << ", Numar componente biconexe: " << numarComponenteBiconexe << endl;
    }

    return 0;
}