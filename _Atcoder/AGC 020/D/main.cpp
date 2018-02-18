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

struct comb {
    ll cnt;
    ll cnt_A, cnt_B;
};

ll Q, A, B, C, D, i;
vector<comb> aux;
ll sm, bg, sz;
char s[111];

bool check(ll sacr) {
    ll rem_a = bg - sacr;
    ll grps_a = (rem_a + sz - 1) / sz;

    ll rem_b = sm - (grps_a - 1);
    ll grps_b = (rem_b + sz - 1) / sz;

    if (sacr >= grps_b - 1) return true;
    return false;
}

void build(int sacr) {
    ll rem_a = bg - sacr;
    ll grps_a = (rem_a + sz - 1) / sz;

    aux.clear();
    aux.pb({grps_a - 1, sz, 1});
    aux.pb({1, rem_a - (grps_a - 1) * sz, 0});

    ll rem_b = sm - (grps_a - 1);
    ll grps_b = (rem_b + sz - 1) / sz;

    if (rem_b == 0) return;
    aux.pb({1, 0, rem_b - (grps_b - 1) * sz});
    aux.pb({grps_b - 1, 1, sz});

    sacr -= max(0LL, grps_b - 1);
    if (sacr > 0) cerr << "Err";
}

char get(int pos) {
    for (auto e : aux) {
        if (e.cnt * (e.cnt_A + e.cnt_B) < pos) {
            pos -= e.cnt * (e.cnt_A + e.cnt_B);
            continue;
        }

        pos %= (e.cnt_A + e.cnt_B);
        if (pos == 0) pos = e.cnt_A + e.cnt_B;

        if (pos <= e.cnt_A) return 'A';
        return 'B';
    }
}

void solve() {
    ll i;

    sm = min(A, B);
    bg = max(A, B);

    sz = (bg + sm) / (sm + 1);

    ll ans = -1;
    for (ll step = 1LL << 30; step > 0; step >>= 1)
        if (ans + step <= bg)
            if (!check(ans + step))
                ans += step;

    ans++;
    build(ans);
    memset(s, 0, sizeof(s));

    if (A < B) {
        C = A + B - C + 1;
        D = A + B - D + 1;
        swap(C, D);
    }

    for (i = C; i <= D; i++) s[i - C] = get(i);

    if (A < B) {
        reverse(s, s + (D - C + 1));
        for (i = C; i <= D; i++) {
            if (s[i - C] == 'A')
                s[i - C] = 'B';
            else
                s[i - C] = 'A';
        }
    }

    printf("%s\n", s);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld", &Q);
    for (i = 1; i <= Q; i++) {
        scanf("%lld%lld%lld%lld", &A, &B, &C, &D);
        solve();
    }


    return 0;
}
