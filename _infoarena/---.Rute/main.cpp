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

const string sol[30] = {"1", "16", "1584", "463104", "299289600", "361552896000", "732443959296000", "2305449150971904000", "10654390419268829184000", "69202145783548005580800000", "610152377325314475294720000000", "7098963015274747190071787520000000", "106459726394067298796772293345280000000", "2017443502989317777418537171765166080000000", "47498845317423375939485280755676453273600000000", "1369194888259957058516432482121960109637632000000000", "47707727343353896071849199802676518699529142272000000000", "1986808065044741506792127293398293547707178657251328000000000", "97908297986853596289751162973434570005127864341000880128000000000", "5658411485682054563233513036204820116833187371988441418956800000000000", "380441882656228106136660937476084664017730632320874290048139264000000000000", "29542274203260991299306918120767179596668310809054550431828105232384000000000000", "2632048450621963385564217879506210820169223387575270215897709147079049216000000000000", "267437403978119053518224743305843162391162716848244838668177487105650805702656000000000000", "30819984888180775029796463921507687646972624079739282710699968483097884292546560000000000000000", "4007943084267744402045878905528443703537768901243237948283803695164621852568977408000000000000000000", "585405859542045525931408549908709321775271279565732510787684448127220233389546487676928000000000000000000", "95622065549579035724936789114248267922015395457399253597102677301093514221088746428140879872000000000000000000", "17397189515090537042714251158989667483872007669374448115496605746578773040131517368586035299090432000000000000000000", "3512331724090453384614741919634889864232078679806054186280835886709241795949992004105350930517249228800000000000000000000"};

#define base 1000000
#define maxData 23
#define TP int

struct Large {
    int dim;
    TP data[maxData];

    Large() {
        memset(data, 0, sizeof(data));
        dim = 1;
    }

    void operator+=(const Large& who) {
        dim = max(dim, who.dim);
        for (int i = 1; i <= dim; i++) {
            data[i] += who.data[i];
            data[i + 1] += data[i] / base;
            data[i] %= base;
        }
        if (data[dim + 1]) dim++;
    }

    void operator*=(TP x) {
        for (int i = 1; i <= dim; i++) data[i] *= x;
        for (int i = 1; i <= dim; i++) {
            data[i + 1] += data[i] / base;
            data[i] %= base;

            if (data[dim + 1]) dim++;
        }
    }

    void operator/=(TP x) {
        for (int i = dim; i > 0; i--) {
            data[i - 1] += base * (data[i] % x);
            data[i] /= x;
        }

        while (data[dim] == 0) dim--;
    }

    void print() {
        printf("%d", data[dim]);
        for (int i = dim - 1; i > 0; i--) {
            TP x = data[i];

            for (TP aux = base / 10; aux > x; printf("0"), aux /= 10);
            if (x) printf("%d", x);
        }
    }
};

#define maxN 32

int n, i, j, k, last, nxt;
Large dp[maxN][maxN][maxN][3];
Large ans;

void hardcoded() {
    n--;
    for (auto e : sol[n])
        printf("%c", e);

    exit(0);
}

int main()
{
    freopen("rute.in","r",stdin);
    freopen("rute.out","w",stdout);

    scanf("%d", &n);
    hardcoded();
    dp[1][0][0][0].data[1] = 1;

    for (i = 1; i <= n; i++) {
        for (j = 0; j <= n; j++) {
            for (k = 0; k <= n; k++) {
                for (last = 0; last < 3; last++) {

                    if (last != 0)
                        dp[i + 1][j][k][0] += dp[i][j][k][last];

                    if (last != 1)
                        dp[i][j + 1][k][1] += dp[i][j][k][last];

                    if (last != 2)
                        dp[i][j][k + 1][2] += dp[i][j][k][last];
                }
            }
        }
    }

    ans = dp[n][n][n][1];
    ans += dp[n][n][n][2];

    ans /= 2;
    for (i = 2; i <= n - 1; i++) ans *= i;
    for (i = 2; i <= n; i++) ans *= i;
    for (i = 2; i <= n; i++) ans *= i;

    ans.print();

    return 0;
}