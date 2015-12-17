#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

int n, i, x, pos, ans;
int Elsie[maxN];
bool us[maxN];
int Bessie[maxN];

int dp_l[maxN], dp_r[maxN];;
vector<int> e_sort;

int my_pair[maxN];
int smen[maxN];

int aib[maxN];

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

int update(int pos, int v) {
    while (pos <= 2 * n) {
        aib[pos] += v;
        pos += zrs(pos);
    }
}

int sum(int pos) {
    int ans = 0;
    while (pos > 0) {
        ans += aib[pos];
        pos -= zrs(pos);
    }

    return ans;
}

int cb(int val) {
    int ans = 0;
    for (int step = 1 << 20; step > 0; step >>= 1) {
        if (ans + step <= 2 * n)
            if (val >= aib[ans + step]) {
                val -= aib[ans + step];
                ans += step;
            }
    }

    return ans;
}

int smen_left(int pos) {
    int val = sum(pos);

    if (val == 0)
        return 0;

    return cb(val - 1) + 1;
}

int smen_right(int pos) {
    int val = sum(pos);

    if (val == sum(2 * n))
        return 2 * n + 1;

    return cb(val) + 1;
}

void solve_left() {
    int i;
    memset(my_pair, 0, sizeof(my_pair));

    for (i = 1; i <= 2 * n; i++)
        smen[i] = i;
    for (i = 1; i <= n; i++)
        smen[ Bessie[i] ] = Bessie[i] - 1;

    memset(aib, 0, sizeof(aib));
    for (i = 1; i <= 2 * n; i++)
        if (smen[i] == i)
            update(i, +1);


    for (i = n; i > 0; i--) {
        int wh = smen_left( Bessie[i] );
        if (wh == 0) break;

        my_pair[wh] = Bessie[i];
        update(wh, -1);
        dp_l[n]++;
    }


    for (i = n - 1; i > 0; i--) {
        int elsie_val = Elsie[i + 1];

        if (my_pair[ elsie_val ] == 0) {
            dp_l[i] = dp_l[i + 1];
            update(elsie_val, -1);
            continue;
        }

        dp_l[i] = dp_l[i + 1] - 1;

        int daddy = my_pair[ elsie_val ];

        int wh = smen_left( daddy );
        if (wh == 0) continue;

        my_pair[wh] = daddy;
        update(wh, -1);
        dp_l[i]++;
    }
}

void solve_right() {
    int i;
    memset(my_pair, 0, sizeof(my_pair));
    smen[2 * n + 1] = 2 * n + 1;

    for (i = 1; i <= 2 * n; i++)
        smen[i] = i;
    for (i = 1; i <= n; i++)
        smen[ Bessie[i] ] = Bessie[i] - 1;

    memset(aib, 0, sizeof(aib));
    for (i = 1; i <= 2 * n; i++)
        if (smen[i] == i)
            update(i, +1);

    for (i = 1; i <= n; i++) {
        int wh = smen_right( Bessie[i] );
        if (wh == 2 * n + 1) break;

        my_pair[wh] = Bessie[i];
        update(wh, -1);
        dp_r[1]++;
    }

    for (i = 2; i <= n; i++) {
        int elsie_val = Elsie[i - 1];

        if (my_pair[ elsie_val ] == 0) {
            dp_r[i] = dp_r[i - 1];
            update(elsie_val, -1);
            continue;
        }

        dp_r[i] = dp_r[i - 1] - 1;

        int daddy = my_pair[ elsie_val ];

        int wh = smen_right( daddy );
        if (wh == 2 * n + 1) continue;;

        my_pair[wh] = daddy;
        update(wh, -1);
        dp_r[i]++;
    }
}

int main()
{
    freopen("cardgame.in","r",stdin);
    freopen("cardgame.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &Elsie[i]);
        us[ Elsie[i] ] = true;
        e_sort.pb(Elsie[i]);
    }

    sort(e_sort.begin(), e_sort.end());

    for (i = 1; i <= 2 * n; i++)
        if (!us[i])
            Bessie[++pos] = i;

    solve_left();
    solve_right();
    for (i = 0; i <= n; i++)
        ans = max(ans, dp_l[i] + dp_r[i + 1]);

    printf("%d", min(ans, n));

    return 0;
}
