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
#define pii pair<int, int>
#define inf 1000000000

int n, i, tr_x, tr_y;
vector< pii > A, B;
vector< vector<int> > op;
int _sin, _cos;

void get_set(vector< pii >& dest) {
    int x, y;
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        dest.pb(mp(x, y));
    }
}

pii _rotate(pii P) {
    return mp(P.first * _cos - P.second * _sin, P.first * _sin + P.second * _cos);
}

bool check() {
    vector< pii > aux;

    aux = B;
    for (auto p : A)
        aux.pb(mp(p.first + tr_x, p.second + tr_y));

    sort(aux.begin(), aux.end());
    return (aux.begin() - unique(aux.begin(), aux.end()) == -n);
}

int main()
{
    freopen("simetrii.in","r",stdin);
    freopen("simetrii.out","w",stdout);

    _sin = 1;
    _cos = 0;

    scanf("%d", &n);
    get_set(A);
    get_set(B);

    pii min_b = mp(inf, inf);
    for (auto p : B) min_b = min(min_b, p);

    int aux = 0;
    for (int ang = 0; ang <= 360; ang += 90) {
        op.clear();
        op.pb({1, 0, 0, ang});

        pii mini = mp(inf, inf);
        for (auto p : A) mini = min(mini, p);

        tr_x = min_b.first - mini.first;
        tr_y = min_b.second - mini.second;
        op.pb({0, tr_x, tr_y});

        if (check()) {
            printf("%d\n", op.size());
            for (auto now : op) {
                for (auto e : now)
                    printf("%d ", e);
                printf("\n");
            }

            return 0;
        }

        for (i = 0; i < A.size(); i++)
            A[i] = _rotate(A[i]);
    }

    printf("-1");
    return 0;
}
