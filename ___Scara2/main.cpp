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

#define maxN 14

int n, i, m, p, h, how;
double dp[1 << maxN];
vector<int> order[1 << maxN];


int act_sum;
vector<int> def, now;
int def_state, now_state;

double best;
int id;

void _back(int pos) {
    if (pos == n) {
        if (now.empty()) return;

        int comb = def_state | now_state;
        double act_cost = dp[def_state] + p + (1.00 * act_sum) / (1.00 * now.size());
        if (dp[comb] == 0 || dp[comb] > act_cost) {
            dp[comb] = act_cost;
            order[comb] = order[def_state];
            for (auto e : now)
                order[comb].pb(e);
        }

        return;
    }

        _back(pos + 1);

    now_state ^= 1 << pos;
    now.pb(pos + 1);
    act_sum += pos + 1;
    if (act_sum <= n) _back(pos + 1);
        now.pop_back();
    act_sum -= pos + 1;
    def_state ^= 1 << pos;

    def_state ^= 1 << pos;
    def.pb(pos + 1);
        _back(pos + 1);
    def.pop_back();
    def_state ^= 1 << pos;


}

bool better(int A, int B) {
    for (int i = 0; ; i++)
        if (order[A] < order[B]) return true;
        else
        if (order[A] > order[B]) return false;
}

int main()
{
    freopen("scara2.in","r",stdin);
    freopen("scara2.out","w",stdout);

    scanf("%d%d%d%d", &h, &how, &n, &p);
    _back(0);

    best = 1000.00 ;
    for (int state = 0; state < (1 << n); state++) {
        if (order[state].size() != how ) continue;

        if (best > dp[state]) {
            best = dp[state];
            id = state;
        } else
        if (best == dp[state]) {
            if (better(state, best)) {
                best = dp[state];
                id = state;
            }
        }
    }

    printf("%.2lf\n", best);
    for (auto e : order[id])
        printf("%d ", e);

    return 0;
}
