#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000011
#define inf 1e85
#define eps 1e-9

int n, i, dim;
double L;

long long dr_a[maxN << 1];
long long dr_b[maxN << 1];

int ind[maxN << 1];

int S[maxN << 1], s_dim;
double limit[maxN << 1];
double time_change;
double ans = inf, ans_time;

void add_line(long long pos, long long w) {
    dr_a[++dim] = w;
    dr_b[  dim] = -w * pos;

    //cerr << "add line " << dr_a[dim] << "x + " << dr_b[dim] << '\n';

    dr_a[n + dim] = -w;
    dr_b[n + dim] = w * (-L + pos);

    //cerr << "add line " << dr_a[dim] << "x + " << dr_b[dim] << '\n';
}

void read_input() {
    long long w, pos, A, B, C1, D, C;
    long long k = 1;

    scanf("%lld%lld%lld%lld%lld", &w, &A, &B, &C1, &D);
    pos = 0; C = C1;

    add_line(pos, w);
    for (long long i = 2; i <= n; i++) {
        pos = pos + 1 + (((pos * i) ^ A) % B);
        if (2 * i > n) k = -1;
        w = max(1LL, w + k * (1 + (((w * (i + C)) ^ (D * i)) % D)));
        C = 1 + ((((C * C) % D) * i) % D);

        add_line(pos, w);
    }

    n = dim * 2;
}

bool cmp(int a, int b) {
    return dr_a[a] < dr_a[b];
}

double getIntersection(int id1, int id2) {
    if (dr_a[id1] == dr_a[id2]) {
        if (dr_b[id1] > dr_b[id2])
            return inf; //! nu il elimina
        else
            return -inf; //! il elimina
    }

    //cerr << "Intersection : " << (1.00 * ( dr_b[id2] - dr_b[id1] ) ) / ( dr_a[id1] - dr_a[id2] ) << '\n';

    return (1.00 * ( dr_b[id2] - dr_b[id1] ) ) / ( dr_a[id1] - dr_a[id2] );
}

void better_sort() {
    int dim = n / 2;
    int l = dim / 2;
    int r = l;
    int pos;

    ind[1] = l + dim;
    ind[n] = l;

    for (i = 1; i < dim; i++) {
        if (l != 1 && r != dim) {
            pos = (dr_a[l - 1] > dr_a[r + 1] ? l - 1 : r + 1);
        } else {
            if (l == 1)
                pos = r + 1;
            else
                pos = l - 1;
        }

        ind[i + 1] = pos + dim;
        ind[n - i] = pos;

        l = min(l, pos);
        r = max(r, pos);
    }
}

int main()
{
    freopen("center.in","r",stdin);
    freopen("center.out","w",stdout);

    scanf("%d %lf", &n, &L);
    read_input();

    better_sort();
    //for (i = 1; i <= n; i++) ind[i] = i;
    //sort(ind + 1, ind + n + 1, cmp);

    S[++s_dim] = ind[1];
    limit[s_dim] = -inf;

    for (int j = 2; j <= n; j++) {
        i = ind[j];

        while (true) {
            time_change = getIntersection(S[s_dim], i);
            if (limit[s_dim] < time_change) break;
            s_dim--;
        }

        if (dr_a[ S[s_dim] ] == dr_a[i]) continue;

        S[++s_dim] = i;
        limit[s_dim] = time_change;
    }

    for (i = 2; i <= s_dim; i++) {
        double act = limit[i] * dr_a[ S[i] ] + 1.00 * dr_b[ S[i] ];

        //cerr << "now : " << act << '\n';

        if (ans > act) {
            ans = act;
            ans_time = limit[i];
        }
    }

    printf("%.9lf\n%.9lf\n", ans, ans_time);

    return 0;
}
