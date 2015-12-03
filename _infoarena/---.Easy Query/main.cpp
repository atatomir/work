#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxLog 21
#define maxN 100011
#define lSon (node << 1)
#define rSon (lSon | 1)
#define inf 1000000000
#define dp_max dp_max_q[lvl]
#define dp_min dp_min_q[lvl]

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);

            reFill();
        }

        template<class T>
        Buffer& operator>>(T &who) {
            bool sign = false;

            while (!isDigit(data[pos]) && data[pos] != '-')
                if (++pos == dim) reFill();

            if (data[pos] == '-') {
                sign = true;
                if (++pos == dim) reFill();
            }

            who = 0;
            while (isDigit(data[pos])) {
                who = who * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }

            if (sign) who *= -1;
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool isDigit(char c) {
            return ('0' <= c && c <= '9');
        }

        void reFill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};

Buffer fin("eq.in", 1 << 20);

int n, m, i;
int v[maxN];
vector<int> Q[maxN << 2];
int qL[maxN << 1], qR[maxN << 1];
int ans[maxN << 1];

void addQuery(int node, int l, int r, int id) {
    int mid = (l + r) >> 1;
    if (qL[id] <= mid && mid <= qR[i]) {
        Q[node].pb(id);
        return;
    }

    if (mid < qL[id])
        addQuery(rSon, mid + 1, r, id);
    else
        addQuery(lSon, l, mid, id);
}

int dp_max_q[maxLog][maxN][7];
int dp_min_q[maxLog][maxN][7];

int myMax(vector<int> vals) {
    int ans = vals[0];
    for (auto v : vals)
        ans = max(ans, v);
    return ans;
}

int myMin(vector<int> vals) {
    int ans = vals[0];
    for (auto v : vals)
        ans = min(ans, v);
    return ans;
}

