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

#define maxN 422

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

        void init2(int _n) {
            n = _n;

            for (int i = 1; i <= 2 * n; i++) {
                list[i].clear();
                rev[i].clear();
            }
            accepted = false;
        }

        inline void add_or(int a, int b) {
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

        inline void add_rel(int a, int b) {
            a = get_id(a);
            b = get_id(b);

            list[a].pb(b);
            rev[b].pb(a);
        }

        inline int get_id(int x) {
            if (x > 0) return x;
            return n - x;
        }

        inline int get_inv(int x) {
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

struct edge {
    int x, y, val;

    bool operator<(const edge& who)const {
        return val > who.val;
    }
};

int n, i, j, x, pos;
vector<edge> E;
int dad[maxN];
int ans;
bool need;
SAT2 work;

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (dad[x] == dad[y])
        return false;

    dad[x] = y;
    return true;
}

bool pair_them(edge act) {
    int x = act.x;
    int y = act.y;
    need = false;

    if (Merge(x, n + y)) {
        Merge(n + x, y);

        if (Find(x) == Find(x + n)) return false;
        if (Find(y) == Find(y + n)) return false;

        need = true;
    }

    return true;
}

bool check(int maxi, int mini) {
    int i;

    work.init2(n);

    for (i = 0; i < E.size(); i++) {
        auto e = E[i];

        if (maxi >= e.val) break;
        work.add_or(e.x, e.y);
        work.add_or(-e.x, -e.y);
    }

    for (; i < E.size(); i++) {
        auto e = E[i];

        if (mini >= e.val) break;
        work.add_or(e.x, e.y);
    }

    return work.run();
}

int get_min(int ini_pos) {
    int ans = ini_pos;

    if (check(E[ans].val, -1)) return E.size();

    for (int step = 1 << 20; step > 0; step >>= 1) {
        if (ans + step >= E.size()) continue;
        if (ans + step >= pos + 1) continue;
        if (check(E[ini_pos].val, E[ans + step].val))
            ans += step;
    }

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    work.init(200);
    work.state.reserve(400);
    for (i = 1; i <= 400; i++) {
        work.list[i].reserve(400);
        work.rev[i].reserve(400);
    }

    while (scanf("%d", &n) == 1) {
        E.clear();

        for (i = 1; i <= n; i++) {
            for (j = i + 1; j <= n; j++) {
                scanf("%d", &x);
                E.pb({i, j, x});
            }
        }

        if (n <= 2) {
            printf("0\n");
            continue;
        }

        sort(E.begin(), E.end());
        for (i = 1; i <= 2 * n; i++) dad[i] = i;
        ans = 2 * E[0].val;
        pos = E.size();

        for (i = 0; i < E.size(); i++) {
            need = true;

            if (i != 0) {
                if (!pair_them(E[i - 1]))
                    break;
            }

            if (need)
                pos = get_min(i);
            else
                pos = max(pos, i);

            if (pos != E.size())
                ans = min(ans, E[i].val + E[pos].val);
            else
                ans = min(ans, E[i].val);
        }


        printf("%d\n", ans);
    }


    return 0;
}
