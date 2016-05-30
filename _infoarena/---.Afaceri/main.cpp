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

#define maxN 2016
#define maxL 5016

struct my_vector {
    int dim;
    int data[maxN], aib[maxN];

    void init(int _dim) {
        dim = _dim;
        memset(data, 0, sizeof(data));
        memset(aib, 0, sizeof(aib));
    }

    int zrs(const int x) {
        return (x ^ (x - 1)) & x;
    }

    void add(int pos, const int val) {
        while (pos <= dim) {
            aib[pos] += val;
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

    //! change_value and sum_on_interval are 0-indexed
    void change_value(int pos, const int val) {
        pos++;

        if (val - data[pos] != 0) {
            add(pos, val - data[pos]);
            data[pos] = val;
        }
    }

    int sum_on_interval(int l, int r) {
        l++; r++;
        return sum(r) - sum(l - 1);
    }
};

int n, m, Q, L, A0, A1, A2, R, i, j;
int LX, X[maxL];
int LY, Y[maxL];
char s[maxN];

int poz, poz1, poz2, len, VAL;
char c;
my_vector work[maxN];

int ans;


void update(const int poz) {
    int i, p1, p2;

    for (i = 0; i < n; i++) {
        //! from poz to ...
        p1 = poz;
        p2 = p1 + i;

        if (p2 >= n) p2 -= n;

        if (s[p1] != s[p2])
            work[i].change_value(p1, 1);
        else
            work[i].change_value(p1, 0);

        //! from .. to poz
        p2 = poz;
        p1 = poz - i;

        if (p1 < 0) p1 += n;
        if (p1 >= n) p1 -= n;

        if (s[p1] != s[p2])
            work[i].change_value(p1, 1);
        else
            work[i].change_value(p1, 0);
    }
}

int query(int p1, int p2, const int len) {
    int dif, bg, en;

    if (p1 > p2) swap(p1, p2);
    dif = p2 - p1;

    bg = p1;
    en = p1 + len - 1;

    if (en >= n) en -= n;

    if (bg <= en)
        return work[dif].sum_on_interval(bg, en);
    else
        return work[dif].sum_on_interval(0, en) + work[dif].sum_on_interval(bg, n - 1);
}

int main()
{
    freopen("afaceri.in","r",stdin);
    freopen("afaceri.out","w",stdout);

    scanf("%d%d%d%d%d%d%d%d", &n, &m, &Q, &L, &A0, &A1, &A2, &R);
    scanf("%d", &LX);
    for (i = 0; i < LX; i++) scanf("%d", &X[i]);
    scanf("%d", &LY);
    for (i = 0; i < LY; i++) scanf("%d", &Y[i]);

    scanf("%s", s);
    for (i = 0; i < n; i++) {
        work[i].init(n);
        for (j = 0; j < n; j++)
            if (s[j] != s[ (i + j) % n ])
                work[i].change_value(j, 1);
    }

    for (i = 1; i <= m; i++) {
        if (i % Q == 0) { // generez o operatie Update
            poz=A1%n; c='a' + A2 % 26;
            s[poz] = c;

            update(poz);
        } else { //generez o operatie Query
            poz1 = A0%n; poz2=A1%n; len=L+A2%(n-L+1);

            int act = query(poz1, poz2, len);
            ans += act;

            //cerr << "Answered q" << i << " : " << act << '\n';
        }
        //recalculez A0 A1 A2
        VAL = ((long long)A2*X[i%LX]+Y[i%LY])%R; A0 = A1; A1 = A2; A2 = VAL;
    }

    printf("%d", ans);

    return 0;
}
