#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
 
using namespace std;
 
#define ll long long
#define pb push_back
#define mp make_pair
 
#define maxN 100011
 
class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
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
 
int n, m, i, j, x;
vector< vector<int> > mat, nxt;
vector<int> aux;
vector< pair<int, int> > best;
int pos[maxN];
 
int now;
vector<int> sol[maxN];
 
int Find(vector<int>& data, int x) {
    if (data[x] == x) return x;
    data[x] = Find(data, data[x]);
    return data[x];
}
 
bool check(int lim) {
    int i, j, pas, wh, need, wh2;
    int ln, val;
 
    for (i = 1; i <= n; i++) pos[i] = m;
    for (i = 1; i <= n; i++) nxt[i] = aux;
 
    for (pas = 0; pas < best.size(); pas++) {
        val = best[pas].first;
        ln = best[pas].second;
 
        wh = Find(nxt[ln], 0);
        if (wh == m) continue;
        if (mat[ln][wh] != val) continue;
 
        need = lim - val;
        nxt[ln][wh] = wh + 1;
 
        for (i = 1; i <= n; i++) {
            if (i == ln) continue;
 
            while (pos[i] > 0) {
                if (mat[i][pos[i] - 1] > need) break;
                pos[i]--;
            }
 
            wh2 = Find(nxt[i], pos[i]);
            if (wh2 == m) return false;
            nxt[i][wh2] = wh2 + 1;
        }
    }
 
    return true;
}
 
bool recon(int lim) {
    int i, j, pas, wh, need, wh2;
    int ln, val;
 
    for (i = 1; i <= n; i++) pos[i] = m;
    for (i = 1; i <= n; i++) nxt[i] = aux;
 
    for (pas = 0; pas < best.size(); pas++) {
        val = best[pas].first;
        ln = best[pas].second;
 
        wh = Find(nxt[ln], 0);
        if (wh == m) continue;
        if (mat[ln][wh] != val) continue;
 
        need = lim - val;
        nxt[ln][wh] = wh + 1;
 
        sol[++now].clear();
 
        for (i = 1; i <= n; i++) {
            if (i == ln) {
                sol[now].pb(val);
                continue;
            }
 
            while (pos[i] > 0) {
                if (mat[i][pos[i] - 1] > need) break;
                pos[i]--;
            }
 
            wh2 = Find(nxt[i], pos[i]);
            if (wh2 == m) return false;
            nxt[i][wh2] = wh2 + 1;
            sol[now].pb(mat[i][wh2]);
        }
    }
 
    return true;
}
 
int main()
{
    Buffer fin("danger.in", 1 << 20);
    freopen("danger.out", "w", stdout);
 
    fin >> n >> m;
    mat.resize(n + 2);
 
    aux.clear();
    for (i = 0; i <= m; i++) aux.pb(i);
    nxt = vector< vector<int> >(n + 2, aux);
 
    int ans = 1;
 
    for (i = 1; i <= n; i++) {
        mat[i].resize(m);
        for (j = 1; j <= m; j++) {
            fin >> mat[i][j - 1];
            ans = max(ans, mat[i][j - 1]);
 
            best.pb(mp(mat[i][j - 1], i));
        }
 
        sort(mat[i].begin(), mat[i].end());
        reverse(mat[i].begin(), mat[i].end());
    }
 
    sort(best.begin(), best.end());
    reverse(best.begin(), best.end());
 
    int base = ans * 2;
 
    for (int step = (1 << 30); step > 0; step >>= 1) {
        if (base - ans >= step)
            if (!check(ans + step))
                ans += step;
    }
 
    ans++;
    cerr << ans;
    recon(ans);
 
    for (i = 1; i <= now; i++) {
        for (j = 0; j < sol[i].size(); j++)
            printf("%d ", sol[i][j]);
        printf("\n");
    }
 
 
    return 0;
}
