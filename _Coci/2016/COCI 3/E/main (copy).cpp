#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define mod 1000000007
#define maxN 1003

int n;

inline void combine(pair<int, int>& a, pair<int, int> b) {
    if (a.first != b.first) {
        a = max(a, b);
    } else {
        a.second += b.second;
        if (a.second >= mod) a.second -= mod;
    }
}

struct aib {
    pair<int, int> data[maxN];

    void init() {
        for (int i = 0; i <= n; i++) data[i] = mp(-n - 1, -1);
    }

    int zrs(int x) {
        return (x & (x - 1)) ^ x;
    }

    void add(int pos, pair<int, int> x) {
        while (pos <= n) {
            combine(data[pos], x);
            pos += zrs(pos);
        }
    }

    pair<int, int> sum(int pos) {
        pair<int, int> ans = mp(-n - 1, -1);
        while (pos > 0) {
            combine(ans, data[pos]);
            pos -= zrs(pos);
        }

        return ans;
    }
};


int m, i, j, val;
int v[maxN];
vector<int> norm;
map<int, int> M;

aib le[maxN], down[maxN];

void upd(int x, int y, pair<int, int> val) {
    le[x].add(y, val);
    //ri[x].add(m - y + 1, val);

    //up[y].add(x, val);
    down[y].add(m - x + 1, val);
}

void add_val(int id) {
    int i, j;
    pair<int, int> aux;

    upd(val, val, mp(1, 1));

    for (j = val + 1; j <= m; j++) {
        aux = down[j].sum(m - val);
        upd(val, j, aux);
    }

    for (i = 1; i < val; i++) {
        aux = le[i].sum(val - 1);
        upd(i, val, aux);
    }
}

int main()
{
    freopen("test.in","r",stdin);

    /*freopen("test.out", "w", stdout);

    printf("1000\n");
    for (i = 1; i <= 1000; i++) printf("%d ", (i * 1773) % 10000);

    return 0;*/

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        norm.pb(v[i]);
    }

    sort(norm.begin(), norm.end());
    norm.resize(unique(norm.begin(), norm.end()) - norm.begin());

    for (i = 0; i < norm.size(); i++) M[norm[i]] = i + 1;
    for (i = 1; i <= n; i++) v[i] = M[v[i]];
    m = norm.size();

    for (i = 1; i <= m; i++) {
        le[i].init();
        down[i].init();
    }


    for (int step = 1; step <= n; step++) {
        val = v[step];
        add_val();
    }

    pair<int, int> ans = mp(-n - 1, -1);
    for (i = 1; i <= m; i++)
        combine(ans, le[i].sum(m));

    printf("%d %d", ans.first, ans.second);

    return 0;
}
