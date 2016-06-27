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
 
#define maxN 200011
 
class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 10);
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
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
            pos = 0;
        }
};
 
 
int n, k, i;
ll pr[maxN], dist[maxN];
ll ans, step;
 
int dim;
pair<int, int> S[maxN];
stack<int> deny;
 
int cb(int x) {
    int ans = 0;
 
    for (int step = (1 << 17); step > 0; step >>= 1)
        if (ans + step <= dim)
            if (S[ans + step].second >= x)
                ans += step;
 
    return ans;
}
 
bool check(ll lim) {
    int i, pos, need;
    ll aux;
    pair<int, int> act;
 
    while (!deny.empty()) deny.pop();
 
    if (lim == 8) {
        cerr << "yep";
    }
 
 
    dim = 0;
    for (i = 2 * n; i >= 1; i--) {
        aux = lim - pr[i];
 
        if (dist[i - 1] + aux < dist[i]) continue;
 
        pos = upper_bound(dist + i, dist + 2 * n + 1, dist[i - 1] + aux) - dist - 1;
        act = mp(i, pos + 1);
 
        while (dim >= 1 && act.second >= S[dim].second) {
            if (!deny.empty())
                if (deny.top() == dim)
                    deny.pop();
            dim--;
        }
 
        while (dim >= 2) {
            if (act.second < S[dim - 1].first) break;
 
            if (!deny.empty())
                if (deny.top() == dim)
                    deny.pop();
            dim--;
        }
 
        if (dim != 0 && S[dim].first > act.second) deny.push(dim + 1); //! limits
 
        S[++dim] = act;
 
        need = i + n;
        if (S[1].second < need) continue;
 
        pos = cb(need);
 
        if (!deny.empty())
            if (pos < deny.top())
                continue;
 
        if (dim - pos + 1 <= k)
            return true;
    }
 
 
 
    return false;
}
 
int main()
{
    Buffer fin("oneouts.in", 1 << 20);
    freopen("oneouts.out","w",stdout);
 
    fin >> n >> k;
    for (i = 1; i <= n; i++) {
        fin >> dist[i];
        dist[i + n] = dist[i];
    }
 
    for (i = 1; i <= n; i++) {
        fin >> pr[i];
        pr[i + n] = pr[i];
    }
 
    for (i = 2; i <= 2 * n; i++) dist[i] += dist[i - 1];
 
    ans = 0;
    for (step = (1LL << 50); step > 0; step >>= 1)
        if (!check(ans + step))
            ans += step;
 
    printf("%lld", ans + 1);
    cerr << ans + 1;
 
    return 0;
}
