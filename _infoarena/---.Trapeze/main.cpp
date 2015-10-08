#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111
#define def_pr 7


#define def_dim 111

class BigNumber {
    public:
        void init() {
            dim = 1;
            memset(data, 0, sizeof(data));
            data[1] = 1;
        }

        void operator*=(int v) {
            for (int i = 1; i <= dim; i++) data[i] *= v;
            for (int i = 1; i <= dim; i++) {
                data[i + 1] += data[i] / 10;
                data[i] %= 10;

                if (data[dim + 1] != 0) dim++;
            }
        }

        void print() {
            for (int i = dim; i > 0; i--) printf("%d", data[i]);
        }

    private:
        int dim;
        int data[def_dim];
};

int n, i, j;
bool ciur[maxN];
vector<int> primes;
vector<int> divs;
double ans = 1e500;

int tmp[def_pr + 5];
int best[def_pr + 5];

BigNumber work;

void back(int pas, double act, int need) {
    if (act > ans) return;

    if (pas == primes.size()) {
        if (need != 1) return;

        ans = act;
        memcpy(best, tmp, sizeof(tmp));

        return;
    }

    for (auto who : divs) {
        if (need % who == 0) {
            tmp[pas] = who;
            back(pas + 1, act + log(primes[pas]) * (who - 1), need / who);
        }
    }
}

int main()
{
    freopen("trapeze.in","r",stdin);
    freopen("trapeze.out","w",stdout);

    scanf("%d", &n);

    for (i = 2; primes.size() != def_pr; i++) {
        if (ciur[i]) continue;
        if (i != 2) primes.pb(i);

        for (j = i * i; j < maxN; j += i) ciur[j] = true;
    }

    for (i = 1; i <= n; i++)
        if (n % i == 0)
            divs.pb(i);

    back(0, 0, n);

    work.init();
    for (i = 0; i < primes.size(); i++) {
        int pr = primes[i];
        int how = best[i] - 1;

        while (how-- > 0) {
            work *= pr;
        }
    }

    work.print();


    return 0;
}
