#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 615
#define maxK 30011

struct Steal {
    int x_be, x_en;
    int y_be, y_en;

    void read() {
        scanf("%d%d%d%d", &x_be, &y_be, &x_en, &y_en);
    }
};

int n, m, k, i;
int Q[maxN];
Steal Upd[maxK];

void solve(int line, int pos, int dim) {
    if (Q[line] >= pos) Q[line] += dim;
}

int main()
{
    freopen("camion.in","r",stdin);
    freopen("camion.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &k, &Q[1]);
    for (i = 2; i <= n; i++) Q[i] = Q[1];

    for (i = 1; i <= k; i++) Upd[i].read();
    for (i = k; i >= 1; i--) {
        for (int line = Upd[i].x_be; line <= Upd[i].x_en; line++)
            solve(line, Upd[i].y_be, Upd[i].y_en - Upd[i].y_be + 1);
    }

    for (i = 1; i <= n; i++)
        if (Q[i] <= m)
            printf("%d\n", Q[i]);
        else
            printf("0\n");


    return 0;
}
