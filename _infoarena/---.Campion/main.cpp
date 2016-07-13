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

#define maxN 20011
#define inf 1e30
#define eps 1e-7

struct Line {
    ll a, b;
    int id;

    bool operator<(const Line& who)const {
        return mp(a, b) < mp(who.a, who.b);
    }

    void read(int _id) {
        static ll R, D;
        scanf("%lld%lld", &R, &D);

        a = D;
        b = R - a * 0;
        id = _id;
    }

    double intr(const Line& who) {
        return (1.00 * who.b - 1.00 * b) / (1.00 * a - 1.00 * who.a);
    }
};

int n, i, j, k;
double T;
Line L[maxN];
int ratio[maxN];
vector<Line> work;

int dim;
pair<double, int> S[maxN];
int ans;


void solve() {
    int i;

    S[dim = 1] = mp(-inf, 0);

    for (i = 1; i < work.size(); i++) {
        auto e = work[i];

        while (S[dim].first > work[ S[dim].second ].intr(e)) dim--;
        S[++dim] = mp( work[ S[dim].second ].intr(e), i );
    }

    for (i = 1; i <= dim; i++) {
        if (S[i].first > T + eps) break;
        if (i != dim && S[i + 1].first < -eps) continue;
        ans += ratio[ work[S[i].second].id ];
    }
}

int main()
{
    freopen("campion.in","r",stdin);
    freopen("campion.out","w",stdout);

    scanf("%d%lf", &n, &T);
    for (i = 1; i <= n; i++) L[i].read(i);
    sort(L + 1, L + n + 1);

    for (i = 1; i <= n; i = j) {
        for (j = i; j <= n && L[i].a == L[j].a; j++);
        for (k = i; k < j; k++)
            if (L[k].b == L[j - 1].b)
                ratio[ L[j - 1].id ]++;

        work.pb(L[j - 1]);
    }

    solve();
    printf("%d", ans);

    return 0;
}
