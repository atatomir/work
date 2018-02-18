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

#define maxN 70011

class Buffer {
    public:
        Buffer(string name, int _dim) {
            if (name != "")
                freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &dest) {
            T sign = +1;
            dest = 0;

            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            if (data[pos] == '-') {
                sign = -1;
                if (++pos == dim)
                    refill();
            }

            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= sign;
            return *this;
        }


    private:
        int pos, dim;
        vector<char> data;

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }

        void refill() {
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
            pos = 0;
        }
};

int n, i, x, y, R;
vector<int> list[maxN];
vector<int> way;
int dp[maxN];

int dad[maxN], ans;
int close_down[maxN], close_up[maxN];

void dfs_ini(int node, int root) {
    close_down[node] = n + 11;
    if (list[node].size() == 1) {
        close_down[node] = 0;
        return;
    }

    for (auto to : list[node]) {
        if (to == root) continue;
        dad[to] = node;
        dfs_ini(to, node);
        close_down[node] = min(close_down[node], close_down[to] + 1);
    }
}

void dfs_up(int node, int root) {
    if (list[node].size() == 1) return;

    vector< pair<int, int> > aux = {};
    for (auto to : list[node])
        if (to != root)
            aux.pb(mp(close_down[to], to));

    sort(aux.begin(), aux.end());
    if (aux.size() == 1) {
        close_up[aux[0].second] = close_up[node] + 1;
        dfs_up(aux[0].second, node);
        return;
    }

    close_up[aux[0].second] = 1 + min(close_up[node], aux[1].first + 1);
    for (i = 1; i < aux.size(); i++)
        close_up[aux[i].second] = 1 + min(close_up[node], aux[0].first + 1);

    for (auto e : aux) dfs_up(e.second, node);
}

void dfs(int node, int root) {
    way.pb(node);
    dp[node] = 0;

    if (list[node].size() == 1) {
        int id = way[(way.size() / 2)];
        dp[id]++;
    }

    for (auto to : list[node]) {
        if (to != root) {
            dfs(to, node);
        }
    }

    if (dp[node] >= 1) {
        dp[node] = 1;
    } else {
        for (auto to : list[node]) {
            if (to != root) {
                dp[node] += dp[to];
            }
        }
    }

    way.pop_back();
}

void dfs_smart(int node, int lvl) {
    if (lvl - 1 == close_down[node] ||
        lvl - 2 == close_down[node]) {
        ans++;
        return;
    }

    for (auto to : list[node])
        if (to != dad[node])
            dfs_smart(to, lvl + 1);
}

void dfs_smart2(int node, int son, int lvl) {
    int v = close_up[node];
    for (auto to : list[node])
        if (to != son)
            v = min(v, close_down[to] + 1);

    if (lvl - 1 == v ||
        lvl - 2 == v) {
        ans++;
        return;
    }

    if (dad[node] != 0) {
        dfs_smart2(dad[node], node, lvl + 1);
    }

    for (auto to : list[node])
        if (to != son && to != dad[node])
            dfs_smart(to, lvl + 1);
}

int solve(int node) {
    int i;

    if (list[node].size() == 1) return 1;
    //dfs(node, 0);

    ans = 0;
    dfs_smart(node, 1);
    if (dad[node] != 0) dfs_smart2(dad[node], node, 2);

    return ans;
}

int main()
{
    Buffer fin("atlarge.in", 1 << 20);
    //freopen("atlarge.in","r",stdin);
    freopen("atlarge.out","w",stdout);

    fin >> n;
    for (i = 1; i < n; i++) {
        fin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    if (n == 2) {
        printf("1\n1\n");
        return 0;
    }

    /*for (i = n + 1; i <= 3000; i++) {
        x = (rand() % (i - 1)) + 1;
        list[x].pb(i);
        list[i].pb(x);
    }
    n = 3000;*/

    for (R = 1; list[R].size() == 1; R++);
    dfs_ini(R, 0);

    close_up[R] = n + 11;
    dfs_up(R, 0);

    for (i = 1; i <= n; i++)
        printf("%d\n", solve(i));



    return 0;
}
