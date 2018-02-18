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

int n, i;
int t, x, y;
int tt, xx, yy;

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> tt >> xx >> yy;

        int dt = abs(tt - t);
        int dx = abs(xx - x);
        int dy = abs(yy - y);

        if (dt < dx + dy) {
            cout << "No";
            return 0;
        }

        if ((dt - dx - dy) & 1) {
            cout << "No";
            return 0;
        }

        swap(xx, x);
        swap(yy, y);
        swap(tt, t);
    }

    cout << "Yes";

    return 0;
}
