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
#define ll long long
#define inf 1000000001

int n, i, t;
int v[maxN];
pair<int, pair<int, int>> ans;

int end_rat[maxN];
vector<int> aux[2];

void preproc() {
    int i;

    for (i = 1; i <= n; i++)
        end_rat[i] = 0;

    if (v[n - 1] >= v[n])
        return ;

    end_rat[n - 1] = v[n] - v[n - 1];
    for (i = n - 2; i > 0; i--) {
        if (v[i + 1] - v[i] != end_rat[i + 1]) return;
        end_rat[i] = end_rat[i + 1];
    }
}

bool must_attach(int id, int val) {
    if (aux[id].size() < 2)
        return true;

    int sz = aux[id].size();

    return val - aux[id][sz - 1] == aux[id][sz - 1] - aux[id][sz - 2];
}

void new_sol(int bg, int rat, int len) {
    ans = min(ans, mp(bg, mp(rat, len)));
}

bool can_connect(int pos) {
    if (end_rat[pos] == 0)
        return false;

    if (aux[1].size() == 0)
        return true;

    bool good = true;
    if (aux[1].size() > 1)
        if (aux[1][1] - aux[1][0] != end_rat[pos])
            good = false;

    return (v[pos] - aux[1][aux[1].size() - 1] == end_rat[pos]) && good;
}

void solve(vector<int> _fixed, vector<int> _run, int bg) {
    int i;

    aux[0] = _fixed;
    aux[1] = _run;
    v[n + 1] = -1;

    for (i = bg - 1; i <= n; i++) {
        //! add new element
        if (i >= bg)
        if (must_attach(0, v[i])) {
            aux[0].pb(v[i]);
        } else {
            if (must_attach(1, v[i]))
                aux[1].pb(v[i]);
            else
                return;
        }


        if (i == n) {
            if (aux[1].size() < 2) return;
            new_sol(aux[0][0], aux[0][1] - aux[0][0], aux[0].size());
            new_sol(aux[1][0], aux[1][1] - aux[1][0], aux[1].size());
        }

        if (i == n - 1) {
            if (must_attach(1, v[n])) {
                aux[1].pb(v[n]);

                if (aux[1].size() >= 2) {
                    new_sol(aux[0][0], aux[0][1] - aux[0][0], aux[0].size());
                    new_sol(aux[1][0], aux[1][1] - aux[1][0], aux[1].size());
                }

                aux[1].pop_back();
            }
        }

        if (i < n - 1) {
            if (can_connect(i + 1)) {
                new_sol(aux[0][0], aux[0][1] - aux[0][0], aux[0].size());
                if (aux[1].size())
                    new_sol(aux[1][0], end_rat[i + 1], aux[1].size() + n - i);
                else
                    new_sol(v[i + 1], end_rat[i + 1], n - i);
            }
        }
    }

}

int main()
{
    freopen("test.in","r",stdin);

    for(scanf("%d", &t); t; t--) {
        scanf("%d", &n);
        for (i = 1; i <= n; i++)
            scanf("%d", &v[i]);

        ans = mp(inf, mp(0, 0));

        preproc();

        if (v[2] > v[1]) solve({v[1], v[2]}, {}, 3);
        if (v[3] > v[1]) solve({v[1], v[3]}, {v[2]}, 4);
        if (v[3] > v[2]) solve({v[2], v[3]}, {v[1]}, 4);

        if (ans.first == inf)
            printf("-1\n");
        else
            printf("%d %d %d\n", ans.first, ans.second.first, ans.second.second);
    }




    return 0;
}
