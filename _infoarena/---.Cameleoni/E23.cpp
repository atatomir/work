#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxState 20
#define mod 666013LL

ll aux1[maxState];
ll aux2[maxState];

class gigi {
    public:
        int pas;
        ll data[maxState];

        void init() {
            pas = 1;
            memset(data, 0, sizeof(data));
            data[1] = data[2] = data[4] = data[8] = 1;
        }

        void operator*=(gigi &who) {
            memcpy(aux1, data, sizeof(data));
            memcpy(aux2, who.data, sizeof(data));

            int i, j;
            memset(data, 0, sizeof(data));

            for (i = 0; i < 16; i++)
                for (j = 0; j < 16; j++)
                    data[i ^ j] = (data[i ^ j] + aux1[i] * aux2[j]) % mod;

            pas += who.pas;
        }
};

int n, i, target;
gigi aux, ans;
char ch1, ch2, ch3, ch4;

void poww() {
    ans = aux;
    n--;

    while (n) {
        if (n & 1) ans *= aux;
        n >>= 1;
        aux *= aux;
    }
}

int main()
{
    freopen("cameleoni.in", "r", stdin);
    freopen("cameleoni.out", "w", stdout);

    scanf("%d\n%c %c %c %c", &n, &ch1, &ch2, &ch3, &ch4);
    if (ch1 == 'G') target += 1;
    if (ch2 == 'G') target += 2;
    if (ch3 == 'G') target += 4;
    if (ch4 == 'G') target += 8;

    aux.init();
    poww();

    printf("%lld", ans.data[target]);

    return 0;
}
