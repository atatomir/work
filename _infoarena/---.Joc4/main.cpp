#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 501
#define In(x) (x)
#define Out(x) (x + n)

int n, m, i, j, x, y, S, D;
char cap[maxN][maxN];
char flux[maxN][maxN];
vector<short> list[maxN];
bool us[maxN];
short prov[maxN];
queue<short> Q;
int ans;

void addArc(int x, int y, int _cap) {
    list[x].pb(y);
    list[y].pb(x);

    cap[x][y] = _cap;
    cap[y][x] = 0;
}

bool Flux() {
    memset(us, 0, sizeof(us));
    while (!Q.empty()) Q.pop();

    us[S] = true; Q.push(S);
    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        if (node == D) continue;

        for (auto to : list[node]) {
            if (us[to] || flux[node][to] == cap[node][to]) continue;

            prov[to] = node;
            us[to] = true;
            Q.push(to);
        }
    }

    if (us[D] == false) return false;

    for (auto from : list[D]) {
        if (!us[from]) continue;

        int flow = 1;

        prov[D] = from;
        for (int node = D; node != S; node = prov[node])
            flow = min(flow, cap[ prov[node] ][node] - flux[ prov[node] ][node] );
        for (int node = D; node != S; node = prov[node]) {
            flux[ prov[node] ][node] += flow;
            flux[node][ prov[node] ] -= flow;
        }

        ans += flow;
    }

    return true;
}

int main()
{
    freopen("joc4.in","r",stdin);
    freopen("joc4.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &S, &D);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);

        if (x == S || y == S) {
            if (x == D || y == D) { //! de la S la D
                addArc(S, D, 1);
            } else { //! de la S la ceva
                if (x != S) swap(x, y);
                addArc(S, In(y), 1);
            }
        }
        if (x == D || y == D) { //! de la ceva la S
            if (y != D) swap(x, y);
            addArc(Out(x), D, 1);
        }

        addArc(Out(x), In(y), 1);
        addArc(Out(y), In(x), 1);
    }

    for (i = 1; i <= n; i++)
        if (i != S && i != D)
            addArc(In(i), Out(i), 1);

    while (Flux()) ;

    printf("%d", ans);

    return 0;
}
