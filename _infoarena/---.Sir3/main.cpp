#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long
#define pii pair<int, int>

#define maxN 200011
#define lSon (node << 1)
#define rSon (lSon | 1)

class aint {
    public:
        void init(int _n, bool *_data) {
            n = _n;
            data = _data;
        }

        void update(int node, int l, int r, int qL, int qR) {
            if (qL <= l && r <= qR) {
                data[node] = true;
                return;
            }

            int mid = (l + r) >> 1;
            if (qL <= mid)
                update(lSon, l, mid, qL, qR);
            if (qR >  mid)
                update(rSon, mid + 1, r, qL, qR);
        }

        bool locked(int node, int l, int r, int pos) {
            if (data[node]) return true;
            if (l == r) return false;

            int mid = (l + r) >> 1;
            if (pos <= mid)
                return locked(lSon, l, mid, pos);
            else
                return locked(rSon, mid + 1, r, pos);
        }

    private:
        int n;
        bool *data;
};

int n, i, s;
int v[maxN];
map<int, int> last;
set<int> not_paired;

bool aint_data[maxN << 2];
aint work;

pair<int, int> ans;

int main()
{
    freopen("sir3.in","r",stdin);
    freopen("sir3.out","w",stdout);

    scanf("%d%d", &n, &s);
    for (i = 1; i <= n; i++)
        scanf("%d", &v[i]);

    work.init(n, aint_data);
    last.clear();
    not_paired.clear();

    for (i = 1; i <= n; i++) {
        int v1 = s - v[i];
        int v2 = v[i];

        last[v2] = i;

        if (last[v1] == 0) {
            //! not paired
            not_paired.insert(i);
            continue;
        }

        //! now paired
        int pos = last[v1];

        not_paired.erase( pos );
        work.update(1, 1, n, pos + 1, i);

        auto deny = not_paired.end();
        if (deny != not_paired.begin()) {
            deny--;
            if (pos <= *deny) continue;
        }
        if (work.locked(1, 1, n, pos)) continue;

        if (i - pos > ans.second - ans.first)
            ans = mp(pos, i);
    }

    printf("%d %d %d", ans.second - ans.first + 1, ans.first, ans.second);

    return 0;
}
