
//#...............................................................

/*
LANT
void Lant(int x, int par[]) {
    if (x == 0) {
        return;
    }
    Lant(par[x], par);
    cout << x << " ";
}

*/


//#...............................................................


/*
DFS DISTANTE PARINTE
COMPLEXITATE O(m+n) LA AMBELE (DFS+BFS)

const int NMAX = 1000, INF=1e9;
int viz[NMAX + 1],d1[NMAX+1]={INF}, d2[NMAX+1]={INF}, P1[NMAX+1], P2[NMAX+1];
int n,m,s, vmin;
vector<int> G[NMAX + 1], T1[NMAX + 1], T2[NMAX + 1];


void DFS(int x)
{
    viz[x]=1;

    for(auto y: G[x])
        if(viz[y]==0)
        {
            P2[y]=x;
            T2[x].push_back(y);
            d2[y]=d2[x]+1;
            DFS(y);
        }
}


BFS DISTANTE PARINTE


void BFS(int x){
    queue <int> q;
    q.push(x);
    viz[x]=1;
    d1[x]=0;

    while(!q.empty()){
        x=q.front();
        q.pop();
        for(auto next: G[x]){
            if(!viz[next]){
                P1[next]=x;
                q.push(next);
                viz[next]=1;
                d1[next]=d1[x]+1;
                T1[x].push_back(next);
            }
        }
    }
}

*/


//#...............................................................


/*
PUNCTE CRITICE

const int NMAX = 1e5;
vector<int> G[NMAX+1];
int d[NMAX+1], low[NMAX+1], cnt, sol;
int art[NMAX+1], h, vis[NMAX+1], r;

void dfs(int x, int p) {
    vis[x] = 1;
    h++;
    d[x]=low[x]=h;
    for(auto next : G[x]) {
        if(!vis[next]) {

            //Aplicam dfs pentru fiecare nod
            dfs(next, x);
            //Calculam vectorul low pentru fiecare nod
            low[x] = min(low[x], low[next]);
            if(x==r) {
                cnt++;
            } else {
                if(low[next]>=d[x]) {
                    art[x]=1;
                }
            }
        } else {
            if(next!=p) {
                low[x] = min(low[x], d[next]);
            }
        }
    }
}


        //Radacina e 1
        r=1;
        sol=cnt=h=0;

        //Se aplica DFS pentru radacina si parintele ei 0
        dfs(r, 0);

        //Daca radacina are cel putin 2 fii in DF, ea e nod de articulatie
        if(cnt>=2) {
            art[1] = 1;
        }

        //Numaram numarul punctelor de articulatie
        for(int i=1; i<=n; i++) {
            if(art[i]==1) {
                sol++;
            }
        }




MUCHII CRITICE

void dfs(int x, int p) {
    vis[x] = 1;
    h++;
    d[x]=low[x]=h;
    for(auto next : G[x]) {
        if(!vis[next]) {

            //Aplicam dfs pentru fiecare nod
            dfs(next, x);
            //Calculam vectorul low pentru fiecare nod
            low[x] = min(low[x], low[next]);

		//fara v daca nu trb muchii critice incidente in v
            if(low[next]>d[x] && (x==v || next==x)) {
                    cout<<x<<" "<<next<<"\n";
                    cnt++;
                }
		//fara asta daca nu avem nevoie de o muchie care nu 			//e critica in v
            else if(x==v || next==x)
            {
                nod1=x;
                nod2=next;
            }
        } else {
            if(next!=p) {
                low[x] = min(low[x], d[next]);
            }
        }
    }
}


*/


//#..............................................................


