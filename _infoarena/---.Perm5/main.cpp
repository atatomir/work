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

#define maxN 2016
#define maxDiv 311

int n, i, j;
bool ciur[maxN];
vector<int> divs;

double dp[maxN][maxDiv];
pair<int, int> prov[maxN][maxDiv];

int best_pos, best_div;
vector<int> recons;
int pas;

int main()
{
    freopen("perm5.in","r",stdin);
    freopen("perm5.out","w",stdout);

    scanf("%d", &n);
    divs.pb(1);
    for (i = 2; i <= n; i++) {
        if (ciur[i]) continue;
        divs.pb(i);

        for (j = i * i; j <= n; j += i)
            ciur[j] = true;
    }

    dp[0][0] = log(1.00);

    best_pos = 1;
    best_div = 0;

    for (i = 1; i <= n; i++) {
        for (j = 0; j < (int)divs.size(); j++) {
            if (i - divs[j] < 0) {
                dp[i][j] = dp[i][j - 1];
                prov[i][j] = prov[i][j - 1];
                continue;
            }

            dp[i][j] = log(1.00);
            prov[i][j] = mp(i - 1, 0);

            if (j == 0) continue;

            dp[i][j] = dp[i][j - 1];
            prov[i][j] = prov[i][j - 1];

            int aux = divs[j];
            while (aux <= i) {
                double now = dp[i - aux][j - 1] + log(aux);

                if (now > dp[i][j]) {
                    dp[i][j] = now;
                    prov[i][j] = mp(i - aux, j - 1);
                }

                aux *= divs[j];
            }

            if (dp[i][j] > dp[best_pos][best_div]) {
                best_pos = i;
                best_div = j;
            }
        }
    }

    for (i = 1; i <= n - best_pos; i++) printf("%d ", i);
    pas = n - best_pos;

    while (best_pos) {
        recons.pb( best_pos - prov[best_pos][best_div].first );

        pair<int, int> aux = prov[best_pos][best_div];

        best_pos = aux.first;
        best_div = aux.second;
    }

    sort(recons.begin(), recons.end());
    reverse(recons.begin(), recons.end());

    while (recons.empty() == false) {
        int dim = recons[ recons.size() - 1 ];
        recons.pop_back();

        for (j = 2; j <= dim; j++) printf("%d ", pas + j);
        printf("%d ", pas + 1);

        pas += dim;
    }


    return 0;
}
