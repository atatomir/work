#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxStr 1000011
#define maxN 500011
#define maxK 55

int k, i, n, act_lvl;
double limit[maxK];
char s[maxStr];

int cnt;
int tp[maxN], lvl[maxN];
stack<int> S;
vector<int> list[maxN];
vector<int> ord;

double ans[maxN];
vector<double> aux;
double sum, prod, need, test;
int sons;

double poww(double a, int b) {
    double ans = 1;

    while (b > 0) {
        if (b & 1) ans *= a;
        b >>= 1;
        a *= a;
    }

    return ans;
}

int main()
{
    //freopen("test.in","r",stdin);

    /*freopen("test.out", "w", stdout);
    printf("5\n10 10 10 10 10\n");
    for (i = 1; i <= 499999; i++) printf("(");
    printf("?");
    for (i = 1; i <= 499999; i++) printf(")");

    return 0;*/

    scanf("%d", &k);
    for (i = 1; i <= k; i++) scanf("%lf", &limit[i]);
    scanf("\n%s", s + 1);
    n = strlen(s + 1);


    for (i = 1; i <= n; i++) {
        if (s[i] == '(') {
            cnt++; lvl[cnt] = ++act_lvl;
            if (!S.empty()) list[S.top()].pb(cnt);
            S.push(cnt);
            continue;
        }

        if (s[i] == ')') {
            S.pop(); act_lvl--;
            continue;
        }

        if (s[i] == '+') {
            tp[S.top()] = 1;
            continue;
        }

        if (s[i] == '*') {
            tp[S.top()] = 2;
            continue;
        }
    }


    ord.resize(cnt);
    for (i = 1; i <= cnt; i++) ord[i - 1] = i;

    sort(ord.begin(), ord.end(), [](const int& a, const int& b)->bool const {
        return lvl[a] > lvl[b];
    });

    for (auto e : ord) {
        if (list[e].size() == 0) {
            ans[e] = limit[1];
            continue;
        }

        if (tp[e] == 1) {
            for (auto to : list[e])
                ans[e] += ans[to];
            ans[e] = min(ans[e], limit[list[e].size()]);
        } else {
            aux.clear();
            sum = 0; prod = 1;

            for (auto to : list[e])
                aux.pb(ans[to]), sum += ans[to], prod *= ans[to];

            sons = list[e].size();
            if (sum <= limit[sons]) {
                ans[e] = prod;
                continue;
            }

            need = limit[sons]; sum = 0; prod = 1;
            sort(aux.begin(), aux.end());

            for (i = 0; i < aux.size(); i++) {
                test = sum + aux[i] * (sons - i);
                if (test < need) {
                    sum += aux[i];
                    prod *= aux[i];
                    continue;
                }
                break;
            }

            if (i < aux.size()) {
                prod *= poww( (need - sum) / (1.00 * (sons - i)), sons - i );
                ans[e] = prod;
            }
        }
    }

    printf("%.9lf", ans[1]);

    return 0;
}
