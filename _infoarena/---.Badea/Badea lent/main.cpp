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

#define maxN 44

int n, l, i, j;
bool us[maxN];
vector<int> dims;
int area;

int sol[maxN][maxN];

void test_solution() {
    static int i, j, t1, t2, d1, d2, step;
    static bool ok;

    memset(sol, 0, sizeof(sol));
    ok = true; step = 0;

    for (i = 1; i <= l && ok; i++) {
        for (j = 1; j <= l; j++) {
            if (sol[i][j]) continue;

            d1 = dims[step];
            d2 = dims[step + 1];
            step += 2;

            if (i + d1 - 1 > l) ok = false;
            if (j + d2 - 1 > l) ok = false;
            if (!ok) break;

            for (t1 = i; t1 < i + d1; t1++) {
                for (t2 = j; t2 < j + d2; t2++) {
                    if (sol[t1][t2]) ok = false;
                    sol[t1][t2] = step / 2;
                }
            }
        }
    }

    if (ok) {
        for (i = 1; i <= l; i++) {
            for (j = 1; j <= l; j++) {
                printf("%d", sol[i][j] - 1);
                cerr << sol[i][j] << ' ';
            }
            cerr << '\n';
        }

        exit(0);
    }
}

void brute() {
    if (area > l * l) return;

    if (dims.size() == 2 * n) {
        int cnt = 10;

        if (area == l * l)
        while(cnt--) {
            test_solution();
            random_shuffle(dims.begin(), dims.end());
        }
        return;
    }

    for (int i = 1; i <= l; i++) {
        if (us[i]) continue;

        us[i] = true;
        if (dims.size() % 2 == 1) area += dims.back() * i;
        dims.pb(i);

        brute();

        us[i] = false;
        dims.pop_back();
        if (dims.size() % 2 == 1) area -= dims.back() * i;
    }
}

int main()
{
    freopen("badea.in","r",stdin);
    freopen("badea.out","w",stdout);

    scanf("%d%d", &n, &l);
    brute();


    return 0;
}
