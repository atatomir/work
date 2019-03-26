#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 101;

ll k, ini;
int n, m, px, py;
char ans[maxN][maxN];

int main()
{
    scanf("%lld", &k);
    ini = k;

    for (int i = 0; i < maxN; i++)
        for (int j = 0; j < maxN; j++)
            ans[i][j] = '.';

    px = py = 1;
    while (k >= 6) {
        ans[px][py] = 'X';
        ans[px + 1][py] = 'X';
        ans[px + 1][py + 1] = 'X';
        ans[px][py + 1] = 'X';

        ans[px][py + 2] = 'd';
        ans[px + 1][py + 2] = 'd';
        ans[px + 2][py + 2] = 'd';
        
        ans[px + 2][py] = 'r';
        ans[px + 2][py + 1] = 'r';
        
        int modo = k % 6;
        switch (modo) {
            case 0: break;
            case 1: ans[px + 2][py] = 'X';
                    break;
            case 2: ans[px + 2][py] = 'X';
                    ans[px][py + 2] = 'X';
                    break;
            case 3: ans[px + 2][py + 1] = 'X';
                    break;
            case 4: ans[px + 2][py] = 'X';
                    ans[px + 2][py + 1] = 'X';
                    break;
            case 5: ans[px + 2][py] = 'X';
                    ans[px + 2][py + 1] = 'X';
                    ans[px][py + 2] = 'X';
        }

        k /= 6;
        px += 2; py += 2;
    }

    switch (k) {
        case 1: ans[px][py] = 'd';
                break;
        case 2: ans[px][py] = 'X';
                ans[px + 1][py] = 'r';
                ans[px][py + 1] = 'd';
                ans[px + 1][py + 1] = 'd';
                break;
        case 3: ans[px][py] = 'X';
                ans[px + 1][py] = 'X';
                ans[px][py + 1] = 'd';
                ans[px + 1][py + 1] = 'd';
                break;
        case 4: ans[px][py] = 'X';
                ans[px][py + 1] = 'X';
                ans[px + 1][py] = 'X';
                ans[px + 1][py + 1] = 'r';
                ans[px][py + 2] = 'd';
                ans[px + 1][py + 2] = 'd';
                break;
        case 5: ans[px][py] = 'X';
                ans[px][py + 1] = 'X';
                ans[px + 1][py] = 'r';
                ans[px + 1][py + 1] = 'X';
                ans[px][py + 2] = 'd';
                ans[px + 1][py + 2] = 'd';
                break;
    }

    px++;
    py += 2;

    n = px + 1;
    m = py + 1;

    if (ini <= 19) {
        n = min(n, 5);
        m = min(m, 5);
    }

    n = min(n, 49);
    m = min(m, 49);

    for (int i = 1; i < n; i++) ans[i][m] = 'd';
    for (int i = 1; i < m; i++) ans[n][i] = 'r';

    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; i++) {
        ans[i][m + 1] = '\0';
        printf("%s\n", ans[i] + 1);
    }


    return 0;
}
