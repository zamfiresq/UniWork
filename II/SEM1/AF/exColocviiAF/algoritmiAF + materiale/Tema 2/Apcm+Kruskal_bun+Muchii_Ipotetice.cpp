#include <bits/stdc++.h>

using namespace std;

ifstream fin("apm2.in");
ofstream fout("apm2.out");

const int NMAX = 10000, INF = 1e9;
int n, m, tata[NMAX + 1], h[NMAX + 1], q, sol[1000];
pair<int, pair<int, int>> muchii[100001];

vector<pair<int, int>> muchiiDeAdaugat;

void Citire(){
    fin>>n>>m>>q;
    for(int i=0; i<m; i++)
    {
        int x, y, cost;
        fin>>x>>y>>cost;
        muchii[i] = make_pair(cost, make_pair(x,y));
    }

    for(int i=0; i<q; i++)
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

    for(int i=0; i<q; i++)
        sol[i]=INF;
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

            for(int j=0; j<q; j++)
                if(Reprez(muchiiDeAdaugat[j].first)==Reprez(muchiiDeAdaugat[j].second)&&sol[j] == INF)
                {
                    sol[j]=cost-1;
                }
        }
    }

}

int main()
{
    Citire();
    Kruskal();

    for(int i=0; i<q; i++)
        fout<<sol[i]<<endl;

    return 0;
}
//complexitate O(m*logm)
