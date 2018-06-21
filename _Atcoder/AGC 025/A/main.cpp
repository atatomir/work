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

int n, i, ans;

int sum(int x) {
    int ans = 0;
    while (x > 0) {
        ans += x % 10;
        x /= 10;
    }
    return ans;
}

int main()
{
    cin >> n;
    ans = 1 << 30;
    for (i = 1; i < n; i++)
        ans = min(ans, sum(i) + sum(n - i));

    cout << ans;


    return 0;
}
