#include <iostream>
#include <vector>


const int NMAX = 1000, INF = 1e9;
int n, m, k, tata[NMAX + 1], h[NMAX + 1];
std::pair<int, std::pair<int, int> > muchii[NMAX];
std::vector<std::pair<std::pair<int,int>, int> > arbore;
std::vector<std::pair<int, int> >  muchiiDeScos;


void initializare()
{
    for(int i = 1; i <= n; i++)
        tata[i] = h[i] = 0;
}


int reprezentare(int nod){
    if(tata[nod] == 0)
        return nod;

    nod = reprezentare(tata[nod]);

    return nod;
}


// union
void reuniune(int x, int y){
    int r1, r2;

    r1 = reprezentare(x);
    r2 = reprezentare(y);

    if(h[r1] > h[r2])
        tata[r2] = r1;
    else
    {
        tata[r1] = r2;
        if(h[r1] == h[r2])
            h[r2] += 1;
    }
}


// functia Kruskal
void Kruskal()
{
    initializare();
    sort(muchii, muchii + m);

    for(int i = 0; i < m; i++)
    {
        int x, y, cost;

        x = muchii[i].second.first;
        y = muchii[i].second.second;
        cost = muchii[i].first;

        if (reprezentare(x) != reprezentare(y))
        {
            reuniune(x, y);

            std::pair<int, int> m = std::make_pair(x, y);
                arbore.push_back(m, cost);
        }
    }

}

// calculam costul arborelui
int calculareCostArbore(){
    int suma = 0;
    for (auto muchie : arbore)
    {
        suma += muchie.second;
    }
    return suma;
}


int main(){
    // citire date
    std::cin >> n >> m;
    for(int i = 0; i < m; i++){
        int x, y, cost;
        std::cin >> x >> y >> cost;
        muchii[i] = make_pair(cost, std::make_pair(x,y));
    }
    for(int i = 0; i < 2; i++)
    {
        int x,y;
        std::cin >>x>>y;
        muchiiDeScos.push_back(std::make_pair(x,y));
    }

    // apelare Kruskal
    Kruskal();
    int costInitial = calculareCostArbore();

    int costMinim = INF;
    int muchieScoasaIndex = -1;

    for (int i = 0; i < 2; i++)
    {
        arbore.clear();
        initializare();
        Kruskal();

        int x, y, cost;
        std::cin >> x >> y >> cost;
        x = muchiiDeScos[i].first;
        y = muchiiDeScos[i].second;
        cost = muchiiDeScos[i].second;

        if (reprezentare(x) != reprezentare(y)){
            int costNou = calculareCostArbore() + cost;
            if (costNou < costMinim)
            {
                costMinim = costNou;
                muchieScoasaIndex = i;
            }
        }
    }

    if (muchieScoasaIndex != -1)
    {
        std::pair<std::vector<int>, std::vector<int> > muchie = std::make_pair(muchiiDeScos, muchiiDeScos[muchieScoasaIndex].second);
        muchiiDeScos.push_back(muchieScoasaIndex);
    }

    for (auto muchie : arbore)
    {
        std::cout << muchie.first.first << " " << muchie.first.second << " " << muchie.second << "\n";
    }


    return 0;
}