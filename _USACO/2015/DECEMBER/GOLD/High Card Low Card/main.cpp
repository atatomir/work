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
int f_card[maxN];
int l_card[maxN];
int my_card[maxN];
bool us[maxN];

int pos_f, pos_l, pos_my;
vector<int> good_left;
vector<int> good_right;
int ans;

int main()
{
    freopen("cardgame.in","r",stdin);
    freopen("cardgame.out","w",stdout);

    scanf("%d", &n); lim = n / 2;
    for (i = 1; i <= lim; i++) {
        scanf("%d", &x);
        us[x] = true;
        f_card[++pos_f] = x;
    }
    for (i = 1; i <= lim; i++) {
        scanf("%d", &x);
        us[x] = true;
        l_card[++pos_l] = x;
    }

    sort(f_card + 1, f_card + lim + 1);
    sort(l_card + 1, l_card + lim + 1);
    for (i = 1; i <= 2 * n; i++) {
        if (us[i] == false) {
            my_card[++pos_my] = i;
        }
    }

    good_left.clear();
    for (i = lim; i > 0; i--)
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

    printf("%d", ans);

    return 0;
}
