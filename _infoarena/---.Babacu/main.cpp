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
#define pii pair<double, double>

int n, i, cnt;
double a, b, c;
vector< pii > v;

vector<pii> S;

int cross(pii A, pii B, pii C) {
    B.first -= A.first;
    B.second -= A.second;

    C.first -= A.first;
    C.second -= A.second;

    return B.first * C.second - B.second * C.first;
}

int main()
{
    freopen("babacu.in","r",stdin);
    freopen("babacu.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", &a, &b, &c);

        if (c == 0.00) continue;
        v.pb(mp(a / c, b / c));
    }
    v.pb(mp(0.00, 0.00)); //! lines at infinity

    if (v.size() == 1) {
        printf("0");
        return 0;
    }

    sort(v.begin(), v.end());
    S.pb(v[0]);
    S.pb(v[1]);

    for (i = 2; i < v.size(); i++) {
        while (S.size() > 1) {
            pii __last = S[ S.size() - 2 ];
            pii _last = S[S.size() - 1];

            if (cross(__last, _last, v[i]) < 0.00) break;
            S.pop_back();
        }
        S.pb(v[i]);
    }

    int limi = S.size();
    for (i = v.size() - 2; i >= 0; i--) {
        while (S.size() > limi) {
            pii __last = S[ S.size() - 2 ];
            pii _last = S[S.size() - 1];

            if (cross(__last, _last, v[i]) < 0.00) break;
            S.pop_back();
        }
        S.pb(v[i]);
    }

    S.pop_back();
    for (auto e : S)
        if (e.first != 0 || e.second != 0.00)
            cnt++;

    printf("%d", cnt);

    return 0;
}
