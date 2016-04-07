#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

int n, i, x, lim;
int elsie[maxN];
int f_card[maxN];
int l_card[maxN];
int my_card[maxN];
bool us[maxN];

int pos_f, pos_l, pos_my;
vector<int> good_left;
vector<int> good_right;
int ans;

int solve(int lim) {
    int i;

    memset(us, 0, sizeof(us));
    pos_f = pos_l = pos_my = 0;
    ans = 0;

    for (i = 1; i <= lim; i++) {
        x = elsie[i];
        us[x] = true;
        f_card[++pos_f] = x;
    }
    for (i = lim + 1; i <= n; i++) {
        x = elsie[i];
        us[x] = true;
        l_card[++pos_l] = x;
    }

    sort(f_card + 1, f_card + pos_f + 1);
    sort(l_card + 1, l_card + pos_l + 1);
    for (i = 1; i <= 2 * n; i++) {
        if (us[i] == false) {
            my_card[++pos_my] = i;
        }
    }

    good_left.clear();
    good_right.clear();
    for (i = pos_l; i > 0; i--)
        good_right.pb( l_card[i] );

    pos_f = 0;
    for (i = 1; i <= n; i++) {
        int act_card = my_card[i];

        while (pos_f < lim && f_card[pos_f + 1] < act_card)
                good_left.pb(f_card[++pos_f]);
        while (good_right.empty() == false) {
            int _last = good_right[ good_right.size() - 1 ];
            if (_last > act_card) break;
            good_right.pop_back();
        }

        if (good_right.empty() == false) {
            good_right.pop_back();
            ans++;
        } else
        if (good_left.empty() == false) {
            good_left.pop_back();
            ans++;
        }
    }

    return ans;

}

int sol;
int maxi, mini;

int main()
{
    freopen("cardgame.in","r",stdin);
    freopen("cardgame.out","w",stdout);

    maxi = mini = 1;

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &elsie[i]);

        if (elsie[i] > elsie[maxi])
            maxi = i;
        if (elsie[i] < elsie[mini])
            mini = i;
    }

    sol = max(sol, solve(0));
    sol = max(sol, solve(n));

    sol = max(sol, solve(mini));
    sol = max(sol, solve(mini - 1));

    sol = max(sol, solve(maxi));
    sol = max(sol, solve(maxi - 1));

    if (mini != n)
        sol = max(sol, solve(mini + 1));
    if (maxi != n)
        sol = max(sol, solve(maxi + 1));

    /*for (i = 0; i <= n; i++) {
        sol = max(sol, solve(i));
        cerr << i << ' ' << solve(i) << '\n';
    }*/

    printf("%d", sol);

    return 0;
}
