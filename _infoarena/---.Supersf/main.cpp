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

#define maxN 200011
#define maxLen (maxN * 4)

struct Huge {
    int dim;
    int data[maxLen];
};

/* Set value v to H */
void set(Huge& H, int v) {
    if (v == 0) {
        H.dim = 1;
        H.data[1] = 0;
        return;
    }

    H.dim = 0;
    while (v) {
        H.data[++H.dim] = v & 1;
        v >>= 1;
    }
}

/* compare if H1 >= (H2 << delay) */
bool cmp(Huge& H1, Huge& H2, int delay) {
    int l1 = H1.dim;
    int l2 = H2.dim + delay;

    if (l1 > l2) return true;
    if (l1 < l2) return false;

    for (int i = H2.dim; i > 0; i--) {
        if (H1.data[delay + i] > H2.data[i]) return true;
        if (H1.data[delay + i] < H2.data[i]) return false;
    }

    return true;
}

/* substract (H2 << delay) from H1 */
void sub(Huge& H1, Huge &H2, int delay) {
    int i;

    for (i = H2.dim; i > 0; i--)
        H1.data[delay + i] -= H2.data[i];

    for (i = 1; delay + i <= H1.dim; i++) {
        if (H1.data[i + delay] >= 0) continue;
        H1.data[i + delay] += 2;
        H1.data[i + delay + 1]--;
    }

    while (H1.dim > 1 && H1.data[H1.dim] == 0) H1.dim--;
}

/* print in hexa */
void print(Huge& H) {
    int cnt = (H.dim + 3) / 4;
    for (int i = 4 * (cnt - 1); i >= 0; i -= 4) {
        int v = 0;

        if (H.data[i + 1]) v |= 1;
        if (H.data[i + 2]) v |= 2;
        if (H.data[i + 3]) v |= 4;
        if (H.data[i + 4]) v |= 8;

        if (v < 10)
            printf("%d", v);
        else
            printf("%c", 'A' + v - 10);
    }
}



int n, i, pos;
char s[maxN];

int bits;
Huge K, aux;
Huge ans;


int main()
{
    freopen("supersf.in","r",stdin);
    freopen("supersf.out","w",stdout);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    K.dim = n * 4; pos = 0;
    for (i = n; i >= 1; i--) {
        int v = ('0' <= s[i] && s[i] <= '9' ? s[i] - '0' : 10 + s[i] - 'A');

        K.data[++pos] = v & 1;
        K.data[++pos] = (v >> 1) & 1;
        K.data[++pos] = (v >> 2) & 1;
        K.data[++pos] = (v >> 3) & 1;
    }

    /* sub 1 */
    for (i = 1; K.data[i] == 0; K.data[i++] = 1);
    K.data[i] = 0;
    while (K.data[K.dim] == 0) K.dim--;

    /* compute answer */
    memset(ans.data, 0, sizeof(ans.data));
    ans.dim = maxLen - 1;

    bits = 0;
    for (i = K.dim; i >= 1; i--) {
        set(aux, 2 * bits + i);
        if (cmp(K, aux, i - 1) == false) continue;

        bits++;
        ans.data[i + 1] = 1;
        sub(K, aux, i - 1);
    }

    set(aux, bits);
    if (cmp(K, aux, 0) == true) {

        /* add 1 */

        for (i = 1; ans.data[i] == 1; ans.data[i++] = 0);
        ans.data[i] = 1;
        ans.dim = max(ans.dim, i);

    }


    while (ans.dim > 1 && ans.data[ans.dim] == 0) ans.dim--;
    print(ans);

    return 0;
}
