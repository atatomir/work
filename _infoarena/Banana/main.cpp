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

#define maxN 16111

#define mod 1007
class Hash {
    public:
        void init() {
            for (int i = 0; i < mod; i++) data[i].clear();
        }

        void add(pair<int, int> act) {
            data[ (act.first + act.second) % mod ].pb(act);
        }
        void remove(pair<int, int> act) {
            int go = (act.first + act.second) % mod;
            for (int i = 0; i < data[go].size(); i++) {
                if (data[go][i] == act) {
                    data[go][i] = data[go][ data[go].size() - 1 ];
                    data[go].pop_back();
                    return;
                }
            }
        }
        bool isIn(pair<int, int> act) {
            int go = (act.first + act.second) % mod;
            for (int i = 0; i < data[go].size(); i++)
                if (data[go][i] == act)
                    return true;

            return false;
        }

    private:
        vector< pair<int, int> > data[mod];
};

const int defX[4] = {0, 0, -1, 1};
const int defY[4] = {-1, 1, 0, 0};

int n, k, i, x, y, aux;

vector< pair<int, int> > vv;
vector<int> ans;

Hash M;

void dfs(int x, int y) {
    M.remove(mp(x, y));
    aux++;

    int xx, yy;
    for (int i = 0; i < 4; i++) {
        xx = x + defX[i];
        yy = y + defY[i];

        if (M.isIn(mp(xx, yy))) dfs(xx, yy);
    }
}

int main()
{
    freopen("banana.in","r",stdin);
    freopen("banana.out","w",stdout);

    scanf("%d %d", &n, &k);

    M.init();
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        M.add(mp(x, y));
        vv.pb(mp(x, y));
    }

    for (auto who : vv) {
        if (!M.isIn(who)) continue;

        aux = 0;
        dfs(who.first, who.second);

        ans.pb(aux);
    }

    sort(ans.begin(), ans.end());

    aux = 0;
    while(k > 0) {
        k--;

        aux += ans[ans.size() - 1];
        ans.pop_back();
    }

    printf("%d", aux);

    return 0;
}
