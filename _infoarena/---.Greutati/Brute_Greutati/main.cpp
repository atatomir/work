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

const int limit = 1000011;
const int def = 1000000;

int n, p, i, j, x, y, sum;
bool ok[limit];
int ans;

void add(int x) {
    int i;

    sum += x;
    for (i = min(def, sum - x); i >= 0; i--)
        ok[i + x] |= ok[i];
}

int main()
{
    freopen("greutati.in","r",stdin);
    freopen("greutati.ok","w",stdout);

    cin >> n >> p;
    ok[0] = true;

    for (i = 1; i <= n; i++) {
        cin >> x >> y;
        while (y > 0) {
            y--;
            add(1 << x);
        }
    }

    ans = 1 << 30;
    for (i = 0; i <= sum && i <= def; i++)
        if (ok[i])
            ans = min(ans, abs(i - (sum - i)));

    cout << ans;



    return 0;
}
