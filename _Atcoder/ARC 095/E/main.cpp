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

const int maxN = 14;

int n, m, i, db, sg;
char s[maxN][maxN];
vector< vector<int> > data;
bool used[maxN];

int p[maxN];
vector< pair<string, string> > act;

void solve() {
    int i, j;
    string A, B;
    bool used = false;

    i = 1; j = n;
    for (auto e : data) {
        if (e.size() == 1) {
            p[(n + 1) / 2] = e[0];
        } else {
            p[i] = e[0];
            p[j] = e[1];
            i++; j--;
        }
    }

    act.clear();
    for (j = 1; j <= m; j++) {
        A.clear();
        for (i = 1; i <= n; i++) A.pb(s[p[i]][j]);

        B = A;
        reverse(B.begin(), B.end());

        act.pb(mp(A, B));
    }

    for (i = 0; i < act.size(); i++) {
        if (act[i].first.size() == 0) continue;

        for (j = i + 1; j < act.size(); j++) {
            if (act[j].first.size() == 0) continue;
            if (act[i].first == act[j].second) {
                act[j].first = "";
                break;
            }
        }

        if (j == act.size()) {
            if (act[i].first == act[i].second) {
                if (used) return;
                used = true;
            } else {
                return;
            }
        }
    }

    printf("YES");
    exit(0);
}

void get_combs() {
    if (db == 0 && sg == 0) {
        solve();
        return;
    }

    int i, j;
    for (i = 1; used[i]; i++);
    if (sg > 0) {
        sg--;
        data.pb({i});
        used[i] = true;

        get_combs();

        sg++;
        data.pop_back();
        used[i] = false;
    }

    if (db > 0) {
        for (j = i + 1; j <= n; j++) {
            if (used[j]) continue;

            db--;
            data.pb({i, j});
            used[i] = used[j] = true;

            get_combs();

            db++;
            data.pop_back();
            used[i] = used[j] = false;
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) scanf("%s\n", s[i] + 1);

    db = n / 2;
    sg = n % 2;
    get_combs();

    printf("NO");


    return 0;
}