/*
KRUSKAL ARBORE APCM COST MINIM
COMPLEXITATE O(m+n)


int n, m, tata[NMAX + 1], h[NMAX + 1], sol[NMAX+1];
pair<int, pair<int, int>> muchii[NMAX], muchii_nou[NMAX];
vector<pair<pair<int,int>, int>> arbore;
vector<pair<int, int>> muchiiDeAdaugat;


void Citire(){
    fin>>n>>m;
    for(int i=0; i<m; i++){
        int x,y,cost;
        fin>>x>>y>>cost;
        muchii[i] = make_pair(cost, make_pair(x,y));
    }
    for(int i=0; i<2; i++)
    {
        int x,y;
        fin>>x>>y;
        muchiiDeAdaugat.push_back(make_pair(x,y));
    }
}

void Initializare()
{
    for(int i=1; i<=n; i++)
        tata[i]=h[i]=0;
}

int Reprez(int nod)
{
    if(tata[nod]==0)
        return nod;

    nod=Reprez(tata[nod]);

    return nod;
}

void Reuneste(int x, int y)
{
    int r1, r2;

    r1=Reprez(x);
    r2=Reprez(y);

    if(h[r1]>h[r2])
        tata[r2]=r1;
    else
    {
        tata[r1]=r2;
        if(h[r1]==h[r2])
            h[r2]+=1;
    }
}

void Kruskal()
{
    Initializare();
    sort(muchii, muchii + m);

    for(int i=0; i<m; i++)
    {
        int x, y, cost;

        x = muchii[i].second.first;
        y = muchii[i].second.second;
        cost = muchii[i].first;

        if (Reprez(x)!=Reprez(y))
        {
            Reuneste(x, y);

            //arbore.push_back({{x,y}, cost});
        }
    }

}

int CalculareCostArbore()
{
    int suma = 0;
    for (auto muchie : arbore)
    {
        suma += muchie.second;
    }
    return suma;
}



*/



//#..............................................................


/*
PRIM ARBORE APCM COST MINIM
COMPLEXITATE: O(mlogn)
daca e graf complet (sau nr muchii prea mare), e mai ok cu O(n^2)

const int Infinit = 10000000;
const int NMAX = 200000;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
vector<pair<int, int>> G[NMAX + 1];
int d[NMAX + 1], tata[NMAX + 1], viz[NMAX + 1];

ifstream f("grafpond.in");
ofstream g("prim.out");

void Prim()
{
    for (int i = 1; i <= n; i++) {
       d[i] = Infinit;
       viz[i] = 0;
   }

   d[1] = 0;
   pq.push({d[1], 1});

   int s = 0, nr_muchii = 0;

   while (!pq.empty()) {
       int x = pq.top().second;
       int cost = pq.top().first;
       pq.pop();

       if (viz[x]) {
           continue;
       }
       viz[x] = 1;
       s += cost;
       nr_muchii++;

       for (auto next : G[x]) {
           if (viz[next.first] == 0 && d[next.first] > next.second) {
               d[next.first] = next.second;
               tata[next.first] = x;
               pq.push({d[next.first], next.first});
           }
       }
   }
}



*/


//#...............................................................


/*
SORTARE TOPOLOGICA SORTTOP
GRAF ORIENTAT SI ACICLIC
COMPLEXITATE O(n+m)

int viz[NMAX + 1],vizT[NMAX+1],vizST[NMAX+1];
int C[NMAX],k,CST[NMAX],kST;
int n, m;
vector<int> G[NMAX + 1],GT[NMAX+1];
int CTC;
int Comp[NMAX+1];
int f[NMAX+1]={0};

//PARTE SORTARE
void DFSST(int x)
{
    vizST[x]=1;
    for(auto next: G[x]){
        if(!vizST[next]){
            DFSST(next);
        }
    }
    //CST[++kST]=x;
}

void SortareTopologica()
{
    int i;
    for(i=1; i<=n; i++)
        if(!vizST[i]) DFSST(i);
    //COMP TARE CONEXE
    //for(i=kST;i>=1; i--)
        //fout<<CST[i]<<" ";
}

*/



//#----------------------------------------------------------------


