#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>


using namespace std;


#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 633
#define mod 1000000007

int n, s, i, x;
vector<int> fixA, selA, fixB, selB;
bool us[maxN];

int ss, dd;
int ans1[maxN], ans2[maxN];
int dp[2][maxN][maxN];

void add(int& a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

void compute(vector<int> sel, vector<int> fix, int *ans) {
    int i, p1, p2, cnt_a, cnt_b, free_a, free_b;
    vector< pair<int, int> > ord;

    ord.clear();
    for (auto e : sel) ord.pb(mp(e, 1));
    for (auto e : fix) ord.pb(mp(e, 2));

    sort(ord.begin(), ord.end());

    memset(dp, 0, sizeof(dp));

    cnt_a = cnt_b = 0;
    dp[0][0][0] = 1;
    ss = 0; dd = 1;

    for (i = 0; i < ord.size(); i++) {

        memset(dp[dd], 0, sizeof(dp[dd]));

        if (ord[i].second == 1) {

            for (p1 = 0; p1 <= i; p1++) {
                for (p2 = 0; p2 <= i; p2++) {
                    if (dp[ss][p1][p2] == 0) continue;

                    free_a = cnt_a - p1 - p2;
                    free_b = cnt_b - p1 - p2;

                    add(dp[dd][p1][p2], dp[ss][p1][p2]);
                    if (free_b > 0)
                        add(dp[dd][p1 + 1][p2], (1LL * dp[ss][p1][p2] * free_b) % mod);
                }
            }

            cnt_a++;
        } else {

            for (p1 = 0; p1 <= i; p1++) {
                for (p2 = 0; p2 <= i; p2++) {
                    if (dp[ss][p1][p2] == 0) continue;

                    free_a = cnt_a - p1 - p2;
                    free_b = cnt_b - p1 - p2;

                    add(dp[dd][p1][p2], dp[ss][p1][p2]);
                    if (free_a > 0)
                        add(dp[dd][p1][p2 + 1], (1LL * dp[ss][p1][p2] * free_a) % mod);
                }
            }

            cnt_b++;
        }

        swap(ss, dd);
    }

    for (i = 1; i <= n; i++) ans[i] = 0;
    for (p1 = 0; p1 <= n; p1++) {
        for (p2 = 0; p2 <= n; p2++) {
            free_a = cnt_a - p1 - p2;
            free_b = cnt_b - p1 - p2;

            if (free_a == 0 && free_b == 0)
                add(ans[p1], dp[ss][p1][p2]);
        }
    }

}

int main() {

    freopen("pitmutare.in", "r", stdin);
    freopen("pitmutare.out", "w", stdout);

    //! read A
    cin >> n >> s;
    for (i = 1; i <= n; i++) {
        cin >> x;
        if (x == 0) continue;
        fixA.pb(x);
        us[x] = true;
    }
    for (i = 1; i <= n; i++)
        if (!us[i])
            selA.pb(i);

    //! read B
    memset(us, 0, sizeof(us));
    for (i = 1; i <= n; i++) {
        cin >> x;
        if (x == 0) continue;
        fixB.pb(x);
        us[x] = true;
    }
    for (i = 1; i <= n; i++)
        if (!us[i])
            selB.pb(i);

    //! compute
    compute(selA, fixB, ans1);

    for (auto& e: selB) e = n - e + 1;
    for (auto& e: fixA) e = n - e + 1;

    compute(selB, fixA, ans2);

    ll sol = 0;
    for (i = 0; i < s; i++)
        sol += (1LL * ans1[i] * ans2[s - i]) % mod;

    sol %= mod;
    cout << sol;



    return 0;
}
