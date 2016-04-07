#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

struct Point {
    int x, y;
};

struct Trie {
    map<int, Trie*> son;
    int cnt;

    Trie() {
        son.clear();
        cnt = 0;
    }
};

int n, i, j, pos;
Point P[maxN];
int dist[maxN], from_start[maxN];
int whole;

int edge[maxN];

vector<int> work;
Trie *R;
int ans1, ans2;

int get_dist(Point a, Point b) {
    int ans = a.x - b.x + a.y - b. y;
    if (ans < 0) ans = -ans;
    return ans;
}

int get_edge(Point a, Point b, Point c) {
    b.x -= a.x;
    b.y -= a.y;

    c.x -= a.x;
    c.y -= a.y;

    int aux = b.x * c.y - b.y * c.x;
    if (aux < 0)
        return -1;
    else
        return -1;
}

int solve() {
    P[0] = P[n];
    P[n + 1] = P[1];

    for (i = 2; i <= n; i++)
        dist[i] = dist[i - 1] + get_dist(P[i - 1], P[i]);
    whole = dist[n] + get_dist(P[1], P[n]);
    for (i = 2; i <= n; i++) {
        from_start[i] = dist[i];
        dist[i] = min(dist[i], whole - dist[i]);
    }

    for (i = 2; i <= n; i++)
        edge[i] = get_edge(P[i - 1], P[i], P[i + 1]);
    edge[1] = edge[n + 1] = -3;

    work.clear();
    for (i = 1; i <= n; i++) {
        work.pb(edge[i]);
        work.pb(get_dist(P[i], P[i + 1]));
    }
    work.pb(edge[1]);

    //! add possib
    R = new Trie();

    pos = 0;
    for (i = 1; i <= n; i++, pos += 2) {

        Trie *act = R;
        for (j = pos; j < work.size(); j++) {
            if (act->son[ work[j] ] == NULL)
                act->son[ work[j] ] = new Trie();

            act = act->son[ work[j] ];
            act->cnt++;
        }
    }

    int ans = 0;

    for (i = 2; i <= n; i++) {
        if (from_start[i] == whole - from_start[i]) continue;

        int aux;
        if (from_start[i] < whole - from_start[i]) { //! invers trigo
            aux = whole - from_start[i];

            Trie *act = R;
            int id = 2 * i - 2;
            int step = -1;

            for (j = id; act != NULL; j++) {
                if(work[j] < 0) step++;

                act = act->son[ work[j] ];
                if (act == NULL) break;

                if (act->cnt == 1 && j % 2 == 0) {
                    aux = min(aux, dist[i + step] + from_start[i + step] - from_start[i]);
                    break;
                }
            }

            ans = max(ans, aux - dist[i]);
        }
    }


    return ans;
}

int main()
{
    freopen("lightsout.in","r",stdin);
    freopen("lightsout.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].x, &P[i].y);
    }

    ans1 = solve();

    i = 2;
    j = n;
    while (i < j) {
        swap(P[i], P[j]);
        i++; j--;
    }

    ans2 = solve();

    cerr << ans1 << ' ' << ans2;

    printf("%d", min(ans1, ans2));


    return 0;
}