/*
KOSARAJU COMPONENTE TARE CONEXE
COMPLEXITATE O(m+n)


const int NMAX = 100005;

int n, m;
vector<vector<int>> G(NMAX+1);
vector<vector<int>> GT(NMAX+1);
bool viz[NMAX+1];
stack<int> order;
vector<int> kingdom(NMAX+1);

void dfs1(int v) {
    viz[v]=1;
    for (int u : G[v]) {
        if (!viz[u]) {
            dfs1(u);
        }
    }
    order.push(v);
}

void dfs2(int v, int regat) {
    kingdom[v]=regat;
    for (int u : GT[v]) {
        if (kingdom[u]==-1) {
            dfs2(u, regat);
        }
    }
}

void Kosaraju() {
    fill(viz, viz+NMAX+1, false);

    //Aflam timpii finali si pastram ordinea intr-o stiva
    for (int i=1; i<=n; i++) {
        if (!viz[i]) {
            dfs1(i);
        }
    }

    //Initializam vectorul cu -1
    int regat=0;
    fill(kingdom.begin(), kingdom.begin()+n+1, -1);

    //In functie de ordine, aplicam DFS nodurilor grafului transpus in ordinea din stiva
    while (!order.empty()) {
        int v=order.top();
        order.pop();
        if (kingdom[v]==-1) {
            regat++;
            dfs2(v, regat);
        }
    }

    cout<<regat<<"\n";
    for (int i=1; i<=n; i++) {
        cout<<kingdom[i]<<" ";
    }
}

*/


//#--------------------------------------------------------------


/*

DIJKSTRA DISTANTA MINIMA GRAF ORIENTAT ACICLIC PONDERI POZITIVE SURSA UNICA
COMPLEXITATE O(mlogn)

vector<pair<int, int>> G[N];
vector<int> viz(N, 0);
int d[N], tata[N];
int n, m, s;


void Dijkstra() {
    for(int i=1; i<=n; i++){
        d[i]=Inf;
        tata[i]=0;
    }
    d[s]=0;

    priority_queue<int> pq;
    pq.push(s);

    while (!pq.empty()) {
        int x = pq.top();
        pq.pop();
        for (const auto& muchie : G[x]) {
            int y = muchie.first;
            int cost = muchie.second;

            if (d[x] + cost < d[y]) {
                d[y] = d[x] + cost;
                pq.push(y);
                tata[y] = x;
            }
        }
    }
}


*/


//#...............................................................

/*
DAG GRAF ORIENTAT ACICLIC PONDERI POZ/NEG, DISTANTA MINIMA, SURSA UNICA
COMPLEXITATE O(m+n)

vector<pair<int, int>> G[N];
vector<int> viz(N, 0);
vector<int> cost(N, 0), activitati_critice;
int d[N], d2[N], tata[N], tata2[N], grad_intern[N], grad_extern[N];
stack<int> S;
int n, m, s1,s2;

void Citire(){

    fin>>n>>m;
    for(int i=1; i<=m; i++){
        int x,y,cost;
        fin>>x>>y>>cost;
        G[x].push_back({y,cost});
    }
    fin>>s1>>s2;
}

void DFS(int x) {
    viz[x] = 1;

    for (const auto y : G[x]) {
        if (!viz[y.first]) {
            DFS(y.first);
        }
    }

    S.push(x);
}

void SortTop() {
    for (int i=1; i<=n; ++i) {
        if (!viz[i]) {
            DFS(i);
        }
    }
}

void DAG(){
    for(int i=1; i<=n; i++)
    {
        d[i]=Inf;
        d2[i]=Inf;
        tata[i]=0;
        tata2[i]=0;
    }

    d[s1]=d2[s2]=0;

    SortTop();

    while (!S.empty()) {
        int x=S.top();
        for (const auto& y : G[x])
        {
            if(d[x]+y.second<d[y.first]){
                d[y.first]=d[x]+y.second;
                tata[y.first]=x;
            }
            if(d2[x]+y.second<d2[y.first]){
                d2[y.first]=d2[x]+y.second;
                tata2[y.first]=x;
            }
        }
        S.pop();
    }

}
*/


//#----------------------------------------------------------------

/*
BELLMAN FORD GRAF ORIENTAT CU CICLURI, DAR ACICLIC NEGATIV, PONERI NEG/POZ, DISTANTA MINIMA, SURSA UNICA
COMPLEXITATE O(n*m)

vector<pair<int, int>> G[N];
int d[N], tata[N], nr[N];
bool in_q[N];
int n, m, s, circuit=0;

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

CICLU CIRCUIT NEGATIV

void Circuit(int x) {
    if(x!=s)
        Circuit(tata[x]);
    fout<<x<<" ";
}

if(circuit!=0){
        fout<<"Circuit de cost negativ:\n";
        Circuit(tata[s]);
    }

DRUM LANT MINIM

for(int i=1; i<=n; i++)
        if(i!=s){
            fout<<"Drum: ";
            Lant(i);
            fout<<"Cost: "<<d[i]<<"\n";
        }


*/


