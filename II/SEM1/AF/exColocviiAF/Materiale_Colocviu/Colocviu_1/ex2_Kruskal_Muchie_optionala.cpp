#include <bits/stdc++.h>

using namespace std;

ifstream fin("graf.in");

const int NMAX = 10000, INF = 1e9;
int n, m, tata[NMAX + 1], h[NMAX + 1], sol[NMAX+1];
pair<int, pair<int, int>> muchii[NMAX], muchii_nou[NMAX];
vector<pair<pair<int,int>, int>> arbore;
vector<pair<int, int>> muchiiDeAdaugat;

void Citire(){
    fin>>n>>m;
    for(int i=0; i<m; i++){
        int x,y,cost;
        fin>>x>>y>>cost;
        muchii[i] = make_pair(cost, make_pair(x,y));
    }
    for(int i=0; i<2; i++)
    {
        int x,y;
        fin>>x>>y;
        muchiiDeAdaugat.push_back(make_pair(x,y));
    }
}

void Initializare()
{
    for(int i=1; i<=n; i++)
        tata[i]=h[i]=0;
}

int Reprez(int nod)
{
    if(tata[nod]==0)
        return nod;

    nod=Reprez(tata[nod]);

    return nod;
}

void Reuneste(int x, int y)
{
    int r1, r2;

    r1=Reprez(x);
    r2=Reprez(y);

    if(h[r1]>h[r2])
        tata[r2]=r1;
    else
    {
        tata[r1]=r2;
        if(h[r1]==h[r2])
            h[r2]+=1;
    }
}

void Kruskal()
{
    Initializare();
    sort(muchii, muchii + m);

    for(int i=0; i<m; i++)
    {
        int x, y, cost;

        x = muchii[i].second.first;
        y = muchii[i].second.second;
        cost = muchii[i].first;

        if (Reprez(x)!=Reprez(y))
        {
            Reuneste(x, y);

            arbore.push_back({{x,y}, cost});
        }
    }

}

int CalculareCostArbore()
{
    int suma = 0;
    for (auto muchie : arbore)
    {
        suma += muchie.second;
    }
    return suma;
}

int main()
{
    Citire();
    Kruskal();
    int costInitial = CalculareCostArbore();
    cout << "a)\n" << costInitial << "\n";

    int costMinim = INF;
    int muchieAdaugataIndex = -1;

    for (int i = 0; i < 2; i++)
    {
        arbore.clear();
        Initializare();
        Kruskal();

        int x, y, cost;
        fin>>x>>y>>cost;
        x = muchiiDeAdaugat[i].first;
        y = muchiiDeAdaugat[i].second;
        cost = muchiiDeAdaugat[i].second;

        if (Reprez(x) != Reprez(y))
        {
            int costNou = CalculareCostArbore() + cost;
            if (costNou < costMinim)
            {
                costMinim = costNou;
                muchieAdaugataIndex = i;
            }
        }
    }

    if (muchieAdaugataIndex != -1)
    {
        arbore.push_back({muchiiDeAdaugat[muchieAdaugataIndex], muchiiDeAdaugat[muchieAdaugataIndex].second});
    }

    cout << "b)\n";
    for (auto muchie : arbore)
    {
        cout << muchie.first.first << " " << muchie.first.second << " " << muchie.second << "\n";
    }
    return 0;
}
