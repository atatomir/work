#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define lSon (node << 1)
#define rSon (lSon | 1)
#define def 100000

template<class T> class Aint {
    public:
        void init(int _dim, T *_data, T *_lazy) {
            dim = dim;
            data = _data;
            lazy = _lazy;
        }

        void update(int node, int l, int r, int qL, int qR, T val) {
            if (qL <= l && r <= qR) {
                lazy[node] += val;
                compute(node, l == r);
                return;
            }

            int mid = (l + r) >> 1;
            if (qL <= mid)
                update(lSon, l, mid, qL, qR, val);
            if (qR >  mid)
                update(rSon, mid + 1, r, qL, qR, val);

            compute(node, l == r);
        }

        T getBest() {
            return data[1];
        }

    private:
        int dim;
        T *data;
        T *lazy;

        void compute(int node, bool leaf) {
            if (leaf) {
                data[node] = lazy[node];
                return;
            }

            data[node] = lazy[node] + max(data[lSon], data[rSon]);
        }
};

int dx, dy;
int n, i, j;
pair<int, int> Points[maxN];

Aint<int> work;
int aint_data[maxN << 2], aint_lazy[maxN << 2];
int dpL[maxN], dpR[maxN];
int ans;

void magic() {
    sort(Points + 1, Points + n + 1);
    memset(aint_data, 0, sizeof(aint_data));
    memset(aint_lazy, 0, sizeof(aint_lazy));
    work.init(def, aint_data, aint_lazy);

    j = 1;
    for (i = 1; i <= n; i++) {
        work.update(1, 1, def, Points[i].second, min(Points[i].second + dy, def), +1);

        while (Points[j].first < Points[i].first - dx) {
            work.update(1, 1, def, Points[j].second, min(Points[j].second + dy, def), -1);
            j++;
        }

        dpL[i] = max(dpL[i - 1], work.getBest());
    }

    //! --------------------------------------------

    memset(aint_data, 0, sizeof(aint_data));
    memset(aint_lazy, 0, sizeof(aint_lazy));
    work.init(def, aint_data, aint_lazy);

    j = n;
    for (i = n; i >= 1; i--) {
        work.update(1, 1, def, Points[i].second, min(Points[i].second + dy, def), +1);

        while (Points[j].first > Points[i].first + dx) {
            work.update(1, 1, def, Points[j].second, min(Points[j].second + dy, def), -1);
            j--;
        }

        dpR[i] = max(dpR[i + 1], work.getBest());
    }

    //! ---------------------------------------------
    j = 0;
    for (i = 1; i <= n; i++) {
        while (Points[j + 1].first != Points[i].first) j++;
        ans = max(ans, dpL[j] + dpR[i]);
    }
}

int main()
{
    freopen("parcele.in","r",stdin);
    freopen("parcele.out","w",stdout);

    scanf("%d%d", &dx, &dy);
    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d%d", &Points[i].first, &Points[i].second);

    //! vertical line
    magic();

    //! horizontal line
    for (i = 1; i <= n; i++) swap(Points[i].first, Points[i].second);
    swap(dx, dy);
    magic();

    printf("%d", ans);

    return 0;
}
