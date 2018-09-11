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

const int maxN = 100011;
const int let = 6;
const int inv = (1 << let) - 1;

char s[maxN];
int n, i, j, q, pos, k, rem;
int rest[maxN], cnt[1 << let];

int aux[1 << let];
char ans[maxN];

bool check() {
    for (int i = 1; i <= inv; i++) {
        if (cnt[i] > rem - aux[i ^ inv]) {
            return false;
        }
    }

    return true;
}


int get_busit() {
    int ans = inv;

    for (int i = 1; i <= inv; i++) {
        if (cnt[i] > rem - aux[i ^ inv]) {
            ans &= i;
        }
    }

    return ans;
}

void add_val(int x, int coef) {
    int cc = (inv ^ x);

    aux[x] += coef;
    for (int conf = cc; conf > 0; conf = (conf - 1) & cc)
        aux[x | conf] += coef;

}

void add_cnt(int x, int coef) {
    int cc = (inv ^ x);

    cnt[x] += coef;
    for (int conf = cc; conf > 0; conf = (conf - 1) & cc)
        cnt[x | conf] += coef;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%s\n%s", s + 1, &q);
    n = strlen(s + 1);

    for (i = 1; i <= n; i++)
        add_cnt(1 << (s[i] - 'a'), +1);

    for (i = 1; i <= q; i++) {
        
        for (j = 0; j <= 20; j++) s[j] = 0;

        scanf("%d %s", &pos, s + 1);
        k = strlen(s + 1);
        for (j = 1; j <= k; j++) rest[pos] |= 1 << (s[j] - 'a');
 

        if (k == 1) {
            ans[pos] = s[1];
            add_cnt(rest[pos], -1);
            rest[pos] = -1;
        }
    }

    for (i = 1; i <= n; i++) {
        if (rest[i] == -1) {
            rest[i] = 0;
            continue;
        }

        if (rest[i] == 0) rest[i] = inv;
        add_val(rest[i], +1);
        rem++;
    }

    if (!check()) {
        printf("Impossible");
        return 0;
    }


    for (i = 1; i <= n; i++) {
        if (rest[i] == 0) continue;

        add_val(rest[i], -1);
        rem--;

        rest[i] &= get_busit();

        for (j = 0; j < let; j++) {
            if (((rest[i] >> j) & 1) == 0) continue;
            
            add_cnt(1 << j, -1);
            ans[i] = 'a' + j;
            break;
        }
    }

    printf("%s", ans + 1);

    return 0;
}
