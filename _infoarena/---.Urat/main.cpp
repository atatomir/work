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
#define maxN 500011
#define mod 543217

int n, i;
vector<int> sol;
ll fact[maxN];

void solve_brute() {
    vector<int> aux, sol;
    int i;

    pair<ll, int> ans = mp(-1, -1);
    ll act;

    aux.clear();
    for (i = 1; i <= n; i++) aux.pb(i);

    do {
        act = 0;
        for (i = 1; i < n; i++) act += abs(aux[i - 1] - aux[i]);

        if (act > ans.first) ans = mp(act, 0), sol = aux;
        if (act == ans.first) ans.second++;
    } while (next_permutation(aux.begin(), aux.end()));

    // rere

    /*aux.clear();
    for (i = 1; i <= n; i++) aux.pb(i);

    do {
        act = 0;
        for (i = 1; i < n; i++) act += abs(aux[i - 1] - aux[i]);

        if (act == ans.first) {
            for (auto e : aux) printf("%d ", e);
            printf("\n");
        }
    } while (next_permutation(aux.begin(), aux.end()));*/

    printf("%lld\n%d\n", ans.first, ans.second);
    for (auto e : sol) printf("%d ", e);
}

ll abss(ll x) {
    if (x < 0) return -x;
    return x;
}

void solve_panaete() {
    int i, mid;
    ll dif, cnt;

    if (n == 1) {
        printf("0\n1\n1\n");
        return;
    }
    if (n == 2) {
        printf("1\n2\n1 2\n");
        return;
    }
    if (n == 3) {
        printf("3\n4\n1 3 2\n");
        return;
    }

    mid = n / 2;
    sol.pb(mid);
    for (i = mid + 2; i <= n; i++) {
        sol.pb(i);
        if (i - mid - 1 != mid) sol.pb(i - mid - 1);
    }
    sol.pb(mid + 1);

    dif = 0;
    for (i = 1; i < n; i++) dif += 1LL * abs(sol[i] - sol[i - 1]);

    fact[0] = 1;
    for (i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % mod;

    if (n % 2 == 0) {
        cnt = (2LL * fact[mid - 1] * fact[mid - 1]) % mod;
    } else {
        cnt = (4LL * fact[mid] * fact[mid - 1]) % mod;
    }


    printf("%lld\n%lld\n", dif, cnt);
    for (auto e : sol) printf("%d ", e);
}

int main()
{
    freopen("urat.in","r",stdin);
    freopen("urat.out","w",stdout);

    scanf("%d", &n);
    //solve_brute();
    solve_panaete();


    return 0;
}
