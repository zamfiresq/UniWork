#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int NMAX=100005;
int tata[NMAX];
vector<int> viz; //tinem evidenta muchiilor selectate in primul MST
int edg;
int n,m;

struct muchie {
    int x, y, cost;
} muchii[NMAX];

void Citire(){
    cin>>n>>m;
    int x,y,cost;
    for (int i=0; i<m; i++) {
        cin>>x>>y>>cost;
        muchii[i].x = x;
        muchii[i].y = y;
        muchii[i].cost = cost;
    }
}
bool cmp(muchie x, muchie y)
{
    return x.cost<y.cost;
}

void Initializare(int n)
{
    for (int i = 1; i <= n; i++)
        tata[i] = i;
}

int Reprez(int x)
{
    if (tata[x]==x)
        return x;
    return tata[x]=Reprez(tata[x]);
}

int union1(int i, int sum)
{
    int x, y;
    x=Reprez(muchii[i].x);
    y=Reprez(muchii[i].y);
    if (x!=y) {
        tata[x]=y;
        viz.push_back(i);
        sum+=muchii[i].cost;
    }
    return sum;
}

int union2(int i, int sum)
{
    int x, y;
    x=Reprez(muchii[i].x);
    y=Reprez(muchii[i].y);
    if (x!=y) {
        tata[x]=y;
        sum+=muchii[i].cost;
        edg++;
    }
    return sum;
}

//se aplica algoritmul lui Kruskal pentru a gasi primul arbore partial de cost minim
void MST1(){
    Initializare(n);

    sort(muchii, muchii+m, cmp);

    int sum = 0;
    for (int i=0; i<m; i++) {
        sum=union1(i, sum);
    }

    cout<<sum<<" ";
}

//se aplica algoritmul lui Kruskal pentru  a gasi cel de-al doilea arbore partial de cost minim
//ideea: aplicam kruskal pentru graful obtinut prin eliminarea pe rand a cate o muchie luata in primul MST
//apoi retinem minimul costului asociat fiecarui astfel de mst gasit
void MST2(){
    int sec_best_mst=NMAX;

    int sum = 0;
    int j;
    //in cazul cel mai rau, lungimea vectorului=m
    for (j=0; j<viz.size(); j++) {
        Initializare(n);
        edg=0;
        for (int i=0; i<m; i++) {
            if (i==viz[j])
                continue;
            //in cel mai rau caz, m operatii de unire=> O(m^2 logn)
            sum=union2(i, sum);
        }
        if (edg!=n-1) {
            sum=0;
            continue;
        }

        if (sec_best_mst>sum)
            sec_best_mst=sum;
        sum=0;
    }

    cout<<sec_best_mst;
}
int main()
{
    Citire();
    MST1();
    MST2();
    return 0;
}
//complexitate O(mlogm+mlogn+m^2 * logn)=> O(m^2 * log m)
