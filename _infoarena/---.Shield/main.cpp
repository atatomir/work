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

#define maxN 100011

int n, l, i;
pair<int, int> pos[maxN], intr[maxN];
int x, y;

pair<int, int> intersection(pair<int, int> a, pair<int, int> b) {
    return mp(max(a.first, b.first), min(a.second, b.second));
}

void print(int cnt, char c) {
    for (int i = 1; i <= cnt; i++)
        printf("%c", c);
}

int main()
{
    freopen("shield.in","r",stdin);
    freopen("shield.out","w",stdout);

    scanf("%d%d", &n, &l);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &pos[i].first, &pos[i].second);
    }

    sort(pos + 1, pos + n + 1);
    reverse(pos + 1, pos + n + 1);

    intr[1] = mp(pos[1].second - l + 1, pos[1].second);
    for (i = 2; i <= n; i++) {
        int dif = pos[i - 1].first - pos[i].first;
        intr[i] = intersection(mp(pos[i].second - l + 1, pos[i].second),
                              mp(intr[i - 1].first - dif, intr[i - 1].second + dif));
    }

    x = y = 1;
    for (i = n; i > 0; i--) {
        int l = intr[i].first;
        int r = intr[i].second;
        int h = pos[i].first;

        if (l <= x && x <= r) {
            print(h - y, 'S');
        } else {
            if (x < l) {
                print(l - x, 'R');
                print(h - y - (l - x), 'S');
                x = l;
            } else {
                print(x - r, 'L');
                print(h - y - (x - r), 'S');
                x = r;
            }
        }

        y = h;
    }



    return 0;
}
