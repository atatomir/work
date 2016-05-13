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

#define maxN 30011
#define dim 9
#define mod 997
#define lSon (node << 1)
#define rSon (lSon | 1)

int k; //! is used in struct matrix

struct matrix {
    int n, m;
    int data[dim][dim];

    void clear(int _n, int _m) {
        n = _n; m = _m;
        memset(data, 0, sizeof(data));
    }

    matrix operator*(matrix who) {
        int i, j, k;
        matrix ans;
        ans.clear(n, who.m);

        for (i = 1; i <= n; i++)
            for (j = 1; j <= who.m; j++) {
                for (k = 1; k <= m; k++)
                    ans.data[i][j] = ans.data[i][j] + data[i][k] * who.data[k][j];
                ans.data[i][j] %= mod;
            }


        return ans;
    }
};

class aint {
    public:
        void init(int _n, matrix *_data, matrix *_from) {
            n = _n;
            data = _data;
            from = _from;

            build(1, 1, n);
        }

        void update(int node, int l, int r, int pos, matrix& new_matrix) {
            if (l == r) {
                data[node] = new_matrix;
                return;
            }

            int mid = (l + r) >> 1;
            if (pos <= mid)
                update(lSon, l, mid, pos, new_matrix);
            else
                update(rSon, mid + 1, r, pos, new_matrix);

            data[node] = data[lSon] * data[rSon];
        }

        matrix query(int node, int l, int r, int qL, int qR) {
            if (qL <= l && r <= qR)
                return data[node];

            matrix ans; ans.clear(k, k);
            bool done = false;
            int mid = (l + r) >> 1;

            if (qL <= mid)
                ans = query(lSon, l, mid, qL, qR), done = true;

            if (qR >  mid)
                if (done)
                    ans = ans * query(rSon, mid + 1, r, qL, qR);
                else
                    ans = query(rSon, mid + 1, r, qL, qR);

            return ans;
        }


    private:
        int n;
        matrix *data, *from;

        void build(int node, int l, int r) {
            if (l == r) {
                data[node] = from[l];
                return;
            }

            int mid = (l + r) >> 1;
            build(lSon, l, mid);
            build(rSon, mid + 1, r);

            data[node] = data[lSon] * data[rSon];
        }
};

int n, i, j, l, t, X, Y;
int pos, cnt, p1, p2, pp1, pp2, o1, o2;
char ch;

matrix act[maxN];
matrix aint_data[maxN << 2];
aint work;

matrix aux;

int main()
{
    freopen("namlei.in","r",stdin);
    freopen("namlei.out","w",stdout);

    scanf("%d%d", &n, &k);
    scanf("%d%d", &X, &Y); X %= k; Y %= k;

    //! read initial state
    for (i = 1; i <= n; i++) {
        act[i].clear(k, k);

        for (l = 1; l <= k; l++)
            for (t = 1; t <= k; t++)
                act[i].data[l][t] = 1;

        scanf("%d%d%d", &cnt, &p1, &p2);
        for (j = 1; j <= cnt; j++) {
            act[i].data[p1 + 1][p2 + 1]++;

            pp1 = p1; pp2 = p2;
            p1 = (pp1 * X + pp2 * j * Y) % k;
            p2 = (pp1 * j * X + pp2 * Y) % k;
        }
    }

    work.init(n, aint_data, act);
    scanf("\n");

    while (true) {
        ch = '}';
        scanf("%c", &ch);

        if (ch == 'U') {
            scanf("%d%d%d%d\n", &pos, &cnt, &p1, &p2);
            pos++; i = pos;

            act[i].clear(k, k);

            for (l = 1; l <= k; l++)
                for (t = 1; t <= k; t++)
                    act[i].data[l][t] = 1;

            scanf("%d%d%d", &cnt, &p1, &p2);
            for (j = 1; j <= cnt; j++) {
                act[i].data[p1 + 1][p2 + 1]++;

                pp1 = p1; pp2 = p2;
                p1 = (pp1 * X + pp2 * j * Y + 1) % k;
                p2 = (pp1 * j * X + pp2 * Y + 1) % k;
            }

            work.update(1, 1, n, i, act[i]);

            continue;
        }

        if (ch == 'Q') {
            scanf("%d%d%d%d\n", &p1, &o1, &p2, &o2); o1++; o2++;

            p1++;
            aux.clear(1, k); aux.data[1][o1] = 1;

            aux = aux * work.query(1, 1, n, p1, p2);
            printf("%d\n", aux.data[1][o2]);

            continue;
        }

        break;
    }


    return 0;
}
