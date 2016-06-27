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

#define maxN 100011
#define inf 2000000000

int N, n, m, k, i, j;
pair<int, int> P[maxN];
vector<int> xx, yy;

ll ans[maxN];

vector< vector< int > > mat;


void put(int x, int y, int v) {
    x = lower_bound(xx.begin(), xx.end(), x) - xx.begin();
    y = lower_bound(yy.begin(), yy.end(), y) - yy.begin();

    mat[x][y] += v;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &k);

    for (i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].first, &P[i].second);
        xx.pb(P[i].first);
        xx.pb(P[i].first + k);

        yy.pb(P[i].second);
        yy.pb(P[i].second + k);
    }

    sort(xx.begin(), xx.end());
    xx.resize(unique(xx.begin(), xx.end()) - xx.begin());

    sort(yy.begin(), yy.end());
    yy.resize(unique(yy.begin(), yy.end()) - yy.begin());

    mat = vector< vector<int> >(xx.size() + 3, vector<int>(yy.size() + 3, 0));
    for (i = 1; i <= n; i++) {
        put(P[i].first, P[i].second, +1);
        put(P[i].first + k, P[i].second, -1);
        put(P[i].first, P[i].second + k, -1);
        put(P[i].first + k, P[i].second + k, +1);
    }

    N = n;
    n = xx.size();
    m = yy.size();

    for (i = 1; i < n; i++) mat[i][0] += mat[i - 1][0];
    for (i = 1; i <= m; i++) mat[0][i] += mat[0][i - 1];

    for (i = 1; i < n; i++)
        for (j = 1; j < m; j++)
            mat[i][j] += mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1];

    n--; m--;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            ans[ mat[i][j] ] += 1LL * (xx[i + 1] - xx[i]) * (yy[j + 1] - yy[j]);


    for (i = 1; i <= N; i++) printf("%lld ", ans[i]);

    return 0;
}
