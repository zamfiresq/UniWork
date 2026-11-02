#include <iostream>
#include <vector>
#define NMAX 100005
using namespace std;

int echipa[NMAX+1];
int viz[NMAX+1];
vector<int> G[NMAX+1];

bool bipartit(int x, int dif) {
    viz[x]=1;
    echipa[x]=dif;
    for (auto next : G[x]) {
        if(echipa[next]==dif)
            return 0;
        if (echipa[next]==0&&!bipartit(next, 3-dif))
            return 0;
    }
    return 1;
}

int main()
{
    int n,m;
    cin>>n>>m;
    bool ok=1;

    for(int i=1; i<=m; i++){
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for (int i=1; i<=n; i++) {
        if (!viz[i]) {
            if (!bipartit(i,1)) {
                ok=0;
                break;
            }
        }
    }
    if(ok==0) cout<<"IMPOSSIBLE";
    else{
        for (int i=1; i<=n; i++)
            cout<<echipa[i]<<" ";
    }

    return 0;
}
