#include <iostream>
#include <vector>
#define N 1010

using namespace std;

int dx[]={0,0,-1,1};
int dy[]={-1,1,0,0};
int n,m;
bool viz[N][N];
char mat[N][N];

void DFS(int x, int y) {

    viz[x][y]=1;
    int i,nx,ny;
    for (int i=0; i<4; i++) {
        nx = x+dx[i];
        ny = y+dy[i];

        if (nx>=0 && nx<n && ny>=0 && ny<m && !viz[nx][ny] && mat[nx][ny]=='.') {
            DFS(nx, ny);
        }
    }
}

int NrCamere() {

    int cnt=0;

    //parcurgem cate un dfs pentru fiecare componenta conexa (camerele libere)
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (!viz[i][j] && mat[i][j]=='.') {
                DFS(i, j);
                cnt++;
            }
        }
    }

    return cnt;
}

int main() {

    cin>>n>>m;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin>>mat[i][j];
        }
    }

    cout<<NrCamere();

    return 0;
}
