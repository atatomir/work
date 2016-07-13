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

#define maxN 111
#define maxSG 10000

int n, x, y, i, j, k;
int sg[maxN][maxN];

vector<int> aux;
int cnt;
int used[maxSG];
int ans, big_sg;

vector< pair<int, int> > tab;

int main()
{
    freopen("joc2.in","r",stdin);
    freopen("joc2.out","w",stdout);

    aux.reserve(500);

    for (i = 1; i <= 100; i++) {
        for (j = 1; j <= 100; j++) {
            aux.clear();

            //! split in two parts
            for (k = 1; k < i; k++)
                aux.pb(sg[k][j] ^ sg[i - k][j]);

            for (k = 1; k < j; k++)
                aux.pb(sg[i][k] ^ sg[i][j - k]);

            //! remove a line / column
            for (k = 2; k < i; k++)
                aux.pb(sg[k - 1][j] ^ sg[i - k][j]);

            for (k = 2; k < j; k++)
                aux.pb(sg[i][k - 1] ^ sg[i][j - k]);

            //! remove the frame
            if (i > 2 && j > 2)
                aux.pb(sg[i - 2][j - 2]);

            //! compute actula sg number
            cnt++;
            for (auto e : aux)
                used[e] = cnt;

            for (k = 0; used[k] == cnt; k++);
            sg[i][j] = k;
        }
    }

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        tab.pb(mp(x, y));
        ans ^= sg[x][y];
    }

    if (ans == 0) {
        printf("0");
        return 0;
    }

    big_sg = ans;
    ans = 0;
    for (auto e : tab) {
        i = e.first;
        j = e.second;

        //! split in two parts
        for (k = 1; k < i; k++)
            ans += (sg[k][j] ^ sg[i - k][j] ^ big_sg) == sg[i][j];


        for (k = 1; k < j; k++)
            ans += (sg[i][k] ^ sg[i][j - k] ^ big_sg) == sg[i][j];

        //! remove a line / column
        for (k = 2; k < i; k++)
            ans += (sg[k - 1][j] ^ sg[i - k][j] ^ big_sg) == sg[i][j];

        for (k = 2; k < j; k++)
            ans += (sg[i][k - 1] ^ sg[i][j - k] ^ big_sg) == sg[i][j];

        //! remove the frame
        if (i > 2 && j > 2)
            ans += (sg[i - 2][j - 2] ^ big_sg) == sg[i][j];
    }

    printf("%d", ans);
    cerr << ans;


    return 0;
}
