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

#define maxN 33

int n, l, i, j;
vector< pair<int, int> > aux, act, now;
vector<int> perm;
int how[33];
int sol[33][33];

int ar;

void check() {
    int i, j, t1, t2;

    now.clear();
    for (auto e : perm) now.pb(act[e - 1]);

    memset(sol, 0, sizeof(sol));
    for (i = 1; i <= l; i++) {
        for (j = 1; j <= l; j++) {
            if (sol[i][j]) continue;

            if (i + now.back().first - 1 > l) return;
            if (j + now.back().second - 1 > l) return;

            for (t1 = i; t1 < i + now.back().first; t1++) {
                for (t2 = j; t2 < j + now.back().second; t2++) {
                    if (sol[t1][t2]) return;
                    sol[t1][t2] = now.size();
                }
            }

            now.pop_back();
        }
    }

    for (i = 1; i <= l; i++, cerr << '\n')
        for (j = 1; j <= l; j++)
            cerr << sol[i][j] << ' ';

    for (i = 1; i <= l; i++)
        for (j = 1; j <= l; j++)
            printf("%d", sol[i][j] - 1);

    exit(0);
}

void test_solution() {
    int i, j;
    int area = 0;

    if (ar != l * l) return;

    memset(how, 0, sizeof(how));
    for (auto e : act) {
        area += e.first * e.second;
        if (++how[e.first] > 1) return;
        if (++how[e.second] > 1) return;
    }

    if (area != l * l) return;

    perm.clear();
    for (i = 0; i < act.size(); i++) perm.pb(i + 1);

    do {
        check();
    } while (next_permutation(perm.begin(), perm.end()));
}

void solve(int pas, int cnt) {
    if (cnt == n) {
        test_solution();
        return;
    }

    for (int i = pas; i + (n - cnt - 1) < aux.size(); i++) {
        act.pb(aux[i]);
        ar += aux[i].first * aux[i].second;
        solve(i + 1, cnt + 1);
        ar -= aux[i].first * aux[i].second;
        act.pop_back();
    }
}

int main()
{
    freopen("badea.in","r",stdin);
    freopen("badea.out","w",stdout);

    scanf("%d%d", &n, &l);
    for (i = 2; i <= 2 * l; i++) {
        for (j = 1; j < i && j <= l; j++) {
            if (i - j == j) continue;
            if (i - j > l) continue;
            aux.pb(mp(j, i - j));
        }
    }

    solve(0, 0);


    return 0;
}
