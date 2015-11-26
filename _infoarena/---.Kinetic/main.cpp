#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define eps 1e-9

#define maxN 512
#define maxM 200011

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

Buffer fin("kinetic.in", 1 << 20);


//#define debug

int n, m, i, j, pos;
double a[maxN], b[maxN];
double x[maxM], y[maxM], t[maxM];

int id[maxN];
int id_pos[maxN];
int q_id[maxM];
vector< pair<pair<double, double>, int> > Events;

double x_act;
double y_act;
double t_act;

int ans[maxM];

bool cmp(int id1, int id2) {
    if (a[id1] == a[id2])
        return b[id1] < b[id2];
    return a[id1] > a[id2];
}

bool q_cmp(int id1, int id2) {
    return t[id1] < t[id2];
}

bool Equals(double a, double b) {
    return -eps <= a - b && a - b <= eps;
}

void solve_bucket() {
    double x_tr = Events[pos].first.first;
    double y_tr = Events[pos].first.second;

    int from = id_pos[Events[pos].second];
    int to = id_pos[Events[pos].second];

    while (pos != Events.size()) {
        if ( !Equals(Events[pos].first.first, x_tr) || !Equals(Events[pos].first.second, y_tr)) break;
        from = min(from, id_pos[Events[pos].second]);
        to = max(to, id_pos[Events[pos].second]);
        pos++;
    }

    while (from < to) {
        swap(id[from], id[to]);
        swap(id_pos[ id[from] ], id_pos[ id[to] ]);
        from++;
        to--;
    }
}

int binary(double x) {
    int ans = 0;

    for (int step = (1 << 9); step > 0; step >>= 1) {
        int to = step + ans;

        if (to <= n)
            if (a[ id[to] ] * t_act + b[ id[to] ] <= x + eps)
                ans = to;
    }

    return ans;
}

int main()
{
    //freopen("kinetic.in","r",stdin);
    freopen("kinetic.out","w",stdout);

    fin >> n >> m;
    for (i = 1; i <= n; i++)
        fin >> b[i] >> a[i];
    for (i = 1; i <= m; i++)
        fin >> x[i] >> y[i] >> t[i];

    for (i = 1; i <= n; i++)
        id[i] = i;
    sort(id + 1, id + n + 1, cmp);
    for (i = 1; i <= n; i++)
        id_pos[ id[i] ] = i;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (a[i] == a[j]) continue;

            double x_i = (b[i] - b[j]) / (a[j] - a[i]);
            double y_i = a[i] * x_i + b[i];

            Events.pb(mp(mp(x_i, y_i), i));
            Events.pb(mp(mp(x_i, y_i), j));
        }
    }

    sort(Events.begin(), Events.end());

    for (i = 1; i <= m; i++)
        q_id[i] = i;
    sort(q_id + 1, q_id + m + 1, q_cmp);

    for (i = 1; i <= m; i++) {
        x_act = x[ q_id[i] ];
        y_act = y[ q_id[i] ];
        t_act = t[ q_id[i] ];

        if (x_act > y_act) swap(x_act, y_act);

        while (pos != Events.size()) {
            if (Events[pos].first.first > t_act) break;
            solve_bucket();
        }

        #ifdef debug
            for (int kk = 1; kk < n; kk++) {
                double v1 = a[id[kk]] * t_act + b[id[kk]];
                double v2 = a[id[kk + 1]] * t_act + b[id[kk + 1]];

                if (v1 > v2) {
                    cerr << "Error";
                    exit(0);
                }
            }
        #endif

        ans[q_id[i]] = binary(y_act) - binary(x_act - 2 * eps);
    }

    for (i = 1; i <= m; i++)
        printf("%d\n", ans[i]);

    return 0;
}