//#----------------------------------------------------------------


/*
FLOYD WARSHALL MATRICE DISTANTE MINIME
GRAF ORIENTAT/NEORIENTAT PONDERAT NEG/POZ, CU CICLURI, DAR ACICLIC NEGATIV
COMPLEXITATE O(n^3)

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
	//VERIFICAM CIRCUIT NEGATIV DACA D[I][I]<0
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


*/


//#----------------------------------------------------------------


/*
FLUX MAXIM TAIETURA MINIMA
FORD FULKERSON EDMOND KARP
COMPLEXITATE O(n*m^2)

int n, s, t, m, tata[N], viz[N];
vector<pair<int, pair<int, int>>> G[N];
vector<pair<pair<int,int>, int>> taieturi;

void Citire(){

    fin>>n>>s>>t>>m;
    for(int i=1; i<=m; i++){
        int x,y,capacitate, flux;
        fin>>x>>y>>capacitate>>flux;
        G[x].push_back({y,{capacitate,flux}});
    }
}
int flux_de_intrare(int nod){
    int s=0;
    for(int i=1; i<=n; i++)
        for (const auto& muchie : G[i])
            if(muchie.first==nod)
                s+=muchie.second.second;
    return s;
}
int flux_de_iesire(int nod){
    int s=0;
    for (const auto& muchie : G[nod]){
        s+=muchie.second.second;
    }
    return s;
}

bool flux_corect()
{
    for(int i=1; i<=n; i++)
        for (const auto& muchie : G[i])
    {
        int f=muchie.second.second, c=muchie.second.first;
        if(c<0||f<0||f>c)
            return false;
    }
    for(int i=1; i<=n; i++)
        if(i!=s && i!=t && flux_de_intrare(i)!=flux_de_iesire(i))
            return false;
    if(flux_de_iesire(s)!=flux_de_intrare(t))
        return false;
    return true;
}
bool construieste_st_lant_nesat_BF()
{
    for(int i=1; i<=n; i++){
        tata[i]=viz[i]=0;
    }
    queue<int> pq;
    pq.push(s);
    viz[s]=1;

    while (!pq.empty())
    {
        int x = pq.front();
        pq.pop();

        for (const auto& muchie : G[x]) {
            int y = muchie.first;
            int capacitate = muchie.second.first;
            int flux = muchie.second.second;

            if(viz[y]==0 && capacitate-flux>0){
                pq.push(y);
                viz[y]=1;
                tata[y]=x;
                if(y==t)
                    return true;
            }
        }
        for(int y=1; y<=n; y++)
            for (const auto& muchie : G[y])
                if(muchie.first==x)
                {
                    int capacitate = muchie.second.first;
                    int flux = muchie.second.second;

                    if(viz[y]==0 && flux>0){
                        pq.push(y);
                        viz[y]=1;
                        tata[y]=-x;
                        if(y==t)
                            return true;
                    }
                }

    }
    return false;
}
int calc_ip(int nod) {
    if (tata[nod] == 0) {
        return Inf;
    }
    else if (tata[nod]>0){
        int x=tata[nod], y=nod;
        for (const auto& muchie : G[x])
            if(muchie.first==y){
                int c=muchie.second.first-muchie.second.second;
                return min(c, calc_ip(x));
            }
    }
    else if(tata[nod]<0)
    {
        int y=-tata[nod], x=nod;
        for (const auto& muchie : G[x])
            if(muchie.first==y)
                return min(muchie.second.second, calc_ip(y));
    }
}
void revizuieste_flux_lant(){
    int iP=calc_ip(t);
    int nod=t;
    while(tata[nod]!=0)
    {
        if(tata[nod]>0){
            int x=tata[nod], y=nod;
            for (auto& muchie : G[x])
                if(muchie.first==y){
                    muchie.second.second+=iP;
                }

            nod=x;

        }
        else if(tata[nod]<0){
            int y=-tata[nod], x=nod;
            for (auto& muchie : G[x])
                if(muchie.first==y)
                {
                    muchie.second.second-=iP;
                }

            nod=y;
        }

    }
}

void afiseaza_flux(){
    if(flux_corect()==0)
        cout<<"NU";
    else
    {
        cout<<"DA"<<"\n";
        cout<<flux_de_iesire(s)<<"\n";
        for(int x=1; x<=n; x++)
            for (const auto& muchie : G[x]){
                int y=muchie.first;
                int flux=muchie.second.second;
                cout<<x<<" "<<y<<" "<<flux<<"\n";
                if(muchie.second.first==muchie.second.second)
                    taieturi.push_back({{x,y},flux});
            }
    }
    int cap_min=0;
    for (const auto& muchie : taieturi)
        if(viz[muchie.first.first]==1)
            cap_min+=muchie.second;
    cout<<cap_min<<"\n";
    for (const auto& muchie : taieturi)
        if(viz[muchie.first.first]==1)
            cout<<muchie.first.first<<" "<<muchie.first.second<<"\n";

}
void Edmonds_Karp(){
    while(construieste_st_lant_nesat_BF())
    {
        revizuieste_flux_lant();
        for(int x=1; x<=n; x++)
            for (const auto& muchie : G[x]){
                int y=muchie.first;
                int flux=muchie.second.second;
                cout<<x<<" "<<y<<" "<<flux<<"\n";
            }
        cout<<"\n\n";
    }
    afiseaza_flux();
}

*/

