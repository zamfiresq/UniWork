#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;
ifstream fin("grafpond.in");
ofstream fout("grafpond.out");

const int N = 1000, Inf=1e9;
vector<pair<int, int>> G[N];
int d[N], tata[N], nr[N];
bool in_q[N];
int n, m, s, circuit=0;

void Citire(){

    fin>>n>>m;
    for(int i=1; i<=m; i++){
        int x,y,cost;
        fin>>x>>y>>cost;
        G[x].push_back({y,cost});
    }
    fin>>s;
}

void Bellman_Ford(){
    for(int i=1; i<=n; i++){
        d[i]=Inf;
        tata[i]=0;
    }
    d[s]=tata[s]=0;
    priority_queue<int> pq;
    pq.push(s);

    while (!pq.empty()) {
        int x = pq.top();
        pq.pop();
        in_q[x]=0;

        for (const auto& muchie : G[x]) {
            int y = muchie.first;
            int cost = muchie.second;

            if (d[x]<Inf && d[x]+cost<d[y]) {
                d[y] = d[x] + cost;
                tata[y] = x;
                if(in_q[y]==0){
                    pq.push(y);
                    in_q[y]=1;
                    nr[y]++;
                    if (nr[y]>n-1){
                        circuit=y;
                        return;
                    }
                }
            }
        }
    }
}

void Lant(int x) {
    if (x == 0) {
        return;
    }
    Lant(tata[x]);
    fout<<x<<" ";
}

void Circuit(int x) {
    if(x!=s)
        Circuit(tata[x]);
    fout<<x<<" ";
}

int main()
{
    Citire();
    Bellman_Ford();
    if(circuit!=0){
        fout<<"Circuit de cost negativ:\n";
        Circuit(tata[s]);
    }
    else{
        for(int i=1; i<=n; i++)
        if(i!=s){
            fout<<"Drum: ";
            Lant(i);
            fout<<"Cost: "<<d[i]<<"\n";
        }
    }
    return 0;
}
