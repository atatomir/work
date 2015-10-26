#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair

#define maxN 100011

int n, m, i, x, y, z;
int base[maxN], aux[maxN];
vector< pair<int, int> > work;
int steps;

bool good(int id, int ind) {
    id = work[id].second - work[id].first;
    if (id == 0) return true;
    if (ind < 0 && id > 0) return false;
    if (ind > 0 && id < 0) return false;
    return true;
}

void rebulk() {
    memcpy(aux, base, sizeof(aux));

    int pos = 1;
    for (int i = 0; i < work.size(); i++) {
        int from = work[i].first;
        int to   = work[i].second;

        if (to == -1) continue;

        int ind = (from < to ? 1 : -1);
        to += ind;
        for (int j = from; j != to; j += ind) {
            base[pos++] = aux[j];
        }
    }

    work.clear();
    work.pb(mp(1, n));
}

int abss(int x) {
    if (x < 0) return -x;
    return x;
}

void swap_content(int x, int y) {
    int whX, whY, howX, howY, i;

    for (i = 0; i < work.size(); i++) {
        int l = work[i].first;
        int r = work[i].second;

        if (r == -1) continue;

        int dim = abss(l - r) + 1;
        if (x > 0 && x <= dim) {
            whX = i;
            howX = x;
        }
        if (y > 0 && y <= dim) {
            whY = i;
            howY = y;
        }

        x -= dim;
        y -= dim;
    }

    //!----------------------------------------
    int n = work.size();
    work.resize(n + 2);
    for (i = n; i > whY; i--) work[i + 1] = work[i - 1];
    for (i = whY; i >= whX; i--) work[i + 1] = work[i];
    whY++;
    whX++;

    if (whX == whY) {
        int from = work[whX].first;
        int to   = work[whY].second;
        int ind = (from < to ? +1 : -1);

        work[whX - 1] = mp(from, from + howX * ind - 2 * ind);
        work[whY + 1] = mp(from + howY * ind, to);
        work[whX] = mp(from + howX * ind - ind, from + howY * ind - ind);

        if (!good(whX - 1, ind)) work[whX - 1] = mp(-1, -1);
        if (!good(whY + 1, ind)) work[whY + 1] = mp(-1, -1);
    } else {
        int from = work[whX].first;
        int to   = work[whX].second;
        int ind = (from < to ? +1 : -1);

        work[whX - 1] = mp(from, from + howX * ind - 2 * ind);
        work[whX] = mp(from + howX * ind - ind, to);
        if (!good(whX - 1, ind)) work[whX - 1] = mp(-1, -1);

        from = work[whY].first;
        to   = work[whY].second;
        ind = (from < to ? +1 : -1);

        work[whY + 1] = mp(from + howY * ind, to);
        work[whY] = mp(from, from + howY * ind - ind);
        if (!good(whY + 1, ind)) work[whY + 1] = mp(-1, -1);
    }

    while (whX < whY) {
        swap(work[whX], work[whY]);
        swap(work[whX].first, work[whX].second);
        swap(work[whY].first, work[whY].second);

        whX++; whY--;
    }

    if (whX == whY) swap(work[whX].first, work[whX].second);
}

int get_element(int x) {
    for (int i = 0; i < work.size(); i++) {
        int l = work[i].first;
        int r = work[i].second;

        if (r == -1) continue;

        int dim = abss(l - r) + 1;
        if (dim >= x) {
            int ind = (l < r ? +1 : -1);
            return base[ l + ind * x - ind ];
        }

        x -= dim;
    }
}

int main()
{
    freopen("rev.in", "r", stdin);
    freopen("rev.out", "w", stdout);

    scanf("%d%d", &n, &m);

    for (i = 1; i <= n; i++) base[i] = i;
    work.pb(mp(1, n));

    int def = int(sqrt(m)) + 1;
    steps = def;
    for (; m > 0; m--) {
        scanf("%d%d%d", &x, &y, &z);

        swap_content(x, y);
        printf("%d\n", get_element(z));

        if (--steps == 0) {
            steps = def;
            rebulk();
        }
    }

    return 0;
}