//#----------------------------------------------------------------


/*
CUPLAJ MAXIM
GRAF BIPARTIT

bool bipartit(int x, int dif) {
    viz[x]=1;
    echipa[x]=dif;
    for (auto next : graf[x]) {
        if(echipa[next]==dif)
            return 0;
        if (echipa[next]==0&&!bipartit(next, 3-dif))
            return 0;
    }
    return 1;
}

bool graf_bipartit()
{
    bool ok=1;
    for (int i=1; i<=n; i++)
        if (!viz[i] && ! bipartit(i, 1))
        {
            cv=i;
            return 0;
        }

    return 1;
}
void Construieste_Graf()
{
    s=n+1;
    t=n+2;
    for(int i=1; i<=n; i++)
        if(echipa[i]==1)
            G[s].push_back({i,{1,0}});
        else
            G[i].push_back({t,{1,0}});

    for(int x=1; x<=n; x++)
        for (auto y : graf[x]){
            if(echipa[x]==1)
                G[x].push_back({y,{1,0}});
        }
    n+=2;
}

//flux pentru noul graf

bool construieste_st_lant_nesat_BF()
{
    for(int i=1; i<=n; i++){
        tata[i]=viz[i]=0;
    }
    queue<int> pq;
    pq.push(s);
    viz[s]=1;

    while (!pq.empty())
    {
        int x = pq.front();
        pq.pop();

        for (const auto& muchie : G[x]) {
            int y = muchie.first;
            int capacitate = muchie.second.first;
            int flux = muchie.second.second;

            if(viz[y]==0 && capacitate-flux>0){
                pq.push(y);
                viz[y]=1;
                tata[y]=x;
                if(y==t)
                    return true;
            }
        }
        for(int y=1; y<=n; y++)
            for (const auto& muchie : G[y])
                if(muchie.first==x)
                {
                    int capacitate = muchie.second.first;
                    int flux = muchie.second.second;

                    if(viz[y]==0 && flux>0){
                        pq.push(y);
                        viz[y]=1;
                        tata[y]=-x;
                        if(y==t)
                            return true;
                    }
                }

    }
    return false;
}
int calc_ip(int nod) {
    if (tata[nod] == 0) {
        return Inf;
    }
    else if (tata[nod]>0){
        int x=tata[nod], y=nod;
        for (const auto& muchie : G[x])
            if(muchie.first==y){
                int c=muchie.second.first-muchie.second.second;
                return min(c, calc_ip(x));
            }
    }
    else if(tata[nod]<0)
    {
        int y=-tata[nod], x=nod;
        for (const auto& muchie : G[x])
            if(muchie.first==y)
                return min(muchie.second.second, calc_ip(y));
    }
}

void revizuieste_flux_lant(){
    int iP=calc_ip(t);
    int nod=t;
    while(tata[nod]!=0)
    {
        if(tata[nod]>0){
            int x=tata[nod], y=nod;
            for (auto& muchie : G[x])
                if(muchie.first==y){
                    muchie.second.second+=iP;
                }

            nod=x;

        }
        else if(tata[nod]<0){
            int y=-tata[nod], x=nod;
            for (auto& muchie : G[x])
                if(muchie.first==y)
                {
                    muchie.second.second-=iP;
                }

            nod=y;
        }

    }
}
void afiseaza_flux()
{
    for(int i=1; i<=n-2; i++)
        for (auto muchie : G[i])
            if(muchie.second.first==muchie.second.second && muchie.first!=t)
                cout<<i<<" "<<muchie.first<<"\n";
}
void Edmonds_Karp(){
    while(construieste_st_lant_nesat_BF())
    {
        revizuieste_flux_lant();
    }
    afiseaza_flux();
}

void DFS(int nod, int start, vector<int>& cycle) {
    viz[nod] = 1;
    cycle.push_back(nod);

    for (int vecin : graf[nod]) {
        if (!viz[vecin]) {
            DFS(vecin, start, cycle);
        } else if (vecin == start && cycle.size() > 2) {
            // Am gasit un ciclu
            if(cycle.size()%2==1 && stop==0)
            {
                cout << "Ciclu: ";
                for (int nodCiclu : cycle) {
                    cout << nodCiclu << " ";
                }
                cout<<cycle[0];
                stop=1;
                return;
            }

        }
    }

    viz[nod] = 0;
    cycle.pop_back();
}

int main()
{
    Citire();

    if(graf_bipartit()==0)
    {
        cout<<"Graful nu este bipartit!\n";
        for(int i=1; i<=n; i++)
            viz[i]=0;
        DFS(cv, cv, cycle);
    }
    else{
        Construieste_Graf();
        Edmonds_Karp();

    }

    return 0;
}

*/



