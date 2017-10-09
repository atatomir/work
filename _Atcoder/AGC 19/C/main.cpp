#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 200011

const ll def = 1000000000LL;
const double PI = 3.141592653589793;

ll px1, px2, py1, py2;
ll n, i;
pair<ll, ll> P[maxN];
bool rev;

vector< pair<ll, ll> > aux;
vector<ll> ord;
double ans;

bool special_cases() {
    if (px1 != px2 && py1 != py2)
        return false;

    if (px1 == px2 && py1 == py2) {
        cout << 0.00;
        return true;
    }

    double ans = 0.00;
    if (px1 == px2) {
        ans = 100LL * (py2 - py1);

        for (i = 1; i <= n; i++) {
            if (P[i].first == px1 && P[i].second > py1 && P[i].second < py2)
                ans += 10.00 * PI - 20.00;
        }
    } else {
        ans = 100LL * (px2 - px1);

        for (i = 1; i <= n; i++) {
            if (P[i].second == py1 && P[i].first > px1 && P[i].first < px2)
                ans += 10.00 * PI - 20.00;
        }
    }

    printf("%.15lf", ans);
    return true;
}

ll solve() {
    int i;

    ord.clear();
    for (auto e : aux) {
        auto it = lower_bound(ord.begin(), ord.end(), e.second);
        if (it == ord.end()) {
            ord.pb(e.second);
        } else {
            assert(*it != e.second);
            *it = e.second;
        }
    }

    return ord.size();
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> px1 >> py1 >> px2 >> py2;
    if (px1 > px2) {
        swap(px1, px2);
        swap(py1, py2);
    }
    if (py1 > py2) {
        py1 = def - py1;
        py2 = def - py2;
        rev = true;
    }

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> P[i].first >> P[i].second;
        if (rev) P[i].second = def - P[i].second;
    }

    if (special_cases())
        return 0;

    assert(px1 < px2);
    assert(py1 < py2);

    for (i = 1; i <= n; i++) {
        if (P[i].first >= px1 && P[i].first <= px2)
            if (P[i].second >= py1 && P[i].second <= py2)
                aux.pb(P[i]);
    }

    sort(aux.begin(), aux.end());
    ll vv = solve();


    ans = 100LL * (px2 - px1 + py2 - py1);
    ans += (5.00 * PI - 20.00) * (1.00 * vv);

    if (vv == min(py2 - py1 + 1, px2 - px1 + 1))
        ans += 5.00 * PI;

    assert(ans > 0.00);

    printf("%.15lf", ans);

    return 0;
}
