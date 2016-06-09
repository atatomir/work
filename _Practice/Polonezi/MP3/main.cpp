#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <assert.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define inf 2000000011
#define tm anti_compilation_error

int n, limit, speed, i;
char press[maxN];
int tm[maxN];
vector<int> aux;

ll last;
bool valid[maxN];

int get_best() {
    int i, l, r;

    l = r = speed;
    for (i = n; i > 0; i--) {
        if (!valid[i]) continue;

        if (press[i] == '-') {
            if (l == limit) return -1;

            l = min(limit, l + 1);
            r = min(limit, r + 1);

            if (l == 1) l = 0;
        } else {
            if (r == 0) return -1;

            l = max(0, l - 1);
            r = max(0, r - 1);

            if (r == limit - 1) r = limit;
        }
    }

    return r;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d%d\n", &n, &limit, &speed);
    for (i = 1; i <= n; i++) scanf("%c %d\n", &press[i], &tm[i]), aux.pb(tm[i] - tm[i - 1] - 1);
    aux.pb(inf);

    sort(aux.begin(), aux.end());
    aux.resize(unique(aux.begin(), aux.end()) - aux.begin());
    reverse(aux.begin(), aux.end());

    for (int aux_t = 0; aux_t < aux.size(); aux_t++) {
        int T = aux[aux_t];

        //! set valid buttons
        last = -1;
        for (i = 1; i <= n; i++) {
            valid[i] = (tm[i] <= last);

            last = 0LL + tm[i] + T;
        }

        int best = get_best();
        if (best != -1) {
            if (T == inf)
                printf("infinity");
            else
                printf("%d %d", T, best);

            return 0;
        }
    }

    return 0;
}
