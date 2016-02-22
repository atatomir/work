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

#define maxN 333
#define maxDim 111

class number {
    public:
        void init() {
            dim = 1;
            memset(data, 0, sizeof(data));
            data[1] = 1;
        }

        void operator*=(int nr) {
            int i;

            for (i = 1; i <= dim; i++) data[i] *= nr;
            for (i = 1; i <= dim; i++) {
                data[i + 1] += data[i] / 10;
                data[i] %= 10;
            }

            if (data[dim + 1]) dim++; //! only for *= 2
        }

        void incr() {
            data[1]++;
            for (int i = 1; i <= dim; i++) {
                data[i + 1] += data[i] / 10;
                data[i] %= 10;
            }

            if (data[dim + 1]) dim++;
        }

        void print() {
            for (int i = dim; i > 0; i--)
                printf("%d", data[i]);
            printf("\n");
        }

    private:
        int dim;
        int data[maxDim];
};

int n, i, now, diff, pow_num;
int S[maxN], P[maxN];

int min_sum;
vector<int> hard;
vector<int> maybe;

pair<int, int> best = mp(-2, -1);
int who = -1;

number _up, _down;

void try_bet(int bet) {
    if (bet > now) return;

    int _low = now - bet;
    int _high = now + bet;

    pair<int, int> ans = mp(-1, -1);

    //! try with _low
    if (_low > min_sum) {
        auto it = lower_bound(hard.begin(), hard.end(), _low);
        ans.second = it - hard.begin();
    }

    //! try with _high
    if (_high > min_sum) {
        auto it = lower_bound(hard.begin(), hard.end(), _high);
        ans.first = it - hard.begin();
    }

    if (ans > best) {
        best = ans;
        who = bet;
    }
}

int main()
{
    freopen("tvshow.in","r",stdin);
    freopen("tvshow.out","w",stdout);

    scanf("%d", &n); n--;
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &S[i], &P[i]);
        min_sum = max(min_sum, S[i] - P[i]);
        hard.pb(S[i] + P[i]);
        maybe.pb(S[i] - P[i]);
        maybe.pb(S[i] + P[i]);
    }
    scanf("%d", &now);

    sort (hard.begin(), hard.end());
    sort (maybe.begin(), maybe.end());

    try_bet(0);
    for (auto e : maybe)
        if (e >= now)
            try_bet(e + 1 - now);

    printf("%d\n", who);
    if (best == mp(-1, -1)) {
        printf("0\n1\n");
        return 0;
    }

    if (best.second != -1) {
        diff = best.second;
        best.first -= diff;
        best.second -= diff;
        pow_num = n + 1 - diff;
    } else {
        pow_num = n + 1 - best.first;
        best.first = 0;
    }

    _up.init();
    for (i = 1; i <= best.first; i++) _up *= 2;
    if (best.second != -1) _up.incr();

    _down.init();
    for (i = 1; i <= pow_num; i++) _down *= 2;

    _up.print();
    _down.print();

    return 0;
}
