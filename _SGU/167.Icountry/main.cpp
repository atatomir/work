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
#define pii pair<int, int>

#define maxN 16 //! atentie!
#define actual_state dp[ln][bg][en][now][sm_bg][sm_en]
#define next_state dp[ln + 1][new_bg][new_en][now + new_en - new_bg + 1][new_sm_bg][new_sm_en]
#define next_prov_state prov[ln + 1][new_bg][new_en][now + new_en - new_bg + 1][new_sm_bg][new_sm_en]

int n, m, k;
int v[maxN][maxN];

int dp[maxN][maxN][maxN][maxN * maxN][2][2]; //! dp[ln][bg][en][k][smaller_bg?][smaller_en?]
int prov[maxN][maxN][maxN][maxN * maxN][2][2];

int i, j, ln, bg, en, now, sm_bg, sm_en;
int new_bg, new_en, new_sm_bg, new_sm_en;

int best;
int best_state;

vector< pii > ans;

bool is_good() {
    if (new_bg < bg && sm_bg == 1) return false;
    if (new_en > en && sm_en == 1) return false;

    if (en < new_bg || new_en < bg) return false;

    if (now + new_en - new_bg + 1 > k) return false;

    return true;
}

int compress(int ln, int bg, int en, int now, int sm_bg, int sm_en) {
    int aux = (ln << 18) + (bg << 14) + (en << 10) + (now << 2) + (sm_bg << 1) + sm_en;
    return aux;
}

void get_best(int state) {
    sm_en = state & 1;
    state >>= 1;

    sm_bg = state & 1;
    state >>= 1;

    now = state & (16 * 16 - 1);
    state >>= 8;

    en = state & 15;
    state >>= 4;

    bg = state & 15;
    state >>= 4;

    ln = state & 15;
    state >>= 4;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            scanf("%d", &v[i][j]), v[i][j] += v[i][j - 1];

    for (ln = 0; ln < n; ln++) {
        for (bg = 1; bg <= m; bg++) {
            for (en = bg; en <= m; en++) {
                for (now = 0; now <= k; now++) {
                    for (sm_bg = 0; sm_bg < 2; sm_bg++) {
                        for (sm_en = 0; sm_en < 2; sm_en++) {
                            //! configure next state

                            for (new_bg = 1; new_bg <= m; new_bg++) {
                                for (new_en = 1; new_en <= m; new_en++) {
                                    if (!is_good()) continue;

                                    new_sm_bg = sm_bg | (new_bg > bg);
                                    new_sm_en = sm_en | (new_en < en);

                                    //! .....
                                    if (next_state < actual_state + v[ln + 1][new_en] - v[ln + 1][new_bg - 1]) {
                                        next_state = actual_state + v[ln + 1][new_en] - v[ln + 1][new_bg - 1];

                                        next_prov_state = compress(ln, bg, en, now, sm_bg, sm_en);
                                    }
                                    if (next_state > best && now + new_en - new_bg + 1 == k) {
                                        best = next_state;

                                        if (next_state == 100) {
                                            best++; best--;
                                        }

                                        best_state = compress(ln + 1, new_bg, new_en, now + new_en - new_bg + 1, new_sm_bg, new_sm_en);
                                    }
                                }
                            }


                        }
                    }
                }
            }
        }
    }

    printf("Oil : %d\n", best);

    get_best(best_state);

    while (k > 0) {
        for (i = bg; i <= en; i++) ans.pb(mp(ln, i));
        k -= en - bg + 1;

        best_state = prov[ln][bg][en][now][sm_bg][sm_en];
        get_best(best_state);
    }

    sort(ans.begin(), ans.end());

    for (i = 0; i < ans.size(); i++)
        printf("%d %d\n", ans[i].first, ans[i].second);

    return 0;
}
