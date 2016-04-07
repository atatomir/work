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

#define maxN 16001

struct aib {
    int data[maxN];

    int zrs(int x) {
        return (x ^ (x - 1)) & x;
    }

    void add(int pos, int v) {
        while (pos < maxN) {
            data[pos] += v;
            pos += zrs(pos);
        }
    }

    int sum(int pos) {
        int ans = 0;

        while (pos) {
            ans += data[pos];
            pos -= zrs(pos);
        }

        return ans;
    }

    int cb(int v) {
        //! first element equal to v
        int ans = 0;

        for (int step = (1 << 14); step; step >>= 1)
            if (ans + step < maxN)
                if ( data[ans + step] < v )
                    ans += step, v -= data[ans];

        return ans + 1;
    }
};

int n, m, i, x, aux, nod;
vector<int> list[maxN];
int cnt;

int dr[maxN];
int dr_l[maxN], dr_r[maxN];

int st[maxN];
int st_l[maxN], st_r[maxN];

aib work_st, work_dr;
vector<int> order;

int id[maxN];
char type[maxN];

int ans[maxN];


void dfs_st(int node) {
    st[++cnt] = node;
    st_l[node] = cnt;

    for (int i = list[node].size() - 1; i >= 0; i--)
        dfs_st(list[node][i]);

    st_r[node] = cnt;
}

void dfs_dr(int node) {
    dr[++cnt] = node;
    dr_l[node] = cnt;
    order.pb(node);

    for (int to : list[node])
        dfs_dr(to);

    dr_r[node] = cnt;
}



int main()
{
    freopen("omizi.in","r",stdin);
    freopen("omizi.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        for (scanf("%d", &x); x != 0; scanf("%d", &x))
            list[i].pb(x);

    cnt = 0;
    dfs_st(1);
    cnt = 0;
    dfs_dr(1);

    memset(work_st.data, 0, sizeof(work_st.data));
    memset(work_dr.data, 0, sizeof(work_dr.data));

    for (i = 1; i <= n; i++) {
        work_st.add(i, +1);
        work_dr.add(i, +1);
    }

    reverse(order.begin(), order.end());

    for (i = 1; i <= m; i++) {
        scanf("%d", &x);
        scanf(" %c\n", &type[x]);
        id[x] = i;
    }

    for (int node : order) {
        if (id[node] == 0) continue;

        if (type[node] == 'S') { //! left
            aux = work_st.sum(st_r[node]);
            aux = work_st.cb(aux);

            nod = st[aux];

            ans[ id[node] ] = nod;
            work_st.add(st_l[nod], -1);
            work_dr.add(dr_l[nod], -1);
        } else {
            aux = work_dr.sum(dr_r[node]);
            aux = work_dr.cb(aux);

            nod = dr[aux];

            ans[ id[node] ] = nod;
            work_st.add(st_l[nod], -1);
            work_dr.add(dr_l[nod], -1);
        }
    }

    for (i = 1; i <= m; i++) printf("%d\n", ans[i]);

    return 0;
}
