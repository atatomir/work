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

const int maxN = 320011;
const int inf = 1000000000;

int n, q, i, l, r;
char s[maxN];
vector<int> zero, one;
vector<ll> sum_zero, sum_one;

int busy_le, busy_ri, cnt;
int free_le;
int free_ri;

int pos_le, pos_ri;

int get_first(vector<int>& data, int bg) {
    return lower_bound(data.begin(), data.end(), bg) - data.begin();
}

int get_last(vector<int>& data, int en) {
    return upper_bound(data.begin(), data.end(), en) - data.begin() - 1;
}

ll get_sum(vector<ll>& data, int l, int r) {
    return data[r] - (l == 0 ? 0 : data[l - 1]);
}

ll get_cost(ll to_left) {
    ll to_right = cnt - to_left;
    ll ans = 0;

    if (to_left > 0) {
        ans += get_sum(sum_one, busy_le, busy_le + to_left - 1);
        ans -= get_sum(sum_zero, pos_le - to_left, pos_le - 1);
    }

    if (to_right > 0) {
        ans += get_sum(sum_zero, pos_ri + 1, pos_ri + to_right);
        ans -= get_sum(sum_one, busy_ri - to_right + 1, busy_ri);
    }

    return ans;
}

bool better_left(ll x) {
    return get_cost(x - 1) >= get_cost(x);
}

ll solve() {
    int i, j;
    int sol, limit;

    if (r - l + 1 > zero.size()) return -1;
    busy_le = get_first(one, l);
    busy_ri = get_last(one, r);

    if (busy_le > busy_ri) return 0;
    cnt = busy_ri - busy_le + 1;

    pos_le = get_first(zero, l);
    pos_ri = get_last(zero, r);

    free_le = pos_le;
    free_ri = zero.size() - pos_ri - 1;

    limit = min(free_le, cnt);
    sol = max(0, cnt - free_ri);

    for (int step = 1 << 20; step > 0; step >>= 1)
        if (sol + step <= limit)
            if (better_left(sol + step))
                sol += step;

    return get_cost(sol);
}

int main()
{
    freopen("copii3.in","r",stdin);
    freopen("copii3.out","w",stdout);

    scanf("%d%d\n%s", &n, &q, s + 1);

    for (i = 1; i <= n; i++) {
        if (s[i] == '1')
            one.pb(i);
        else
            zero.pb(i);
    }

    sum_one.resize(one.size());
    sum_zero.resize(zero.size());

    if (one.size() > 0) {
        sum_one[0] = one[0];
        for (i = 1; i < one.size(); i++)
            sum_one[i] = sum_one[i - 1] + one[i];
    }

    if (zero.size() > 0) {
        sum_zero[0] = zero[0];
        for (i = 1; i < zero.size(); i++)
            sum_zero[i] = sum_zero[i - 1] + zero[i];
    }

    for (i = 1; i <= q; i++) {
        scanf("%d%d", &l, &r);
        printf("%lld\n", solve());
    }


    return 0;
}
