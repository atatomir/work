#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
 
using namespace std;
 
#define mp make_pair
#define pb push_back
#define ll long long
 
#define maxN 5016
 
class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 5);
            refill();
        }
 
        Buffer& operator>>(int &dest) {
            while (!is_digit(data[pos]))
                if (++pos == dim)
                    refill();
            dest = 0;
            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }
 
            return *this;
        }
 
    private:
        int dim, pos;
        vector<char> data;
 
        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }
 
        void refill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};
 
int n, m, i, x, y, S;
vector<int> ini[maxN];
vector<int> list[maxN];
int dep[maxN];
bool us[maxN], on_way[maxN];
queue<int> Q;
 
vector<int> order;
bool st[maxN][maxN];
queue<int> in_queue[maxN];
 
 
 
void dfs(int node) {
    us[node] = true;
    on_way[node] = true;
 
    for (int to : ini[node]) {
        if (!us[to]) dfs(to);
        if (!on_way[to])
            list[node].pb(to);
    }
 
    on_way[node] = false;
}
 
void bfs(int node) {
    memset(us, 0, sizeof(us));
    us[node] = true;
    Q.push(node);
 
 
    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();
 
        order.pb(node);
        memcpy(st[node], us, sizeof(us));
        in_queue[node] = Q;
 
        for (int to : list[node]) {
            if (us[to]) continue;
 
            us[to] = true;
            Q.push(to);
        }
    }
}
 
int main()
{
    Buffer fin("colonii.in", 1 << 20);
    freopen("colonii.out","w",stdout);
 
    fin >> n >> m >> S;
    for (i = 1; i <= m; i++) {
        fin >> x >> y;
        ini[x].pb(y);
    }
 
    dfs(S);
    bfs(S);
 
 
    for (int i : order) {
        if (i == S) continue;
 
        memcpy(us, st[i], sizeof(us));
        Q = in_queue[i];
 
        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();
 
            for (int to : list[node])
                if (!us[to])
                    us[to] = true, Q.push(to);
        }
 
        for (int j = 1; j <= n; j++)
            dep[j] += (us[j] == false);
    }
 
    for (i = 1; i <= n; i++)
        printf("%d\n", dep[i] + 1 - (i == S));
 
 
    return 0;
}
