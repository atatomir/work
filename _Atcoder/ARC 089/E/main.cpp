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

const int val = 100;

int A, B, i, j, n, m;
int v[maxN][maxN];
int least[maxN][maxN];
vector< pair<pair<int, int>, int> > edges;

void execute(int x, int y, int need) {
    int i, j;

    for (i = 0; i <= val; i++)
        for (j = 0; j <= val; j++)
            least[i][j] = max(least[i][j], need - (x * i + y * j));

}

bool check(int x, int y, int need) {
    int i, j;

    int act = 1 << 30;

    for (i = 0; i <= val; i++)
        for (j = 0; j <= val; j++)
            act = min(act, i * x + j * y + least[i][j]);

    if (act != need) return false;
    return true;
}

void add_edge(int x, int y, int v) {
    edges.pb(mp(mp(x, y), v));
    m++;
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);

    cin >> A >> B;
    for (i = 1; i <= A; i++) {
        for (j = 1; j <= B; j++) {
            cin >> v[i][j];

            execute(i, j, v[i][j]);
        }
    }

    for (i = 1; i <= A; i++) {
        for (j = 1; j <= B; j++) {
            if (!check(i, j, v[i][j])) {
                cout << "Impossible";
                return 0;
            }
        }
    }

    cout << "Possible\n";

    add_edge(1, 2, 0);
    for (i = 2; i + 1 <= val + 2; i++)
        add_edge(i, i + 1, -1);

    for (i = val + 3; i + 1 <= 2 * val + 3; i++)
        add_edge(i + 1, i, -2);

    add_edge(val + 3, 2 * val + 4, 0);

    for (i = 0; i <= val; i++)
        for (j = 0; j <= val; j++)
            add_edge(i + 2, j + val + 3, least[i][j]);

    n = 2 * val + 4;

    cout << n << ' ' << m << '\n';
    for (auto e : edges) {
        cout << e.first.first << ' ' << e.first.second << ' ';
        if (e.second == -1) cout << "X\n";
        if (e.second == -2) cout << "Y\n";
        if (e.second >= 0) cout << e.second << "\n";
    }

    cout << 1 << ' ' << n;


    return 0;
}
