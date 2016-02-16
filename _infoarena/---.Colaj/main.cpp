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

#define maxN 211

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};

int n, l, h, i, j;
vector<int> xx, yy;
short smen[maxN][maxN];

int xx1[maxN], yy1[maxN], xx2[maxN], yy2[maxN];
int cnt;

void dfs(int x, int y) {
    smen[x][y] = 1;

    //cerr << xx[x - 1] << ' ' << yy[y - 1] << '\n';

    for (int i = 0; i < 4; i++) {
        int go_x = x + defX[i];
        int go_y = y + defY[i];

        if (smen[go_x][go_y] == 0)
            dfs(go_x, go_y);
    }
}

int main()
{
    freopen("colaj.in","r",stdin);
    freopen("colaj.out","w",stdout);

    scanf("%d%d%d", &n, &l, &h);

    for (i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &xx1[i], &yy1[i], &xx2[i], &yy2[i]);
        xx1[i]++; yy1[i]++;
        xx2[i]++; yy2[i]++;

        xx.pb(xx1[i]);
        xx.pb(xx2[i]);
        yy.pb(yy1[i]);
        yy.pb(yy2[i]);
    }

    xx.pb(1);
    xx.pb(l);
    xx.pb(l + 1);

    yy.pb(1);
    yy.pb(h + 1);
    yy.pb(h);

    sort(xx.begin(), xx.end());
    sort(yy.begin(), yy.end());

    xx.resize(unique(xx.begin(), xx.end()) - xx.begin());
    yy.resize(unique(yy.begin(), yy.end()) - yy.begin());
    xx.pop_back();
    yy.pop_back();

    for (i = 1; i <= n; i++) {
        xx1[i] = lower_bound(xx.begin(), xx.end(), xx1[i]) - xx.begin() + 1;
        xx2[i] = lower_bound(xx.begin(), xx.end(), xx2[i]) - xx.begin() + 1;

        yy1[i] = lower_bound(yy.begin(), yy.end(), yy1[i]) - yy.begin() + 1;
        yy2[i] = lower_bound(yy.begin(), yy.end(), yy2[i]) - yy.begin() + 1;

        smen[xx1[i]][yy1[i]]++;
        smen[xx1[i]][yy2[i]]--;
        smen[xx2[i]][yy1[i]]--;
        smen[xx2[i]][yy2[i]]++;
    }

    for (i = 1; i <= xx.size(); i++ )
        for (j = 1; j <= yy.size(); j++)
            smen[i][j] += smen[i - 1][j] + smen[i][j - 1] - smen[i - 1][j - 1];

    for (i = 0; i <= xx.size() + 1; i++)
        smen[i][0] = smen[i][ yy.size() + 1 ] = 1;

    for (i = 0; i <= yy.size() + 1; i++)
        smen[0][i] = smen[ xx.size() + 1 ][i] = 1;

    for (i = 1; i <= xx.size(); i++ )
        for (j = 1; j <= yy.size(); j++)
            if (smen[i][j] == 0) {
                //cerr << xx[i - 1] << ' ' << yy[j - 1] << '\n';
                cnt++, dfs(i, j);
            }

    printf("%d", cnt);

    return 0;
}
