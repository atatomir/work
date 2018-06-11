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

const int maxN = 22;


int n, m, i, j;
char mat[maxN][maxN];
int v[maxN][maxN];
vector<int> p;
int ans;

bool check() {
    int i, j, act;

    for (i = 1; i <= n; i++) {
        act = 0;
        for (j = 0; j < m; j++)  {
            act += v[i][p[j]];
            if (act < 0) return false;
        }
    }
    return true;
}

int main()
{
    freopen("karma.in","r",stdin);
    freopen("karma.ok","w",stdout);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", mat[i]);
        for (j = 0; j < m; j++) {
            if (mat[i][j] == '(')
                v[i][j] = 1;
            else
                v[i][j] = -1;
        }
    }

    for (i = 0; i < m; i++) p.pb(i);
    do {
        if (check()) ans++;
    } while(next_permutation(p.begin(), p.end()));

    printf("%d", ans);



    return 0;
}
