#include <bits/stdc++.h>
using namespace std;

ifstream fin("retea2.in");
ofstream fout("retea2.out");

struct punct {
    long long x, y;
};
const long long INF=1e18;
//memoram in c->coordonatele centralelor, iar in b->coordonatele blocurilor de locuinte
punct c[2001], b[2001];
long long d[2001], vis[2001];
int n,m;

//distanta euclidiana
long long dist(punct a, punct b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void Citire(){
    fin >> n >> m;
    for(int i = 1; i <= n; i++) {
        fin >> c[i].x >> c[i].y;
    }
    for(int i = 1; i <= m; i++) {
        fin >> b[i].x >> b[i].y;
        d[i] = INF;
    }
}
int main() {

    //citirea datelor+initializarea costului fiecarei muchii
    Citire();

    //calculam costurile  muchiilor
    for(int i = 1; i <= m; i++) {
        long long vmin = INF;
        for(int j = 1; j <= n; j++) {
            vmin = min(vmin, dist(b[i], c[j]));
        }
        //costul muchiei i=minimul distantei euclidiene blocul i si oricare centrala
        d[i] = vmin;
    }

    //adaptam algoritmul lui Prim
    for(int i = 1; i <= m; i++) {
        long long vmin = INF;
        int pos = 0;

        //cautam muchia de cost min care nu e inca vizitata
        for(int j = 1; j <= m; j++) {
            if(!vis[j] && d[j] < vmin) {
                vmin = d[j];
                pos = j;
            }
        }

        //vizitam muchia gasita
        vis[pos] = 1;

        //actualizam costul muchiilor in cazul in care acesta este mai mare decat distanta  dintre oricare doua blocuri nevizitate
        for(int j = 1; j <= m; j++) {
            if(!vis[j] && d[j] > dist(b[pos], b[j])) {
                d[j] = dist(b[pos], b[j]);
            }
        }
    }

    //solutia=suma costurilor minime gasite
    double sol = 0;
    for(int i = 1; i <= m; i++) {
        sol += sqrt(d[i]);
    }
    fout<< fixed << setprecision(7) << sol;
    return 0;
}
//complexitate O(n+m)+O(n*m)+O(m^2)+O(m)=>O(m^2) (m>n)
