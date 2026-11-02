#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#define N 10000
using namespace std;
ifstream fin("cuvinte.in");
ofstream fout("cuvinte.out");

struct muchie{
    int x,y,cost;
};

vector<pair<int, int>> G[N];
int C[255][255], comp[N];
int n, S, k;
char cuvinte[N][255];
vector<muchie> muchii;
vector<muchie> T1;
vector<muchie> T2;


//functia pentru sort
bool compara(const muchie& m1, const muchie& m2) {
    return m1.cost < m2.cost;
}

//calculam distanta de editare dintre doua cuvinte=gradul de asemanare dintre ele
int distanta(char str1[255], char str2[255]){
    //programare dinamica
    int n1=strlen(str1), n2=strlen(str2);
    int i,j;
    //facem matricea C care contine distantele si elementele asociate operatiilor sterge/insereaza/inlocuieste
    for(i=0; i<=n1; i++)
        C[i][0]=i;
    for(j=0; j<=n2; j++)
        C[0][j]=j;
    for(i=1; i<=n1; i++)
        for(j=1; j<=n2; j++){
            if(str1[i-1]==str2[j-1])
                C[i][j]=C[i-1][j-1];
            else
                C[i][j]=1+min(min(C[i-1][j],C[i-1][j-1]),C[i][j-1]);
    }
    return C[n1][n2];
}

void graf_complet(){
    //facem un graf complet cu ponderea unei muchii=distanta dintre cuvintele asociate nodurilor din capetele muchiei
    for (int i=0; i<n; ++i) {
        for (int j=i+1; j<n; ++j) {
            int pondere=distanta(cuvinte[i], cuvinte[j]);
            G[i].push_back({j, pondere});
            G[j].push_back({i, pondere});
        }
    }
}

void Kruskal(){
    for (int i=0; i<n; ++i) {
        for (auto u: G[i]) {
            muchii.push_back({i, u.first, u.second});
        }
    }
    sort(muchii.begin(), muchii.end(), compara);
    for(int i=0; i<n; i++)
        comp[i]=i;

    int nrmsel=0;
    for (const auto& muchie : muchii) {
        int x = muchie.x;
        int y = muchie.y;
        int cost = muchie.cost;

        //daca fac parte din componente diferite, unim componentele
        if (comp[x] != comp[y]) {
            // Adaugam muchia în arbore
            T1.push_back({x,y,cost});

            int cop=comp[y];
            for(int i=0; i<n; i++) {
                if (comp[i]==cop)
                    comp[i]=comp[x];
            }
            nrmsel++;
            if(nrmsel==n-1)
                break;
        }
    }

}
void rezolva(){

    //sortam muchiile crescator in functie de ponderea lor
    sort(T1.begin(), T1.end(), compara);
    int i=1,x,y,cost;
    //facem un nou graf format din primele n-k+1 cele mai mici ca pondere muchii
    for (const auto& muchie : T1) {
        x=muchie.x;
        y=muchie.y;
        cost=muchie.cost;
        if(i<=n-k)
            T2.push_back({x,y,cost});
        else if(i==n-k+1)
            //cautam gradul de separare maxim
            S=cost;
        else
            S=min(S,cost);
        i++;
    }

    for (i=0; i<n; i++)
        comp[i] = i;

    for (const auto& muchie : T2) {
        int x = muchie.x;
        int y = muchie.y;
        int cost = muchie.cost;

        int cop = comp[y];
        if (comp[x] != comp[y])
            for(i=0; i<n; i++) {
                if (comp[i] == cop)
                    comp[i]=comp[x];
            }
    }

    int f[n+1]={0};
    for(i=0; i<n; i++)
        f[comp[i]]++;
    //afisam k-clausteringul=partitionarea gasita
    for(i=0; i<n; i++)
        if(f[i]!=0){
            for(int j=0; j<n; j++)
                if(comp[j]==i) fout<<cuvinte[j]<<" ";
            fout<<"\n";
        }
    //gradul de separare a k-claustering-ului
    fout<<S;
}
int main()
{

    int i=0;
    while(fin>>cuvinte[i])
        i++;
    n=i;
    cin>>k;
    //formam graful complet cu nodurile asociate cuvintelor
    graf_complet();
    //ii gasim un MST
    Kruskal();
    //rezolvam prin metoda prezentata la curs, mai
    rezolva();
    return 0;
}
//complexitate O(n^2 * log(n))
