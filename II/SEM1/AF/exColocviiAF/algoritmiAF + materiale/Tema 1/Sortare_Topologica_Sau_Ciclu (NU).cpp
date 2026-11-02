#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int NMAX = 100000;
int vis1[NMAX + 1], vis2[NMAX+1], P[NMAX + 1], s, d, cycle;
int C[NMAX],k;
int n, m;
vector<int> lantmax;
vector<int> G[NMAX + 1];

void DFS(int x, int y){
    vis1[x]=1;
    for(auto next: G[x]){
        if(!vis1[next]){
            P[next]=x;
            DFS(next,x);
        }
        else {
            if(next!=y){
                cycle=1;
                s=x;
                d=next;
            }
        }
    }
}

void DFSST(int x)
{
    vis2[x]=1;
    for(auto next: G[x]){
        if(!vis2[next]){
            DFSST(next);
        }
    }
    C[++k]=x;
}
void SortareTopologica()
{
    int i;
    for(i=1; i<=n; i++)
        if(!vis2[i]) DFSST(i);
    for(i=k;i>=1; i--)
        cout<<C[i]<<" ";
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
    }
    DFS(1, 0);

    if (cycle) {
        cout<<"IMPOSSIBLE";
        vector <int> sol;
        while(d!=s){
            sol.push_back(d);
            d=P[d];
        }
        sol.push_back(s);
        reverse(sol.begin(),sol.end());
        sol.push_back(s);
        for(auto x: sol)
            cout<<x<<" ";
    }
    else {
        SortareTopologica();
    }

    return 0;
}
