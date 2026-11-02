#include <iostream>
#include <vector>
#include <set>
#include <limits>

using namespace std;

const int NMAX = 1e4;
const int INF = 1e9;

int d[NMAX + 1];
bool vis[NMAX + 1];
vector<pair<int, int>> G[NMAX + 1];

void Initializeaza(int n) {
    for (int i = 1; i <= n; i++) {
        d[i] = INF;
        vis[i] = false;
    }
}

void StatiiInitiale(int k, set<pair<int, int>>& s) {
    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        //marcam in vectorul d cele k statii initiale si costul 0 asociat fiecareia
        d[x] = 0;
        s.insert(make_pair(0, x));
    }
}

void CreeazaGraf(int m) {
    for (int i = 1; i <= m; i++) {
        int x, y, cost;
        cin>>x>>y>>cost;
        G[x].push_back(make_pair(y, cost));
        G[y].push_back(make_pair(x, cost));
    }
}

long long Rezolva(set<pair<int, int>>& s, int n, int L, int k) {
    long long sol = 0;

    //pentru fiecare statie initiala
    while (!s.empty()) {
        //parcurgem statiile initiale si le memoram pe rand in variabila it
        set<pair<int, int>>::iterator it = s.begin();
        s.erase(it);


        int cost = (*it).first;
        int node = (*it).second;

        //executam algoritmul doar pentru statiile initiale nevizitate
        if (vis[node]) {
            continue;
        }

        //le vizitam
        vis[node] = true;

        //facem costul de tip long long
        sol += 1LL * cost;

        //actualizam distantele în functie de costurile minime gasite
        for (vector<pair<int, int>>::iterator next = G[node].begin(); next != G[node].end(); ++next) {
            if (d[(*next).first] > (*next).second)
            {
                d[(*next).first] = (*next).second;
                s.insert(make_pair(d[(*next).first], (*next).first));
            }
        }
    }

    //golim/pregatim graful pentru urmatoaroarele seturi de date
    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }

    //se adauga costul pentru a ajunge la celelalte noduri
    sol += 1LL * (n - k) * L;
    return sol;
}

int main() {
    int t;
    cin >> t;

    //pentru fiecare test, executam:
    while (t--) {
        int n, m, L, k;
        cin>>n>>m>>L>>k;
        //cream multimea s care va contine statiile initiale
        set<pair<int, int>> s;

        //initializam vectorii d si viz
        Initializeaza(n);

        //memoram cele k statii initiale si le marcam in vectorul d
        StatiiInitiale(k, s);

        //cream graful cu cele m muchii date si ponderile asociate lor
        CreeazaGraf(m);

        //adaptam algoritmul lui Prim pentru a gasi cel mai scurt drum
        long long result = Rezolva(s, n, L, k);

        cout<<result<<'\n';
    }

    return 0;
}
//complexitate O(T*(n+n^2))=>O(T*n^2)
