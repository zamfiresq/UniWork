#include <iostream>
#include <vector>
#include <queue>

const int N = 1000005, Inf = 1e9;

int n, m, p, tata[N], viz[N];
std::vector<std::pair<int, std::pair<int, int> > > G[N];


void citire(){

    std::cin >> n >> m >> p;
    for(int i = 1; i <= m; i++){
        int x, y, z;
        std::cin >> x >> y >> z;
        std::pair<int, int> arc (y, z);
        G[x].push_back(arc);
    }
}
int fluxIn(int nod){
    int s = 0;
    for(int i = 1; i <= n; i++)
        for (const auto& muchie : G[i])
            if(muchie.first==nod)
                s += muchie.second.second;
    return 1;
}
int fluxOut(int nod){
    int s = 0;
    for (const auto& muchie : G[nod]){
        s += muchie.second.second;
    }
    return 1;
}

bool fluxCorect()
{
    for(int i=1; i<=n; i++)
        for (const auto& muchie : G[i])
        {
            int f=muchie.second.second, c=muchie.second.first;
            if(c<0||f<0||f>c)
                return false;
        }
    for(int i = 1; i <= n; i++)
        if(i != 1 && i != n && fluxIn(i) != fluxOut(i))
            return false;
    if(fluxOut(1) != fluxIn(n))
        return false;
    return true;
}
bool construieste_st_lant_nesat_BF()
{
    for(int i = 1; i <= n; i++){
        tata[i] = viz[i] = 0;
    }
    std::queue<int> pq;
    pq.push(1);
    viz[1]=1;

    while (!pq.empty())
    {
        int x = pq.front();
        pq.pop();

        for (const auto& muchie : G[x]) {
            int y = muchie.first;
            int capacitate = muchie.second.first;
            int flux = muchie.second.second;

            if(viz[y] == 0 && capacitate-flux > 0){
                pq.push(y);
                viz[y] = 1;
                tata[y] = x;
                if(y == n)
                    return true;
            }
        }
        for(int y = 1; y <= n; y++)
            for (const auto& muchie : G[y])
                if(muchie.first == x)
                {
                    int capacitate = muchie.second.first;
                    int flux = muchie.second.second;

                    if(viz[y] == 0 && flux > 0){
                        pq.push(y);
                        viz[y] = 1;
                        tata[y] = -x;
                        if(y == n)
                            return true;
                    }
                }

    }
    return false;
}
int calc_ip(int nod) {
    if (tata[nod] == 0) {
        return Inf;
    }
    else if (tata[nod]>0){
        int x = tata[nod], y=nod;
        for (const auto& muchie : G[x])
            if(muchie.first == y){
                int c = muchie.second.first - muchie.second.second;
                return std::min(c, calc_ip(x));
            }
    }
    else if(tata[nod] < 0)
    {
        int y = -tata[nod], x = nod;
        for (const auto& muchie : G[x])
            if(muchie.first == y)
                return std::min(muchie.second.second, calc_ip(y));
    }
}


//void fluxLant(){
//    int iP = calc_ip(n);
//    int nod = n;
//    while(tata[nod] != 0)
//    {
//        if(tata[nod] > 0){
//            int x = tata[nod], y = nod;
//            for (auto& muchie : G[x])
//                if(muchie.first == y){
//                    muchie.second.second += iP;
//                }
//
//            nod = x;
//
//        }
//        else if(tata[nod] < 0){
//            int y =- tata[nod], x = nod;
//            for (auto& muchie : G[x])
//                if(muchie.first == y)
//                {
//                    muchie.second.second -= iP;
//                }
//
//            nod = y;
//        }
//
//    }
//}

void afisare(){
    if(fluxCorect() == 0)
        std::cout<<"NU";
    else
    {
        std::cout << "DA" << "\n";
        std::cout << fluxOut(1)<<"\n";
        for(int x = 1; x <= n; x++)
            for (const auto& muchie : G[x]){
                int y = muchie.first;
                int flux = muchie.second.second;
                std::cout << x <<" "<< y <<" "<< flux <<"\n";
            }
    }
}


int main(){
    citire();
    afisare();


    return 0;
}