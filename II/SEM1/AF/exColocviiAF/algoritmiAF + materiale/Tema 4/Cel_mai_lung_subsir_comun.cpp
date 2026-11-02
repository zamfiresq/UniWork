#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("lcs.in");
ofstream fout("lcs.out");

const int N = 1000;
//matricea in care stocam lungimile LCS ale subsirurilor
int mat[N][N]={0};

string lcs(const string& s1, const string& s2) {
    int n = s1.length();
    int m = s2.length();

    // Construim matricea mat pentru a calcula lungimile LCS
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            if (s1[i-1] == s2[j-1]) {
                mat[i][j] = mat[i-1][j-1] + 1;
            } else {
                mat[i][j] = max(mat[i-1][j], mat[i][j-1]);
            }
        }
    }

    // Reconstruim subsirul comun
    int i=n, j=m;
    string subsir = "";
    while (i>0 && j>0) {
        if (s1[i-1] == s2[j-1]) {
            subsir = s1[i-1] + subsir;
            i--;
            j--;
        } else if (mat[i-1][j] > mat[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }

    return subsir;
}

int main() {
    string s1, s2;
    fin>>s1>>s2;

    fout<<lcs(s1, s2);

    return 0;
}
