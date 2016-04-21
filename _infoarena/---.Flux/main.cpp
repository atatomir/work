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

#define maxN 111

struct gauss {
    vector< vector<double> > data;
    int ec, rez;
    const double eps = 1e-11;
    vector<double> solutions;

    bool equal(double a, double b) {
        a -= b;
        if (a < -eps || eps < a) return false;
        return true;
    }

    void init(int _ec, int _var) {
        ec = _ec; rez = _var + 1;
        data = vector< vector<double> >(ec + 3, vector<double>(rez + 3, 0));
    }

    void rm_gauss() {
        int i, j, k, l;

        i = 1; j = 1;
        while (i <= ec && j < rez) {
            int found = 0;
            for (k = i; k <= ec; k++)
                if (!equal(data[k][j], 0.00))
                    {found = k; break;}

            if (!found) {
                j++;
                continue;
            }

            swap(data[i], data[found]);
            for (k = i + 1; k <= ec; k++) {
                if (equal(data[k][j], 0.00)) continue;

                double delta = data[k][j] / data[i][j];
                for (l = j; l <= rez; l++) data[k][l] -= data[i][l] * delta;
            }

            i++; j++;
        }
    }

    bool solve() {
        int i, j, k;

        rm_gauss();
        solutions = vector<double>(rez + 3, 0.00);

        for (i = ec; i > 0; i--) {
            for (j = 1; j < rez && equal(data[i][j], 0.00); j++);
            if (j == rez) {
                if (!equal(data[i][rez], 0.00)) return false;
                continue;
            }

            int pos = j;
            solutions[pos] = data[i][rez];

            for (j++; j < rez; j++) {
                if (equal(data[i][j], 0.00)) continue;
                solutions[pos] -= data[i][j] * solutions[j];
            }

            solutions[pos] /= data[i][pos];
        }

        return true;
    }
};

int n, m, i, x, y, c;
vector< pair<int, int> > list[maxN];
gauss work;

double mn = 1e18;
double sumi = 0.00;

int main()
{
    freopen("flux.in","r",stdin);
    freopen("flux.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &c);
        list[x].pb(mp(y, c));
        list[y].pb(mp(x, c));
    }

    work.init(n, n);

    //! set node 1
    work.data[1][1] = 1.00;
    work.data[1][work.rez] = 0.00;

    //! set node n
    work.data[n][n] = 1.00;
    work.data[n][work.rez] = 1.00;

    //! set nodes 2..n - 1
    for (i = 2; i < n; i++) {
        for (auto to : list[i]) {
            work.data[i][i] += 1.00;
            work.data[i][to.first] -= 1.00;
        }
    }

    if(!work.solve()) cerr << "err";

    for (i = 1; i <= n; i++) {
        for (auto to : list[i]) {
            double act = work.solutions[to.first] - work.solutions[i];
            if (i == 1) sumi += act;
            if (act < 0) act *= -1;

            if (!work.equal(act, 0.00))
                mn = min(mn, (1.00 * to.second) / act );
        }
    }

    printf("%.5lf", mn * sumi);

    return 0;
}
