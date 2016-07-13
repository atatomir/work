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

#define lett 19
#define states 512
#define mod 2520

ll pre[lett][states][mod];
ll ten_mod[mod];
ll pow_ten[lett];

int Q, i;
ll a, b, k;
vector<int> aux;
ll ans[states][mod];
int go[states][mod];

ll cnt[30];



void ciudat() {
    int i, j, st, act_mod, new_mod, new_st, aux;

    //! compute go
    for (st = 0; st < states; st++) {
        for (act_mod = 0; act_mod < mod; act_mod++) {
            aux = 0;

            for (i = 0; i < 9; i++) {
                if ( ( (st >> i) & 1 ) == 0 ) continue;
                if ((act_mod % (i + 1)) == 0)
                    aux++;
            }

            go[st][act_mod] = aux;
        }
    }
}

void precompute() {
    /*
     * dp[lett][state][act_mod]
     * Count of numbers with :
     * - at most lett + 1 digits
     * - (bits of states) digits used
     * - % mod == act_mod
     */

    int i, j, st, act_mod, new_mod, new_st, aux;

    //! (x * 10) % mod
    for (i = 0; i < mod; i++)
        ten_mod[i] = (i * 10) % mod;

    //! (10^x) % mod
    pow_ten[0] = 1;
    for (i = 1; i < lett; i++)
        pow_ten[i] = (pow_ten[i - 1] * 10) % mod;

    pre[0][0][0] = 1;



    for (i = 0; i + 1 < lett; i++) {
        for (st = 0; st < states; st++) {
            for (act_mod = 0; act_mod < mod; act_mod++) {

                for (j = 0; j < 10; j++) {
                    new_mod = ten_mod[act_mod] + j;
                    if (new_mod >= mod) new_mod -= mod;

                    new_st = st | (j == 0 ? 0 : 1 << (j - 1));

                    pre[i + 1][new_st][new_mod] += pre[i][st][act_mod];
                }

            }
        }
    }

}

void add_states(int dig, int bg_state, int bg_mod) {
    int i, j;

    for (i = 0; i < states; i++)
        for (j = 0; j < mod; j++)
            ans[i | bg_state][ (bg_mod + j) % mod ] += pre[dig][i][j];
}

void add_smaller(ll nr) {
    int i, n;
    int act_state, act_mod;

    aux.clear();
    nr++;

    while (nr) {
        aux.pb(nr % 10);
        nr /= 10;
    }

    reverse(aux.begin(), aux.end());
    n = aux.size();


    act_state = act_mod = 0;
    for (auto dig : aux) {

        for (i = 0; i < dig; i++)
            add_states(n - 1, act_state | (i == 0 ? 0 : 1 << (i - 1)), (act_mod + i * pow_ten[n - 1]) % mod);

        act_state |= (dig == 0 ? 0 : 1 << (dig - 1));
        act_mod = (act_mod + dig * pow_ten[n - 1]) % mod;

        n--;
    }
}

void compute(ll nr, ll ind) {
    memset(ans, 0, sizeof(ans));
    add_smaller(nr);

    for (int i = 0; i < states; i++)
        for (int j = 0; j < mod; j++)
            cnt[ go[i][j] ] += ind * ans[i][j];
}




int main()
{
    //freopen("test.in","r",stdin);

    ciudat();
    precompute();


    scanf("%d", &Q);
    for (i = 1; i <= Q; i++) {
        scanf("%lld%lld%lld", &a, &b, &k);
        memset(cnt, 0, sizeof(cnt));

        compute(b, +1);
        compute(a - 1, -1);

        ll ans = 0;
        for (int j = k; j < 10; j++)
            ans += cnt[j];

        printf("%lld\n", ans);
    }


    return 0;
}
