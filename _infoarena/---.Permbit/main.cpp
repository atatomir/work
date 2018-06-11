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

const ll mod = 1000000007;
const int maxM = 1000011;

struct group {
    vector<int> t1, t2;
};

int tp, n, m, i, j, sz;
char s[maxM];
vector<string> data;
vector<int> aux1, aux2;

ll fact[maxM], ans;
int p[maxM];

int gr[maxM];
vector<group> work;



bool is_lower(int id1, int id2, int bg, int en) {
    for (; bg <= en; bg++) {
        if (data[bg][id1] < data[bg][id2]) return true;
        if (data[bg][id1] > data[bg][id2]) return false;
    }
    return false;
}

bool is_equal(int id1, int id2, int bg, int en) {
    for (; bg <= en; bg++) {
        if (data[bg][id1] < data[bg][id2]) return false;
        if (data[bg][id1] > data[bg][id2]) return false;
    }
    return true;
}

void get_group(int l, int r) {
    vector<int> t1, t2;
    int i;

    t1 = t2 = {};
    for (i = l; i <= r; i++) {
        t1.pb(aux1[i]);
        t2.pb(aux2[i]);
    }

    sort(t1.begin(), t1.end());
    sort(t2.begin(), t2.end());

    work.pb({t1, t2});
    for (auto e : t1) gr[e] = work.size() - 1;
}

void assign_mid(int id) {
    int pos = (0 + work[id].t2.size() - 1) / 2;
    p[work[id].t1[0]] = work[id].t2[pos];

    work[id].t1.erase(work[id].t1.begin());
    work[id].t2.erase(work[id].t2.begin() + pos);
}

void solve() {
    int i, j;

    for (i = 0; i < m; i++) {
        if (work[gr[i]].t1.size() % 2 == 1) {
            assign_mid(gr[i]);
        } else {
            assign_mid(gr[i]);
            break;
        }
    }

    for (i = 0; i < work.size(); i++) {
        reverse(work[i].t2.begin(), work[i].t2.end());
        for (j = 0; j < work[i].t2.size(); j++)
            p[work[i].t1[j]] = work[i].t2[j];
    }
}

int main()
{
    freopen("permbit.in","r",stdin);
    freopen("permbit.out","w",stdout);

    scanf("%d%d%d\n", &tp, &n, &m);
    data.resize(n + 5);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s);
        data[i] = "";
        for (j = 0; j < m; j++)
            data[i] += s[j];
    }

    for (i = 0; i < m; i++) {
        aux1.pb(i);
        aux2.pb(i);
    }

    sort(aux1.begin(), aux1.end(), [](int a, int b)->bool const{
        return is_lower(a, b, 1, n - 1);
    });

    sort(aux2.begin(), aux2.end(), [](int a, int b)->bool const{
        return is_lower(a, b, 2, n);
    });

    fact[0] = ans = 1;
    for (i = 1; i <= m; i++) fact[i] = (fact[i - 1] * i) % mod;

    for (i = 0; i < aux1.size(); i = j) {
        for (j = i; j < aux1.size(); j++) {
            if (!is_equal(aux1[i], aux1[j], 1, n - 1)) break;
        }

        sz = j - i;
        ans = (ans * fact[sz]) % mod;

        get_group(i, j - 1);
    }

    if (tp == 1 || tp == 2) {
        solve();
        for (i = 0; i < m; i++) printf("%d ", p[i] + 1);
    } else {
        printf("%lld", ans);
    }



    return 0;
}
