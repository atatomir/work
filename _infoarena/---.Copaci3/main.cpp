#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <assert.h>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111

//! min SlidingWindow
class SlidingWindow {
    public:
        void init() {
            while (!data.empty()) data.pop_back();
        }

        void add(int pos, long long val) {
            while (!data.empty()) {
                auto last = data.back();
                if (last.second < val) break;
                data.pop_back();
            }
            data.push_back(mp(pos, val));
        }

        void remove(int pos) {
            while (!data.empty()) {
                auto last = data.front();
                if (last.first > pos) break;
                data.pop_front();
            }
        }

        long long getBest() {
            assert( data.empty() == false );
            return data.front().second;
        }

    private:
        deque< pair<int, long long> > data;
};

int n, i, D;
int Height[maxN];
vector<int> Useful;

int so,de;
long long dp[2][maxN * maxN * 2];

int w_left, w_right;
SlidingWindow work;

int abss(int x) {
    return (x < 0?-x : x);
}

int main()
{
    freopen("copaci3.in","r",stdin);
    freopen("copaci3.out","w",stdout);

    scanf("%d%d", &n, &D);
    for (i = 1; i <= n; i++) {
        scanf("%d", &Height[i]);

        for (int aux = -n; aux <= n; aux++) Useful.pb( Height[i] + aux * D );
    }

    if ( 1LL * abss(Height[1] - Height[n]) > 1LL * (n - 1) * D ) {
        printf("-1");
        return 0;
    }

    sort(Useful.begin(), Useful.end());
    Useful.resize(unique(Useful.begin(), Useful.end()) - Useful.begin());

    memset(dp, 0, sizeof(dp));
    so = 0; de = 1;

    for (i = 0; i < Useful.size(); i++)
        if (Useful[i] != Height[1])
            dp[so][i] = 1LL << 55;

    for (int pas = 2; pas <= n; pas++) {
        work.init();
        w_left = 0; w_right = -1;

        for (i = 0; i < Useful.size(); i++) {
            int h_act = Useful[i];

            while (w_right + 1 < Useful.size()) {
                int value = Useful[w_right + 1];
                if (value - h_act > D) break;

                w_right++;
                work.add(w_right, dp[so][w_right]);
            }
            while (w_left < w_right) {
                int value = Useful[w_left];
                if (h_act - value <= D) break;

                work.remove(w_left);
                w_left++;
            }

            dp[de][i] = abss(Height[pas] - h_act);
            dp[de][i] += work.getBest();
        }

        swap(so, de);
    }

    for (i = 0; i < Useful.size(); i++)
        if (Useful[i] == Height[n]) break;
    printf("%lld", dp[so][i]);

    return 0;
}
