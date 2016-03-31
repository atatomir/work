#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define inf (1 << 30)

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 5);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &dest) {
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

Buffer fin("berarii.in", 1 << 22);

int t, ti;
int n, k, i, x, y, l;
int B[maxN];
vector< pair<int, int> > list[maxN];

bool us[maxN];
queue<int> Q;
vector<int> order;

int daddy_edge[maxN];
int supp[maxN];
int max_up[maxN];  //! how much you can go up
int min_down[maxN]; //! nearest beerhouse


void clean() {
    memset(B, 0, sizeof(B));
    for (i = 1; i < maxN; i++) list[i].clear();
    memset(us, 0, sizeof(us));
    while (!Q.empty()) Q.pop();
    order.clear();
}

void compute_order() {
    us[1] = true;
    Q.push(1);
    daddy_edge[1] = 1;

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        order.pb(node);

        for (int i = 0; i < list[node].size(); i++) {
            if (us[ list[node][i].first ]) {
                list[node][i] = list[node][ list[node].size() - 1 ];
                list[node].pop_back();
                i--;
                continue;
            }

            us[ list[node][i].first ] = true;
            Q.push(list[node][i].first);
            daddy_edge[ list[node][i].first ] = list[node][i].second;
        }
    }

    reverse(order.begin(), order.end());
}

bool check(ll dist) {
    int i;
    int cnt = 0;

    for (i = 1; i <= n; i++) supp[i] = min(1LL * inf, 1LL * dist / B[i]);

    for (int node : order) {
        max_up[node] = supp[node];
        min_down[node] = inf;

        for (auto to : list[node]) {
            max_up[node] = min(max_up[node], max_up[to.first] - to.second);
            min_down[node] = min(min_down[node], min_down[to.first] + to.second);
        }

        if (max_up[node] >= min_down[node]) {
            //! can satisfy right now
            max_up[node] = inf;
            continue;
        }

        if (max_up[node] < daddy_edge[node]) {
            //! must set a beerhouse
            max_up[node] = inf;
            min_down[node] = 0;
            cnt++;
            continue;
        }

        //! just go up
    }

    if (max_up[1] < inf) cnt++;

    return cnt <= k;
}

int main()
{
    //freopen("berarii.in","r",stdin);
    freopen("berarii.out","w",stdout);

    fin >> t;
    for (ti = 1; ti <= t; ti++) {
        clean();

        fin >> n >> k;
        for (i = 1; i <= n; i++) fin >> B[i];
        for (i = 1; i < n; i++) {
            fin >> x >> y >> l;
            list[x].pb(mp(y, l));
            list[y].pb(mp(x, l));
        }

        compute_order();

        ll ans = -1;
        for (ll step = (1LL << 60); step; step >>= 1)
            if (!check(ans + step))
                ans += step;

        printf("%lld\n", ans + 1);
        cerr << ans + 1 << '\n';
    }


    return 0;
}
