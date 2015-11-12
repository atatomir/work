#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 311

#define base 1000
#define lett 3
#define v_dim 357
char s[v_dim];
class bigNumber {
    public:
        void init() {
            dim = 1;
            memset(data, 0, sizeof(data));
            data[1] = 1;
        }

        void operator=(const bigNumber& who) {
            dim = who.dim;
            memcpy(data, who.data, sizeof(data));
        }

        void operator=(int val) {
            dim = 1;
            data[1] = val;
        }

        void operator-=(const bigNumber& who) {
            for (int i = 1; i <= dim; i++) data[i] -= who.data[i];
            for (int i = 1; i <= dim; i++) {
                while (data[i] < 0) {
                    data[i] += base;
                    data[i + 1]--;
                }
            }

            while (dim > 1 && data[dim] == 0) dim--;
        }

        void operator*=(int val) {
            for (int i = 1; i <= dim; i++) data[i] *= val;
            for (int i = 1; i <= dim; i++) {
                data[i + 1] += data[i] / base;
                data[i] %= base;
                if (data[dim + 1] != 0) dim++;
            }

            while (dim > 1 && data[dim] == 0) dim--;
        }

        void operator/=(int val) {
            if (val == 0) return;

            for (int i = dim; i > 0; i--) {
                data[i - 1] += (data[i] % val) * base;
                data[i] /= val;
            }

            while (dim > 1 && data[dim] == 0) dim--;
            data[0] = 0;
        }

        bool operator>=(const bigNumber& who) {
            if (dim > who.dim) return true;
            if (dim < who.dim) return false;

            for (int i = dim; i > 0; i--) {
                if (data[i] > who.data[i]) return true;
                if (data[i] < who.data[i]) return false;
            }

            return true;
        }

        void read() {
            init();
            data[1] = 0;

            s[0] = '0';
            scanf("%s\n", s + 1);
            int s_dim = strlen(s + 1);

            dim = (s_dim + lett - 1) / lett;
            for (int i = 1; i <= dim; i++) {
                int bg = s_dim - lett * i + 1 ;
                int en = s_dim - lett * (i - 1);

                bg = max(bg, 1);

                for (int j = bg; j <= en; j++) data[i] = data[i] * 10 + s[j] - '0';
            }
        }

    private:
        int dim;
        int data[v_dim];
};

//!-------------------------------------------

int n, i, m;
int baseA[maxN], baseB[maxN];

int how, now, step;
int aux[maxN];

bigNumber actA, actB, act, k;
int ans[maxN];

bool enough;

void compute_init() {
    actA.init();
    actB.init();

    if (baseA[ aux[1] ] <= step - 1) actA = 0;
    if (baseB[ aux[1] ] <= step - 1) actB = 0;

    for (int i = 2; i <= how; i++) {
        actA *= 1LL * (baseA[ aux[i] ] - (step + i - 2));
        actB *= 1LL * (baseB[ aux[i] ] - (step + i - 2));
    }

    act = actA;
    if (!enough) act -= actB;
}

void recompute(int pas) {
    actA /= 1LL * (baseA[ aux[i] ] - (step + pas - 2));
    actA *= 1LL * (baseA[ aux[i - 1] ] - (step + pas - 2));

    actB /= 1LL * (baseB[ aux[i] ] - (step + pas - 2));
    actB *= 1LL * (baseB[ aux[i - 1] ] - (step + pas - 2));

    act = actA;
    if (!enough) act -= actB;
}

int main()
{
    freopen("bubblesort.in","r",stdin);
    freopen("bubblesort.out","w",stdout);

    scanf("%d%d", &n, &m);
    k.read();

    how = n;
    for (i = 1; i <= how; i++) {
        aux[i] = i;
        baseA[i] = min(n, i + m - 1);
        baseB[i] = min(n, i + m - 2);
    }

    for (step = 1; step <= n; step++) {
        compute_init();

        if (act >= k) {
            now = 1;
        } else {
            k -= act;
            for (i = 2; i <= how; i++) {
                recompute(i);

                if (act >= k) {
                    now = i;
                    break;
                }

                k -= act;
            }
        }

        ans[step] = aux[now];
        for (i = now; i < how; i++) aux[i] = aux[i + 1];
        how--;

        if (step - ans[step] == m - 1) enough = true;
    }

    for (i = 1; i <= n; i++) printf("%d ", ans[i]);

    return 0;
}
