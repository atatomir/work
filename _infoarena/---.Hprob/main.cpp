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
#define ll long long

int t, ti, n, i;
double p1, p2, p3, p4;
vector< vector<int> > P;
vector<int> aux;
vector<double> ini, ans;
map< vector<int>, int> M;

void pre(int step) {
    if (step == 4) {
        P.pb(aux);
        M[aux] = P.size() - 1;

        /*cerr << P.size() - 1 << ' ';
        for (auto e : aux)
            cerr << e << ' ';
        cerr << '\n';*/

        return;
    }

    for (int i = 1; i <= 4; i++) {
        bool found = false;
        for (auto e : aux)
            found |= (e == i);

        if (!found) {
            aux.pb(i);
            pre(step + 1);
            aux.pop_back();
        }
    }
}

int combine(int a, int b) {
    int i;

    for (i = 0; i < P[b].size(); i++)
        aux[i] = P[a][ P[b][i] - 1 ];

    /*for (auto e : aux)
        cerr << e << ' ';
    cerr << '\n';*/

    return M[aux];
}

vector<double> prod(const vector<double>& a, const vector<double>& b) {
    int i, j;
    static vector<double> ans;

    ans.resize(24);
    for (i = 0; i < ans.size(); i++) ans[i] = 0;

    for (i = 0; i < 24; i++) {
        for (j = 0; j < 24; j++) {
            ans[ combine(i, j) ] += a[i] * b[j];
        }
    }

    return ans;
}

void solve() {
    if (n == 0) {
        printf("1.00000\n");
        return;
    }

    n--;
    ans = ini;

    while (n) {
        if (n & 1) ans = prod(ans, ini);
        n >>= 1;
        ini = prod(ini, ini);
    }

    printf("%.5lf\n", ans[0]);
    return;
}



int main()
{
    freopen("hprob.in","r",stdin);
    freopen("hprob.out","w",stdout);

    pre(0);
    ini.resize(24);
    aux.resize(4);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%lf%lf%lf", &n, &p1, &p2, &p3);
        p4 = 1.00 - p1 - p2 - p3;

        for (i = 0; i < ini.size(); i++)
            ini[i] = 0;

        ini[18] = p1;
        ini[23] = p2;
        ini[2] = p3;
        ini[0] = p4;

        solve();
    }


    return 0;
}
