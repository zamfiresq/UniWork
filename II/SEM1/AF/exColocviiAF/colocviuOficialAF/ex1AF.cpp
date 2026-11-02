#include <iostream>
#include <vector>
#include <queue>


const int N = 1000005;
std::vector<std::vector<int> > arbore;
std::vector<bool> vizitat;
std::vector<int> parinte;
std::vector<int> descendentiComuni;
std::queue<int> coadaBFS;
int n, m, r, c1, c2;


void BFS(int r) {
    coadaBFS.push(r);
    vizitat[r] = true;

    while (!coadaBFS.empty()) {
        int nodSursa = coadaBFS.front();
        coadaBFS.pop();

        for (auto next: arbore[nodSursa]) {
            if (!vizitat[next]) {
                coadaBFS.push(next);
                parinte[next] = nodSursa;
                vizitat[next] = true;
            }
            if(parinte[next] == c1 || parinte[next] == c2){
                descendentiComuni.push_back(next);
            }
        }
    }
}


int main(){
    std::cin >> n >> m >> r >> c1 >> c2;

    arbore.resize(N);
    vizitat.resize(N, false);
    parinte.resize(N, 0);
    descendentiComuni.resize(N,0);

    for(int i = 1; i <= m; i++){
        int x, y;
        std::cin >> x >> y;
        arbore[x].push_back(y);
        arbore[y].push_back(x);
    }

    BFS(r);
    for(int i = 1; i <= n; i++)
        if(vizitat[i] == 0){
            std::cout<< 0;
            return 0;
        }

    if((parinte[c1] != parinte[c2]) || (parinte[c1] == parinte[c2])){
        std::cout << 0;
    } else {
        for(int i = 0; i < descendentiComuni.size(); i++){
            std::cout<< descendentiComuni[i]<< " ";
        }
    }

    return 0;
}