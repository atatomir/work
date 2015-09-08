#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 511

const unsigned long long limit = 1000000000000000000;
int n,i;
char s[maxN];
vector<int> list[maxN];
unsigned long long dp[maxN][maxN]; //! count, pos
int p;
unsigned long long q;

void compute_edges() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; s[i-j] == s[i+j]; j++)
            list[i-j].pb(i+j+1);

        for (int j = 0; s[i-j-1] == s[i+j]; j++)
            list[i-j-1].pb(i+j+1);
    }

    for (i = 1; i <= n; i++) sort(list[i].begin(), list[i].end());
}

void compute_dp() {
    dp[0][n+1] = 1;

    for (int k = 1; k <= n; k++) {
        for (int i = n; i > 0; i--) {
            dp[k][i] = 0;

            for (auto edge : list[i]) {
                dp[k][i] += dp[k-1][edge];
                if (dp[k][i] >= limit) {
                    dp[k][i] = limit;
                    break;
                }
            }

        }
    }
}

void go_for(int k, int pos) {
    for (auto edge : list[pos]) {
        if (dp[k-1][edge] >= q) {

            for (int i = pos; i < edge; i++) printf("%c",s[i]);
            if (edge != n+1) printf(" ");

            go_for(k - 1, edge);
            return;
        } else {
            q -= dp[k-1][edge];
        }
    }
}

int main()
{
    freopen("ppal.in","r",stdin);
    freopen("ppal.out","w",stdout);

    scanf("%d\n%s\n",&n,s+1);
    s[0] = '@'; s[n+1] = '#';

    compute_edges();
    compute_dp();

    while ( scanf("%d%lld",&p,&q) == 2 ) {
        if (dp[p][1] < q) {
            printf("0\n");
            continue;
        }

        go_for(p,1);
        printf("\n");
    }


    return 0;
}
