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

#define maxN 10011
#define inf 1000000000

int t, ti;
int n, i, cnt;
vector<int> A, B;

vector<int> in, out;

int need[maxN];
int vars[maxN];

int sum[maxN];
vector< pair<int, int> > ans, aux;

bool valid() {
    if (n > 100) return true;

    for (auto e : ans) {
        int pos = e.first;
        int x = e.second;

        if (pos < 0 || pos > inf)
            return false;
        if (x < 0 || x > inf)
            return false;

        for (i = 0; i < n; i++) {
            if (A[i] < pos)
                A[i] = min(pos, A[i] + x);
            else
                A[i] = max(pos, A[i] - x);
        }
    }

    for (i = 0; i < n; i++)
        if (A[i] != B[i])
            return false;

    return true;
}

bool check() {
    for (i = 0; i < cnt; i++)
        vars[i + 1] = need[i] ^ vars[i];

    for (i = 0; i < cnt; i++)
        if (in[i] - vars[i] - vars[i + 1] < out[i])
            return false;


    return true;
}

void give_sol() {
    int i, before;

    sum[0] = A[0];
    for (i = 1; i <= cnt; i++) sum[i] = sum[i - 1] + in[i - 1];
    aux.clear();

    for (i = cnt; i >= 0; i--) {
        if (vars[i] == 0) continue;

        ans.pb(mp(sum[i] + ans.size(), 1));
        aux.pb(mp(sum[i], 1));
    }

    reverse(aux.begin(), aux.end());

    for (i = 0; i <= cnt; i++) {
        auto l = lower_bound(aux.begin(), aux.end(), mp(sum[i], 0));
        auto r = l;

        if (r != aux.end())
            if (r->first == sum[i])
                sum[i]--;

        sum[i] -= l - aux.begin();
        sum[i] += aux.end() - r;
    }


    in.clear();
    for (i = 1; i <= cnt; i++)
        in.pb(sum[i] - sum[i - 1]);

    before = 0;
    for (i = 0; i < cnt; i++) {
        int dif = in[i] - out[i];

        if (dif % 2 == 1)
            cerr << "err";
        dif /= 2;

        if (dif) {
            ans.pb(mp(sum[i] - before + dif, dif));
            before += dif;
        }
    }

    sum[0] += before;

    if (sum[0] < B[0])
        ans.pb(mp(inf, B[0] - sum[0]));
    if (sum[0] > B[0])
        ans.pb(mp(0, sum[0] - B[0]));

    if (!valid()) {
        cerr << "avem o mare problema..";
        //exit(-1);
    }

    printf("%d\n", ans.size());
    for (auto e : ans)
        printf("%d %d\n", e.first, e.second);
}

void solve() {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    in.clear();
    for (i = 1; i < A.size(); i++)
        in.pb(A[i] - A[i - 1]);

    out.clear();
    for (i = 1; i < B.size(); i++)
        out.pb(B[i] - B[i - 1]);

    for (i = 0; i < in.size(); i++) {
        if (in[i] < out[i]) {
            printf("-1\n");
            return;
        }
    }

    cnt = 0;
    for (i = 0; i < in.size(); i++) {
        if (in[i] != 0 || out[i] != 0) {
            in[cnt] = in[i];
            out[cnt] = out[i];

            cnt++;
        }
    }

    in.resize(cnt);
    out.resize(cnt);

    for (i = 0; i < cnt; i++)
        need[i] = ( in[i] % 2 != out[i] % 2 );

    vars[0] = 0;
    if (check()) {
        give_sol();
        return;
    }

    vars[0] = 1;
    if (check()) {
        give_sol();
        return;
    }

    printf("-1\n");
}

int main()
{
    freopen("magnet.in","r",stdin);
    freopen("magnet.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);

        A.resize(n);
        B.resize(n);
        ans.clear();

        for (i = 0; i < n; i++)
            scanf("%d", &A[i]);

        for (i = 0; i < n; i++)
            scanf("%d", &B[i]);

        solve();
    }


    return 0;
}
