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

#define maxN 100011
#define dleft (p1)
#define dright (n - p2 + 1)

int n, i, p1, p2, odd, wrong, wrong2, same, mid, last;
int v[maxN];
int cnt[maxN];
ll ans;

void print_sol() {
    printf("%lld", ans);
    exit(0);
}

void dec(int pos) {
    wrong += (cnt[pos] == 0);
    wrong2 -= (cnt[pos] == 1);
    cnt[pos]--;
}

void inc(int pos) {
    wrong -= (cnt[pos] == -1);
    wrong2 += (cnt[pos] == 0);
    cnt[pos]++;
}

bool is_good() {
    return (wrong == 0) || (wrong2 == 0);
}

void add_left() {
    p1++;

    if (p1 > mid && v[p1] != v[n - p1 + 1]) print_sol(); // no way..

    dec(v[p1]);
    if (dleft - 1 < dright)
        inc(v[n - dleft + 1]);
    else
        dec(v[p1]);
}

void rm_right() {
    if (p2 == n + 1)
        print_sol(); // can't remove anymore

    inc(v[p2]);
    if (dleft < dright)
        inc(v[p2]);
    else
        dec(v[dright]);

    p2++;
}



int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]), cnt[v[i]]++;
    for (i = 1; i <= n; i++) odd += (cnt[i] & 1);
    if (odd > 1) {
        printf("0");
        return 0;
    }

    if (n == 1) {
        printf("1");
        return 0;
    }

    // set p1 = 0 and p2 = 2
    mid = (n + 1) / 2;
    p1 = 0; p2 = 2;
    memset(cnt, 0, sizeof(cnt));
    inc(v[1]);

    for (i = 2; i <= n; i++)
        dec(v[i]);

    while (!is_good())
        rm_right();

    for (last = mid; p1 <= last - 1 && v[last] == v[n - last + 1]; last--);
    while (p2 <= last) rm_right();

    ans += (n + 1) - p2 + 1;

    for (i = 1; i < n; i++) {
        add_left();

        while (p1 + 1 == p2) rm_right();

        same = min(dleft, dright);
        while (same > 0 && v[same] != v[n - same + 1])
            rm_right();

        while (!is_good())
            rm_right();

        ans += dright + 1;
    }

    print_sol();

    return 0;
}
