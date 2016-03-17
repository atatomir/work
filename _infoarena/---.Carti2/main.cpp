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

#define maxN 13

int n, i, t;
int H, L, G;
int dp[1 << maxN];
int prov[1 << maxN];

int h[maxN];
int l[maxN];

int cnt_new;
int state_new, state_old;

int ans;
int ans_state;

vector<int> books;
int bits[1 << maxN];
int swapped[1 << maxN];

void solve(int pas, int act_h, int act_l) {
    if (pas == n + 1) {
        if (state_new == state_old) return; //! == 0

        int rez = state_new | state_old;
        if (dp[rez] > dp[state_old] + act_h + G) {
            dp[rez] = dp[state_old] + act_h + G;
            prov[rez] = state_new;
        }


        if (bits[rez] >= ans && dp[rez] <= H) {
            if (ans < bits[rez] || swapped[rez] > swapped[ans_state]) {
                ans = bits[rez];
                ans_state = rez;
            }
        }


        return;
    }

    //! 0
    solve(pas + 1, act_h, act_l);

    //! 1
    cnt_new++;
    state_new ^= (1 << (pas - 1));
    if ( max(act_h, h[pas]) + G + dp[state_old] <= H)
        if (act_l + l[pas] <= L)
            solve(pas + 1, max(act_h, h[pas]), act_l + l[pas]);
    state_new ^= (1 << (pas - 1));
    cnt_new--;

    //! 2
    state_old ^= (1 << (pas - 1));
        solve(pas + 1, act_h, act_l);
    state_old ^= (1 << (pas - 1));
}

void roll_back() {
    int state = ans_state;
    int sel = ans;

    while (state > 0) {
        int conf = prov[state];
        int diff = 0;

        for (int i = 0; i < n; i++)
            if (conf & (1 << i))
                books.pb(i + 1), diff++;

        state ^= conf;
        sel -= diff;
    }
}

int main()
{
    freopen("carti2.in","r",stdin);
    freopen("carti2.out","w",stdout);

    for (int state = 0; state < (1 << 12); state++)
        for (i = 0; i < 12; i++)
            if (state & (1 << i))
                bits[state]++,
                swapped[state] |= 1<< (11 - i);


    for(scanf("%d", &t); t > 0; t--) {
        scanf("%d%d%d%d", &n, &H, &L, &G);

        for (i = 1; i <= n; i++)
            scanf("%d%d", &h[i], &l[i]);


        ans = 0;
        ans_state = 0;

        for (int state = 0; state < (1 << n); state++)
            dp[state] = H + 1;
        dp[0] = 0;


        solve(1, 0, 0);

        books.clear();
        roll_back();

        sort(books.begin(), books.end());

        printf("%d\n", ans);
        for (int e : books) printf("%d ", e);
        printf("\n");
    }


    return 0;
}
