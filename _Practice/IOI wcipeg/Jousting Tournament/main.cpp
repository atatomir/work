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

#define maxN 200011
#define maxLog 18

int n, i, C, R;
int power[maxN];

int cnt;
int belong[maxN];
int on_l[maxN], on_r[maxN];
vector<int> list[maxN];
int aib[maxN];
vector<int> aux;

int dad[maxLog][maxN];

int best, best_pos;

int zrs(int x) {
    return (x & (x - 1)) ^ x;
}

void add(int pos, int val) {
    while (pos <= n) {
        aib[pos] += val;
        pos += zrs(pos);
    }
}

int src(int val) {
    int ans = 0;

    for (int step = 1 << 17; step; step >>= 1)
        if (ans + step <= n)
            if (aib[ans + step] < val)
                ans += step, val -= aib[ans];

    return ans + 1;
}

void build_tree() {
    int i, j, l, r;

    for (i = 1; i <= n; i++) {
        cnt++;
        on_l[i] = on_r[i] = i;
        add(i, +1);
        belong[i] = i;
    }

    for (int round = 1; round <= C; round++) {
        scanf("%d%d", &l, &r);
        l++; r++;

        aux.clear();
        cnt++;

        for (i = l; i <= r; i++) {
            aux.pb(src(i));
            dad[0][ belong[aux[i - l]] ] = cnt;
            list[cnt].pb(belong[aux[i - l]]);
        }

        on_l[cnt] = on_l[ belong[aux[0]] ];
        on_r[cnt] = on_r[ belong[aux[aux.size() - 1]] ];

        belong[aux[0]] = cnt;
        add(aux[0], +1);

        for (int e : aux)
            add(e, -1);
    }


    for (i = 1; i < maxLog; i++)
        for (j = 1; j <= cnt; j++)
            dad[i][j] = dad[i - 1][ dad[i - 1][j] ];
}

void test_position(int pos) {
    int ans = 0;
    int rez = pos;

    for (int i = maxLog - 1; i >= 0; i--) {
        if (dad[i][pos] == 0) continue;

        int l = on_l[ dad[i][pos] ];
        int r = on_r[ dad[i][pos] ];

        if (power[r - 1] - power[l - 1] == 0)
            ans += (1 << i), pos = dad[i][pos];
    }

    if (ans > best) {
        best = ans;
        best_pos = rez;
    }


    //cerr << rez << ' ' << ans << '\n';
}


int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &C, &R);
    for (i = 1; i < n; i++) {
        scanf("%d", &power[i]);
        if (power[i] > R)
            power[i] = 1 + power[i - 1];
        else
            power[i] = 0 + power[i - 1];
    }

    build_tree();

    best = -1;
    best_pos = 0;

    for (i = 1; i <= n; i++)
        test_position(i);

    test_position(74);

    printf("%d", best_pos - 1);

    return 0;
}
