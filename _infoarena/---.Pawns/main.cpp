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

#define maxN 555

int n, m, i, j, x, y, t, ans;
vector<int> list[maxN];
int sg[maxN];

int compute(int node) {
    vector<int> aux;
    aux.clear();

    if (sg[node] != -1) return sg[node];

    sg[node] = 0;
    for (int to : list[node])
        aux.pb(compute(to));

    sort(aux.begin(), aux.end());
    aux.resize(unique(aux.begin(), aux.end()) - aux.begin());

    aux.pb(-1);
    for (int i = 0; i < aux.size(); i++) {
        if (aux[i] != i) {
            sg[node] = i;
            break;
        }
    }

    return sg[node];
}

int main()
{
    freopen("pawns.in","r",stdin);
    freopen("pawns.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) sg[i] = -1;
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
    }

    scanf("%d", &t);
    for (i = 1; i <= t; i++) {
        ans = 0;

        for (j = 1; j <= n; j++) {
            scanf("%d", &x);
            if (x & 1) {
                ans ^= compute(j);
            }
        }

        printf("%d\n", (ans > 0 ? 1 : 0));
    }



    return 0;
}
