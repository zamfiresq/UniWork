#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;
ifstream fin("grafpond.in");
ofstream fout("grafpond.out");

const int N = 1000, Inf=1e9;
int p[N][N], d[N][N], w[N][N];
int n, m;

void Citire(){

    fin>>n>>m;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(i!=j)
                w[i][j]=Inf;
    for(int i=1; i<=m; i++){
        int x,y,cost;
        fin>>x>>y>>cost;
        w[x][y]=cost;
    }
}

void Floyd_Warshall(){
    int i,j,k;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++){
            if (i != j)
                d[i][j] = w[i][j];
            else
                d[i][j] = 0;
            if (w[i][j] == Inf)
                p[i][j] = 0;
            else
                p[i][j] = i;
        }
    for(k=1;k<=n;k++)
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                if(d[i][j]>d[i][k]+d[k][j]&&(d[k][j]!=Inf&&d[i][k]!=Inf)){
                    d[i][j]=d[i][k]+d[k][j];
                    p[i][j]=p[k][j];
                }
}

void drum(int i,int j){
    if(i!=j)
        drum(i,p[i][j]);
    fout<<j<<" ";
}


int main()
{
    Citire();
    Floyd_Warshall();
    int x,y;
    bool ok=1;
    for(int i=1; i<=n&&ok==1; i++)
        if(d[i][i]<0){
            x=i;
            ok=0;
        }
    if(ok)
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++)
                if(d[i][j]==Inf)
                    fout<<0<<" ";
                else
                    fout<<d[i][j]<<" ";
            fout<<"\n";
        }

    else{
        fout<<"Circuit de cost negativ:\n";
        drum(x,p[x][x]);
    }
    return 0;
}
