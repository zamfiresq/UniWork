#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
using namespace std;

ifstream fin("graf.in");
ofstream fout("graf.out");

const int N=20;
const int INF=1e9;

int n,m;
vector<pair<int,int>>G[N];
int x, y, c;
int dp[1 << 18 + 3][N];

void Citire()
{
    fin>>n>>m;
    for(int i=1; i<=m; i++) {
        fin>>x>>y>>c;
        G[y].push_back({x,c});
    }
}
int main() {
    Citire();
    for(int i=0; i <= (1 << n); i++) {
        for(int j=0; j<=n; j++) {
            dp[i][j] = INF;
        }
    }
    dp[1][0] = 0;
    for(int mask = 1; mask <= (1 << n); mask++) {
        for(int j=1; j<=n; j++) {
            if(mask & (1 << j)) {
                for(auto muchie : G[j]) {
                    if(mask & (1 << muchie.first)) {
                        dp[mask][j] = min(dp[mask][j], dp[mask - (1 << j)][muchie.first] + muchie.second);
                    }
                }
            }
        }
    }
    int sol = INF;
    for(auto muchie : G[0]) {
        sol = min(sol, dp[(1 << n) - 1][muchie.first] + muchie.second);
    }
    if(sol == INF) fout << "Nu exista solutie";
    else fout << sol;
}
