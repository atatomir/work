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

#define maxN 100011

int n, low, high, i;

double sum[maxN];
bool sgn[maxN];

deque< pair<int, double> > Q[2]; //! 0 poz, 1 neg

double ans;
int pos_l, pos_r;

void add_to_queue(int id, pair<int, double> now) {
    while (!Q[id].empty()) {
        auto last = Q[id].back();

        if (last.second < now.second) break;
        Q[id].pop_back();
    }
    Q[id].push_back(now);
}

void remove_until(int id, int limit) {
    while (!Q[id].empty()) {
        auto last = Q[id].front();

        if (last.first >= limit) break;
        Q[id].pop_front();
    }
}

int main()
{
    freopen("secv4.in","r",stdin);
    freopen("secv4.out","w",stdout);

    scanf("%d%d%d", &n, &low, &high);
    for (i = 1; i <= n; i++) {
        scanf("%lf", &sum[i]);

        if (sum[i] < 0) {
            sgn[i] = true;
            sum[i] *= -1;
        }

        sum[i] = log(sum[i]) + sum[i - 1];
        sgn[i] ^= sgn[i - 1];
    }

    ans = - (1e18);

    for (i = 1; i <= n; i++) {
        //! add element i - low
        if (i - low >= 0) {
            if (sgn[i - low] == 0) //! positive
                add_to_queue(0, mp(i - low, sum[i - low]));
            else  //! negative
                add_to_queue(1, mp(i - low, sum[i - low]));
        }

        //! remove element i - high - 1
        remove_until(0, i - high);
        remove_until(1, i - high);

        if (!sgn[i]) { //! positive
            if (Q[0].empty() == true) goto out;

            auto now = Q[0].front();
            if (ans < sum[i] - now.second) {
                ans = sum[i] - now.second;
                pos_l = now.first + 1;
                pos_r = i;
            }

        } else { //! negative
            if (Q[1].empty() == true) goto out;

            auto now = Q[1].front();
            if (ans < sum[i] - now.second) {
                ans = sum[i] - now.second;
                pos_l = now.first + 1;
                pos_r = i;
            }
        }

        out: i++; i--;
    }


    printf("%d %d", pos_r - pos_l + 1, pos_l);

    return 0;
}
