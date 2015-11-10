#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define pb push_back
#define mp make_pair

#define maxN 1055

int n, i, j, p;
int answer;
int pX[maxN], pY[maxN];
int how[maxN];

vector< pair<double, int> > aux;
int def[maxN << 1];

int ans;
int total;

double PI = acos(-1.00);

int abss(int x) {
    if (x > 0) return x;
    return -x;
}

int main()
{
    freopen("gold.in", "r", stdin);
    freopen("gold.out", "w", stdout);

    scanf("%d%d", &n, &p);
    for (i = 1; i <= n; i++) {
        scanf("%d", &how[i]);
        total += how[i];
    }
    for (i = 1; i <= n; i++) scanf("%d%d", &pX[i], &pY[i]);

    for (i = 1; i <= n; i++) {
        aux.clear();

        for (j = 1; j <= n; j++) {
            if (i == j) continue;
            aux.pb(mp( atan2(pY[j] - pY[i], pX[j] - pX[i]) , how[j]));
        }

        for (j = 1; j <= n; j++) {
            if (i == j) continue;
            aux.pb(mp( atan2(pY[j] - pY[i], pX[j] - pX[i]) + 2 * PI , how[j]));
        }

        sort(aux.begin(), aux.end());

        def[0] = aux[0].second;
        for (j = 1; j < aux.size(); j++) def[j] = aux[j].second + def[j - 1];

        int p1Lim = aux.size() / 2;
        int limit = aux.size();
        int p1, p2;
        p1 = p2 = 0;

        while (p1 < p1Lim) {
            while (p2 + 1 < limit && aux[p2 + 1].first <= aux[p1].first + PI) p2++;

            int v1 = def[p2] - def[p1];
            int v2 = total - how[i] - aux[p1].second - v1;

            if (abss(v1 - v2) <= p) ans++;

            p1++;
        }
    }

    printf("%d", ans / 2);

    return 0;
}
