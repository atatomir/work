#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 10011
#define lSon (node << 1)
#define rSon (lSon | 1)

class SAT2 {
    public:
        int n;
        vector< vector<int> > list, rev;
        vector<int> state;
        bool accepted;

        void init(int _n) {
            n = _n;
            list = rev = vector< vector<int> >(2 * n + 10, vector<int>(0));
            state = vector<int>(2 * n + 10, -1);
            accepted = false;
        }

        void add_or(int a, int b) {
            add_rel(-a, b);
            add_rel(-b, a);
        }

        bool run() {
            int i;

            state = vector<int>(2 * n + 10, -1);
            accepted = true;

            us = vector<bool>(2 * n + 10, false);
            while (!S.empty()) S.pop();

            for (i = 1; i <= 2 * n; i++)
                if (!us[i])
                    dfs(i);

            us = vector<bool>(2 * n + 10, false);

            while (!S.empty()) {
                int node = S.top(); S.pop();
                if (us[node]) continue;

                aux.clear();
                dfs2(node);

                int c = get_color();
                if (!set_color(c)) {
                    accepted = false;
                    return false;
                }
            }

            return true;
        }

    private:
        vector<bool> us;
        stack<int> S;
        vector<int> aux;

        void add_rel(int a, int b) {
            a = get_id(a);
            b = get_id(b);

            list[a].pb(b);
            rev[b].pb(a);
        }

        int get_id(int x) {
            if (x > 0) return x;
            return n - x;
        }

        int get_inv(int x) {
            if (x <= n) return x + n;
            return x - n;
        }

        void dfs(int node) {
            us[node] = true;

            for (auto to : list[node])
                if (!us[to])
                    dfs(to);

            S.push(node);
        }

        void dfs2(int node) {
            us[node] = true;

            for (auto to : rev[node])
                if (!us[to])
                    dfs2(to);

            aux.pb(node);
        }

        int get_color() {
            int ans = 0;

            for (auto e : aux)
                ans = max(ans, state[e]);

            return ans;
        }

        bool set_color(int c) {
            for (auto e : aux) {
                if (state[e] == c) continue;
                if (state[e] != -1) return false;

                state[e] = c;
                state[get_inv(e)] = c ^ 1;

                if (c) {
                    for (auto to : list[e]) {
                        if (state[to] == 0) return false;
                        if (state[to] == 1) continue;
                        state[to] = 1;
                        state[get_inv(to)] = 0;
                    }
                }
            }

            return true;
        }
};

struct aint {
    int n;
    SAT2 data;

    void build(int node, int l, int r) {
        if (l == r) return;

        int mid = (l + r) >> 1;
        build(lSon, l, mid);
        build(rSon, mid + 1, r);

        data.add_or(node, -lSon);
        data.add_or(node, -rSon);
    }

    void init(int _n) {
        n = _n;
        data.init(4 * n + 10);

        build(1, 1, n);
    }

    int get_id(int node, int l, int r, int pos) {
        if (l == r)
            return node;

        int mid = (l + r) >> 1;
        if (pos <= mid)
            return get_id(lSon, l, mid, pos);
        else
            return get_id(rSon, mid + 1, r, pos);
    }

    void upd(int node, int l, int r, int qL, int qR, int fr) {
        if (qL <= l && r <= qR) {
            data.add_or(-node, -fr);
            return;
        }

        int mid = (l + r) >> 1;
        if (qL <= mid)
            upd(lSon, l, mid, qL, qR, fr);
        if (qR > mid)
            upd(rSon, mid + 1, r, qL, qR, fr);
    }
};

int n, i;
ll x, y;
vector< pair<ll, int> > ord;
aint pattern, work;

vector<int> wh[maxN];

bool check(ll d) {
    int i;

    work = pattern;
    for (i = 0; i < ord.size(); i++) {
        int p1 = lower_bound(ord.begin(), ord.end(), mp(ord[i].first - d, 0)) - ord.begin() + 1;
        int p2 = lower_bound(ord.begin(), ord.end(), mp(ord[i].first + d + 1, 0)) - ord.begin();
        int p = i + 1;
        int id = work.get_id(1, 1, 2 * n, p);

        if (p1 < p)
            work.upd(1, 1, 2 * n, p1, p - 1, id);
        if (p2 > p)
            work.upd(1, 1, 2 * n, p + 1, p2, id);
    }

    return work.data.run();
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &x, &y);
        ord.pb(mp(x, i));
        ord.pb(mp(y, i));
    }

    sort(ord.begin(), ord.end());
    for (i = 0; i < ord.size(); i++)
        wh[ord[i].second].pb(i + 1);

    pattern.init(2 * n);
    for (i = 1; i <= n; i++) {
        int id1 = pattern.get_id(1, 1, 2 * n, wh[i][0]);
        int id2 = pattern.get_id(1, 1, 2 * n, wh[i][1]);

        pattern.data.add_or(id1, id2);
        pattern.data.add_or(-id1, -id2);
    }

    ll ans = -1;
    for (ll step = (1LL << 30); step > 0; step >>= 1)
        if (check(ans + step))
            ans += step;

    printf("%lld", ans + 1);

    return 0;
}
