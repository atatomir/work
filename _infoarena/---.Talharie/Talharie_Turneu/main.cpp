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
#define ll long long

#define maxN 200011

int n, t, k, i;
char s[maxN];
int pos;
bool start[maxN];
vector<int> aux;

bool keep_left(int pos1, int pos2) {
    int dim = pos2 - pos1;

    for (int i = 0; i < dim; i++) {
        if (s[pos1 + i] < s[pos2 + i])
            return true;
        if (s[pos1 + i] > s[pos2 + i])
            return false;
    }
    return true;
}

int solve() {
    int i, dim;

    memset(start, 0, sizeof(start));

    i = 0;
    while (start[i] == false) {
        start[i] = true;
        i += k; i %= n;
    }

    aux.clear();
    for (i = 0; i < n; i++)
        if (start[i])
            aux.pb(i);

    while (aux.size() > 1) {
        int last = 0;

        if (aux.size() % 2 == 1) {
            last = aux[ aux.size() - 1 ];
            aux.pop_back();
        }
        dim = 0;

        for (i = 0; i < aux.size(); i += 2) {
            if (keep_left(aux[i], aux[i + 1]))
                aux[dim++] = aux[i];
            else
                aux[dim++] = aux[i + 1];
        }

        aux.resize(dim);
        if (last)
            aux.pb(last);
    }

    return aux[0];
}

int main()
{
    freopen("talharie.in","r",stdin);
    freopen("talharie.out","w",stdout);

    for (scanf("%d\n", &t); t > 0; t--) {
        memset(s, 0, sizeof(s));
        scanf("%d %d %s\n", &n, &k, s);

        for (i = 0; i < n; i++)
            s[n + i] = s[i];

        pos = solve();

        s[n] = '\0';
        printf("%s", s + pos);
        s[pos] = '\0';
        printf("%s\n", s);
    }


    return 0;
}
