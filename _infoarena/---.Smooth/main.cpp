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

const int maxN = 100011;
const int sigma = 26;

int n, i, j, p;
char s[maxN];
int id[sigma + 11];
int ans;

int bonus[sigma + 11];
int sum[sigma + 11][sigma + 11];

bool aux[sigma + 11];

void prep_batch(int sz) {
    int i, j, act;

    for (i = 1; i <= n; i += sz) {

        for (j = 0; j < sz && i + j <= n; j++) {
            act = id[s[i + j] - 'a'];

            if (aux[act]) {
                bonus[sz]++;
            } else {
                aux[act] = true;
                sum[sz][act]++;
            }
        }

        for (j = 0; j < sz && i + j <= n; j++) {
            act = id[s[i + j] - 'a'];
            aux[act] = false;
        }
    }

    sort(sum[sz] + 1, sum[sz] + p + 1);
    for (i = 1; i <= p; i++) sum[sz][i] += sum[sz][i - 1];
}

void solve() {
    int ini, rm, ad, sz;

    ini = p;
    for (rm = 0; rm <= ini; rm++) {
        for (ad = 0; ini + ad <= sigma; ad++) {
            sz = ini - rm + ad;
            if (sz == 0) continue;

            ans = min(ans, bonus[sz] + sum[sz][rm]);
        }
    }
}

int main()
{
    freopen("smooth2.in", "r", stdin);
    freopen("smooth2.out", "w", stdout);

    scanf("%s", s + 1);
    n = strlen(s + 1);
    ans = n;

    for (i = 1; i <= n; i++) {
        if (id[s[i] - 'a'] != 0) continue;
        id[s[i] - 'a'] = ++p;
    }

    for (i = 1; i <= sigma; i++) prep_batch(i);
    solve();

    printf("%d", ans);

    return 0;
}