//#----------------------------------------------------------------


/*

TEST EULERIAN CICLU EULERIAN GRAF

vector<int> C;
vector <int> G[N];
int n,m;
int viz[N];

void Citire(){

    fin>>n>>m;
    for(int i=1; i<=m; i++){
        int x,y;
        fin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
}
void sterge_muchia(int u, int v) {
    for (int i=0; i<G[u].size(); ++i) {
        if (G[u][i] == v) {
            G[u].erase(G[u].begin() + i);
            break;
        }
    }

    for (int i = 0; i < G[v].size(); ++i) {
        if (G[v][i] == u) {
            G[v].erase(G[v].begin() + i);
            break;
        }
    }
}
void euler(int v) {
    while (!G[v].empty()) {
        int w = G[v].back();
        sterge_muchia(v, w);
        euler(w);
    }
    C.push_back(v);
}
void DFS(int x){
    viz[x]=1;
    for(auto y: G[x])
        if(viz[y]==0)
            DFS(y);
}

bool verifica_condtii()
{
    for(int i=1; i<=n; i++)
        if((G[i].size())%2!=0)
            return 0;
    for(int i=1; i<=n; i++)
        if(G[i].size()!=0)
    {
        DFS(i);
        for(int j=1; j<=n; j++)
            if(G[j].size()!=0 && viz[j]==0)
                return 0;
        return 1;
    }
    return 1;
}
int main()
{
    Citire();
    if(verifica_condtii()==0)
    {
        fout<<"Graful nu este eulerian!";
        return 0;
    }
    euler(1);
    for(auto v: C)
        fout<<v<<" ";
    return 0;
}


*/

//#----------------------------------------------------------------


/*
TEST HAMILTONIAN CICLU HAMILTONIAN GRAF MASCA

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

*/

//#----------------------------------------------------------------

    // FORD FULKERSON - COMPLEXITATE 