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
int n, i, x;
bool us[maxN];
vector<int> Elsie;
vector<int> Bessie;
int ans;

int main()
{
    freopen("highcard.in","r",stdin);
    freopen("highcard.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        us[x] = true;
        Elsie.pb(x);
    }
    sort(Elsie.begin(), Elsie.end());

    for (i = 1; i <= 2 * n; i++)
        if (!us[i])
            Bessie.pb(i);

    int pos = 0;
    for (auto card : Elsie) {
        while (pos != n) {
            if (Bessie[pos] > card) break;
            pos++;
        }

        if (pos == n) break;
        pos++;
        ans++;
    }

    printf("%d", ans);

    return 0;
}
