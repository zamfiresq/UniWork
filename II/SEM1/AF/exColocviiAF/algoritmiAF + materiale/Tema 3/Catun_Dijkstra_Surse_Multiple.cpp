#include<fstream>
#include<vector>
#include<queue>

using namespace std;
ifstream fin("catun.in");
ofstream fout("catun.out");

const int NMAX = 36e3 + 1;
//struct pt muchie cu vf destinatie si lg drumului
struct muchie{
    int y , c;
};

int dp[NMAX],n,m,x,y,c,f,fort,asta[NMAX];
//vector pt fortarete
bool b[NMAX];
vector <muchie> g[NMAX]; //graf

struct cmp{
    bool operator()(int a, int b){
        return dp[a]>dp[b];
    }
};

//coada de prioritati pt Dijkstra
priority_queue <int,vector<int>,cmp> pq;

void Citire()
{
    fin>>n>>m>>f;

    //citire si marcare fortarete
    for(int i=1 ; i<=f ; i++){
        fin>>fort;
        b[fort]=1;
        asta[fort]=fort;
        pq.push(fort);
    }
    //citire drumuri
    for(int i=1 ; i<=m ; i++){
        fin>>x>>y>>c;
        g[x].push_back({y,c});
        g[y].push_back({x,c});
    }
}

void Dijkstra()
{
    //initializare distante pt alg Dijkstra
    for(int i=1; i<=n;i++){
        if(!b[i]) dp[i] = 1e9; //val mare pt comp
        else dp[i] = 0;
    }

    //Dijkstra
    while(!pq.empty()){
        x = pq.top();
        pq.pop();
        for(auto it : g[x]){
            if(dp[it.y] > dp[x] + it.c ){
                dp[it.y] = dp[x] + it.c;
                asta[it.y] = asta[x];
                pq.push(it.y);
            }
            else if(dp[it.y] == (dp[x] + it.c)){
                if(asta[x] < asta[it.y]){
                    asta[it.y] = asta[x];
                    pq.push(it.y);
                }
            }
        }
    }
}
int main(){
    Citire();
    Dijkstra();
    for(int i=1 ; i<=n ; i++){
        if(!b[i]) fout<<asta[i]<<" ";
        else fout<<0<<" ";
    }

    return 0;
}
