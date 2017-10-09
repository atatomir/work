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

#define maxN 100011

int n, i, x;
int cnt, ans;

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> x;
        if (x == i) {
            cnt++;
        } else {
            ans += (cnt + 1) / 2;
            cnt = 0;
        }
    }

    ans += (cnt + 1) / 2;
    cout << ans;


    return 0;
}