void solve(int node, int l, int r, int lvl) {
    int mid = (l + r) >> 1;

    if (Q[node].size() > 0) {
        //! solve now..
        //! two parts : [l, mid] - [mid + 1, r]
        int i, j;

        //! left side...

        dp_max[mid][0] = 0;
        dp_max[mid][1] = v[mid];
        dp_max[mid][2] = -v[mid];
        dp_max[mid][3] = 0;
        dp_max[mid][4] = v[mid];

        dp_min[mid][0] = 0;
        dp_min[mid][1] = v[mid];
        dp_min[mid][2] = -v[mid];
        dp_min[mid][3] = 0;
        dp_min[mid][4] = v[mid];

        dp_max[mid][6] = dp_min[mid][6] = v[mid];
        dp_max[mid][7] = dp_min[mid][7] = 0;

        for (i = mid - 1; i >= l; i--) {
            dp_max[i][0] = dp_max[i + 1][0];
            dp_max[i][1] = myMax({dp_max[i + 1][1], dp_max[i + 1][0] + v[i]});
            dp_max[i][2] = myMax({dp_max[i + 1][2], dp_max[i + 1][0] - v[i]});
            dp_max[i][3] = myMax({dp_max[i + 1][3], dp_max[i + 1][1] - v[i], dp_max[i + 1][2] + v[i], dp_max[i + 1][0]});
            dp_max[i][4] = myMax({dp_max[i + 1][4], dp_max[i + 1][3] + v[i], dp_max[i + 1][0] + v[i],
                                  dp_max[i + 1][1], dp_max[i + 1][2] + 2 * v[i]});

            dp_min[i][0] = dp_min[i + 1][0];
            dp_min[i][1] = myMin({dp_min[i + 1][1], dp_min[i + 1][0] + v[i]});
            dp_min[i][2] = myMin({dp_min[i + 1][2], dp_min[i + 1][0] - v[i]});
            dp_min[i][3] = myMin({dp_min[i + 1][3], dp_min[i + 1][1] - v[i], dp_min[i + 1][2] + v[i], dp_min[i + 1][0]});
            dp_min[i][4] = myMin({dp_min[i + 1][4], dp_min[i + 1][3] + v[i], dp_min[i + 1][0] + v[i],
                                  dp_min[i + 1][1], dp_min[i + 1][2] + 2 * v[i]});

            dp_max[i][6] = max(dp_max[i + 1][6], v[i]);
            dp_min[i][6] = min(dp_min[i + 1][6], v[i]);

            dp_max[i][7] = max(dp_max[i + 1][7], v[i] - dp_min[i][1]);
            dp_min[i][7] = min(dp_min[i + 1][7], v[i] - dp_max[i][1]);
        }

        //! right side...
        mid++;

        dp_max[mid][0] = 0;
        dp_max[mid][1] = v[mid];
        dp_max[mid][2] = 2 * v[mid];
        dp_max[mid][3] = 0;
        dp_max[mid][4] = v[mid];

        dp_min[mid][0] = 0;
        dp_min[mid][1] = v[mid];
        dp_min[mid][2] = 2 * v[mid];
        dp_min[mid][3] = 0;
        dp_min[mid][4] = v[mid];

        dp_max[mid][6] = dp_min[mid][6] = v[mid];

        for (i = mid + 1; i <= r; i++) {
            dp_max[i][0] = dp_max[i - 1][0];
            dp_max[i][1] = myMax({dp_max[i - 1][1], dp_max[i - 1][0] + v[i]});
            dp_max[i][2] = myMax({dp_max[i - 1][2], dp_max[i - 1][1] + v[i], dp_max[i - 1][0] + 2 * v[i]});
            dp_max[i][3] = myMax({dp_max[i - 1][3], dp_max[i - 1][1] - v[i], dp_max[i - 1][0]});
            dp_max[i][4] = myMax({dp_max[i - 1][4], dp_max[i - 1][2] - v[i], dp_max[i - 1][3] + v[i],
                                  dp_max[i - 1][1], dp_max[i - 1][0] + v[i]});

            dp_min[i][0] = dp_min[i - 1][0];
            dp_min[i][1] = myMin({dp_min[i - 1][1], dp_min[i - 1][0] + v[i]});
            dp_min[i][2] = myMin({dp_min[i - 1][2], dp_min[i - 1][1] + v[i], dp_min[i - 1][0] + 2 * v[i]});
            dp_min[i][3] = myMin({dp_min[i - 1][3], dp_min[i - 1][1] - v[i], dp_min[i - 1][0]});
            dp_min[i][4] = myMin({dp_min[i - 1][4], dp_min[i - 1][2] - v[i], dp_min[i - 1][3] + v[i],
                                  dp_min[i - 1][1], dp_min[i - 1][0] + v[i]});

            dp_max[i][6] = max(dp_max[i - 1][6], v[i]);
            dp_min[i][6] = min(dp_min[i - 1][6], v[i]);
        }

        //! now solve actual queries
        for (auto now : Q[node]) {
            int maxi = -inf;
            int mini = +inf;

            int ll = qL[now];
            int rr = qR[now];

            if (mid - 1 == rr) {
                ans[now] = dp_max[ll][4] + dp_min[ll][4];
                continue;
            }

            if (mid == ll) {
                ans[now] = dp_max[rr][4] + dp_min[rr][4];
                continue;
            }

            maxi = max(maxi, dp_max[ll][4]);
            maxi = max(maxi, dp_max[rr][4]);
            maxi = max(maxi, 2 * dp_max[ll][6] - dp_min[rr][6]);
            maxi = max(maxi, dp_max[ll][6] + dp_max[rr][6] - dp_min[rr][6]);
            maxi = max(maxi, dp_max[ll][7] + dp_max[rr][1]);

            mini = min(mini, dp_min[ll][4]);
            mini = min(mini, dp_min[rr][4]);
            mini = min(mini, 2 * dp_min[ll][6] - dp_max[rr][6]);
            mini = min(mini, dp_min[ll][6] + dp_min[rr][6] - dp_max[rr][6]);
            mini = min(mini, dp_min[ll][7] + dp_min[rr][1]);

            ans[now] = maxi + mini;
        }
    }

    mid = (l + r) >> 1;

    if (l == r) return;
    solve(lSon, l, mid, lvl + 1);
    solve(rSon, mid + 1, r, lvl + 1);
}

void brute(int id) {
    if (qR[id] - qL[id] == 0) {
        ans[id] = 2 * v[ qL[id] ];
        return;
    }

    ans[id] = myMax({v[ qL[id] ], 2 * v[ qL[id] ] - v[ qL[id] + 1], v[ qL[id] + 1] }) +
              myMin({v[ qL[id] ], 2 * v[ qL[id] ] - v[ qL[id] + 1], v[ qL[id] + 1] }) ;
}

int main()
{
    //freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);

    fin >> n >> m;
    for (i = 1; i <= n; i++)
        fin >> v[i];

    for (i = 1; i <= m; i++) {
        fin >> qL[i] >> qR[i];

        addQuery(1, 1, n, i);

        ans[i] = 0;
    }

    solve(1, 1, n, 1);
    for (i = 1; i <= m; i++)
        printf("%d\n", ans[i]);

    return 0;
}
