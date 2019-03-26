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

const int maxN = 1011;
const ll inf = 1LL << 50;

int n, i, j, m;
char s[maxN];

ll mini[maxN][maxN], maxi[maxN][maxN];

bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

bool isLegal(char c) {
    return isDigit(c) || c == '+' || c == '-';
}

void solve() {
    int i, j, k;

    for (i = n; i >= 1; i--) {
        for (j = i; j <= n; j++) {
            mini[i][j] = inf;
            maxi[i][j] = -inf;
        }
        
        if (isDigit(s[i])) {
            mini[i][i] = maxi[i][i] = s[i] - '0';
            if (s[i] == '0') continue;
            for (j = i + 1; j <= n; j++) {
                if (!isDigit(s[j])) break;
                if (j - i + 1 > 9) break;
                mini[i][j] = mini[i][j - 1] * 10 + s[j] - '0';
                maxi[i][j] = mini[i][j];
            }
        } else {
            if (s[i] == '+') {
                for (j = i + 2; j <= n; j++) {
                    for (k = i + 1; k < j; k++) {
                        mini[i][j] = min(mini[i][j], mini[i + 1][k] + mini[k + 1][j]);
                        maxi[i][j] = max(maxi[i][j], maxi[i + 1][k] + maxi[k + 1][j]);
                    }
                }
            } else {
                for (j = i + 1; j <= n; j++) {
                    mini[i][j] = min(mini[i][j], -maxi[i + 1][j]);
                    maxi[i][j] = max(maxi[i][j], -mini[i + 1][j]);
                }

                for (j = i + 2; j <= n; j++) {
                    for (k = i + 1; k < j; k++) {
                        mini[i][j] = min(mini[i][j], mini[i + 1][k] - maxi[k + 1][j]);
                        maxi[i][j] = max(maxi[i][j], maxi[i + 1][k] - mini[k + 1][j]);
                    }
                }
            
            }
        }
    }

    printf("%lld %lld\n", mini[1][n], maxi[1][n]);
}

int main()
{
    //freopen("test.in","r",stdin);

    while(true) {
        s[1] = '@';
        scanf("%s\n", s + 1);
        if (!isLegal(s[1])) return 0;
        n = strlen(s + 1);

        solve();

        memset(s, 0, n + 3);
    }


    return 0;
}
