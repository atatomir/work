#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 500011
#define maxK 30011
#define lSon (node << 1)
#define rSon (lSon | 1)

template<class T> class Aint {
    public:
        void init(int _dim, T *_data, T *_adds, int *_prov) {
            dim = _dim;
            data = _data;
            adds = _adds;
            prov = _prov;

            make_tree(1, 1, dim);
        }

        void update(int node, int l, int r, int qL, int qR, T v) {
            if (prov[node] == 0) prov[node] = l;

            if (qL <= l && r <= qR) {
                adds[node] += v;
                data[node] += v;
                return;
            }

            int mid = (l + r) >> 1;
            if (qL <= mid)
                update(lSon, l, mid, qL, qR, v);
            if (qR >  mid)
                update(rSon, mid + 1, r, qL, qR, v);

            data[node] = min(data[lSon], data[rSon]) + adds[node];
            if (data[lSon] < data[rSon])
                prov[node] = prov[lSon];
            else
                prov[node] = prov[rSon];

            if (data[lSon] == data[rSon])
                prov[node] = prov[lSon];
        }

        T getBest() {
            return data[1];
        }

        int getProv() {
            return prov[1];
        }

    private:
        int dim;
        T *data;
        T *adds;
        int *prov;

        void make_tree(int node, int l, int r) {
            prov[node] = l;

            if (l == r) return;
            int mid = (l + r) >> 1;
            make_tree(lSon, l, mid);
            make_tree(rSon, mid + 1, r);
        }
};

int n, m, dx, dy, k, i;
int xx1[maxK], yy1[maxK], xx2[maxK], yy2[maxK], p[maxK];

Aint<long long> work;
long long aint_data[maxN << 2];
long long aint_adds[maxN << 2];
int aint_prov[maxN << 2];

vector<int> id;
long long ans = 1000000000000000;
int ans_pos_x, ans_pos_y;

bool cmp(int x, int y) {
    if (x < 0)
        x = xx1[-x];
    else
        x = xx2[x];

    if (y < 0)
        y = xx1[-y];
    else
        y = xx2[y];

    return x < y;
}

int getWhere(int x) {
    if (x < 0)
        return xx1[-x];
    else
        return xx2[x];
}

void getPosition(int x, int &_y1, int &_y2, int &_how) {
    if (x < 0) {
        x = -x;

        _y1 = yy1[x];
        _y2 = yy2[x];
        _how = p[x];
    } else {
        _y1 = yy1[x];
        _y2 = yy2[x];
        _how = -p[x];
    }
}

int main()
{
    freopen("demolish.in","r",stdin);
    freopen("demolish.out","w",stdout);

    scanf("%d%d%d%d%d", &n, &m, &k, &dx, &dy);
    work.init(m - dy + 1, aint_data, aint_adds, aint_prov);

    for (i = 1; i <= k; i++) {
        scanf("%d%d%d%d%d", &xx1[i], &yy1[i], &xx2[i], &yy2[i], &p[i]);

        xx1[i]++; yy1[i]++;
        xx2[i]++; yy2[i]++;

        xx1[i] = max(1, xx1[i] - dx + 1);
        yy1[i] = max(1, yy1[i] - dy + 1);
        xx2[i] = min(xx2[i], n - dx + 2);
        yy2[i] = min(yy2[i], m - dy + 2);

        id.pb(i);
        id.pb(-i);
    }
    id.pb(0);
    xx1[0] = 1; xx2[0] = 2;
    yy1[0] = 1; yy2[0] = 2;

    sort(id.begin(), id.end(), cmp);

    for (int i = 0; i < id.size(); ) {
        int who = id[i];
        int main_wh = getWhere(who);

        if (main_wh + dx > n + 1) break;

        int j = i;
        while (j < id.size()) {
            int wh = getWhere(id[j]);
            if (wh > main_wh) break;

            int y1_loc, y2_loc, how;
            getPosition(id[j], y1_loc, y2_loc, how);
            work.update(1, 1, m - dy + 1, y1_loc, y2_loc - 1, how);
            //cerr << "upd " << 1 << ' ' << m - dy + 1 << ' ' << y1_loc<< ' ' << y2_loc - 1 << ' ' << how << '\n';

            j++;
        }

        if (work.getBest() < ans) {
            ans = work.getBest();
            ans_pos_x = main_wh;
            ans_pos_y = work.getProv();
        }
        i = j;
    }

    printf("%lld\n%d %d %d %d", ans, ans_pos_x - 1, ans_pos_y - 1, ans_pos_x - 1 + dx, ans_pos_y - 1 + dy);


    return 0;
}
