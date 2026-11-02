#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 10000;

vector<int> G_neorientat[NMAX + 1];
int G_orientat[NMAX + 1][NMAX + 1] = {0};
vector<int> viz(NMAX + 1, 0);
vector<pair<int, int> > muchii_pe_care_le_pot_scoate;
vector<int> noduri_pt_care_facem_un_nou_DFS;


void DFS(int nod) {
    viz[nod] = 1;
    for (auto next : G_neorientat[nod]) {
        if (!viz[next]) {
            DFS(next);
        }
        else {
            if(G_orientat[nod][next] == 1) {
                muchii_pe_care_le_pot_scoate.push_back(make_pair(nod, next));
            }
        }
    }
}

int main() {
    int N, M, nr_comp_conexe = 0;
    cin >> N >> M;
    for(int i = 1; i <= M; i++) {
        int x, y;
        cin >> x >> y;

        G_neorientat[x].push_back(y);
        G_neorientat[y].push_back(x);

        G_orientat[x][y] = 1;
    }

    for(int nod = 1; nod <= N; nod++) {
        if(!viz[nod]) {
            noduri_pt_care_facem_un_nou_DFS.push_back(nod);
            nr_comp_conexe++;
            DFS(nod);
        }
    }

    int nr_muchii_pe_care_le_putem_scoate = muchii_pe_care_le_pot_scoate.size();

    if(nr_muchii_pe_care_le_putem_scoate < nr_comp_conexe) {
        cout << "nu se poate";
    }
    else {
        cout << "k=" << nr_comp_conexe - 1 << endl;
        cout << "k-stergere a arcelor" << endl;
        for(int i = 0; i < nr_comp_conexe - 1; i++) {
            cout << muchii_pe_care_le_pot_scoate[i].first << " " << muchii_pe_care_le_pot_scoate[i].second << endl;
        }
        cout << "k-adaugare a arcelor" << endl;
        for(int i = 0; i < noduri_pt_care_facem_un_nou_DFS.size() - 1; i++) {
            cout << noduri_pt_care_facem_un_nou_DFS[i] << " " << noduri_pt_care_facem_un_nou_DFS[i+1] << endl;
        }
    }

    return 0;
}
