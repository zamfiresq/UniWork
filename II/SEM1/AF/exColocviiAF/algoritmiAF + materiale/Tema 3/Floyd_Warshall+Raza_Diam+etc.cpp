#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;
ifstream fin("grafpond.in");
ofstream fout("grafpond.out");

const int N = 10000, Inf=1e9;
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
        w[x][y]=w[y][x]=cost;
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
                if(d[i][j]>(d[i][k]+d[k][j]) && i!=j && j!=k && i!=k){
                    if(d[i][k]<Inf && d[k][j]<Inf)
                            d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
                    if(d[j][k]<Inf && d[k][i]<Inf)
                            d[j][i]=min(d[j][i],d[j][k]+d[k][i]);
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
    int raza=Inf, diametru=-Inf, vmax, i, j, x=-1, y=-1, ci, cj;
    vector<int> pct_centru;

    for(i=1; i<=n; i++)
    {
        vmax=-Inf;
        for(j=1; j<=n; j++)
            if(d[i][j]>vmax){
                vmax=d[i][j];
                ci=i;
                cj=j;
            }
        if(diametru<vmax){
            diametru=vmax;
            x=ci;
            y=cj;
        }
        if(raza>vmax)
            raza=vmax;
    }
    for(i=1; i<=n; i++)
    {
        vmax=-Inf;
        for(j=1; j<=n; j++)
            if(d[i][j]>vmax)
                vmax=d[i][j];
        if(raza==vmax)
            pct_centru.push_back(i);
    }
    fout<<"Raza: "<<raza;
    fout<<"\nCentrul: ";
    for(auto x: pct_centru)
        fout<<x<<" ";
    fout<<"\nDiametrul: "<<diametru;

    fout<<"\nLant diametral: ";
    drum(x,y);

    return 0;
}
