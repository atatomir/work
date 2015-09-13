#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 20
#define maxM 75

int t, i, j, n, m, val;
char work[maxN][maxM];
int posX, posY;

vector< pair<int, int> > useful;

int main()
{
    freopen("nop.in","r",stdin);
    freopen("nop.out","w",stdout);

    n = 16; m = 70;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            work[i][j] = '0';

    work[1][1] = '1';
    posX = 1; posY = 2;
    useful.pb(mp(1, 1));

    for (i = 2; i <= 26; i += 2) {
        work[posX][posY] = '1';

        for (int ii = posX; ii <= posX+1; ii++) {
            work[ii][posY + 1] = work[ii][posY + 2] = work[ii][posY + 3] = work[ii][posY + 4] = '1';
        }

        useful.pb(mp(posX + 1, posY + 2));
        useful.pb(mp(posX + 1, posY + 4));

        posX++;
        posY+=5;
    }

    for (auto e : useful)
        for (; e.first <= n; e.first++) work[e.first][e.second] = '1';

    for (j = 1; j <= m; j++) work[n][j] = '1';
    for (j = 1; j <= m; j++) work[n-1][j] = '0';


    for (scanf("%d", &t); t > 0; t--) {
        for (j = 1; j <= m; j++) work[n-1][j] = '0';

        scanf("%d", &val);
        for (int bit = 0; bit < useful.size(); bit++) {
            if (val % 2 == 1)
                work[n-1][ useful[bit].second ] = '1';

            val >>= 1;
        }

        printf("%d %d\n", n, m);
        for (i = 1; i <= n; i++) printf("%s\n", work[i] + 1);
    }

    return 0;
}
