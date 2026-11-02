#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 10000, INF = 1e9;
int n, m, k, B, tata[NMAX + 1], h[NMAX + 1], costmin;
vector<pair<int, pair<int, int>>> muchii;
vector<pair<int, pair<int, int>>> muchii_copie;
vector<pair<int, int>> arbore;

void Citire(){
    cin>>n>>m>>k>>B;
    for(int i=0; i<m; i++)
    {
        int x, y, cost;
        cin>>x>>y>>cost;
        muchii.push_back({cost, {x,y}});
    }

    for(int i=0; i<k; i++)
    {
        int x,y, cost;
        cin>>x>>y;
        for(auto muchie: muchii)
            if((muchie.second.first==x&&muchie.second.second==y) || (muchie.second.first==y&&muchie.second.second==x))
                muchii_copie.push_back({muchie.first, {x,y}});
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
    sort(muchii.begin(), muchii.end(), [](const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) {
        return a.first < b.first;
    });
    for(auto muchie: muchii)
        muchii_copie.push_back(muchie);

    int nrmsel=0;
    bool ok=0;

    for(auto muchie: muchii_copie)
    {
        int x, y, cost;

        x = muchie.second.first;
        y = muchie.second.second;
        cost = muchie.first;

        if (Reprez(x)!=Reprez(y))
        {
            Reuneste(x, y);
            arbore.push_back({x,y});
            costmin+=cost;

            nrmsel++;
            if(nrmsel==n-1)
                ok=1;
        }
    }

}

int main()
{
    Citire();
    Kruskal();

    if(costmin<=B){
        cout<<"Da\n";
        for(auto muchie: arbore){
            cout<<muchie.first<<" "<<muchie.second<<"\n";
        }
    }
    else{
        cout<<"Nu";
    }
    return 0;
}
