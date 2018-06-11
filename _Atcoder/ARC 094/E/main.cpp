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

const int maxN = 200011;

ll n, i;
ll A, B, ans, mm = 1LL << 60;
bool any;


int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> A >> B;
        if (A != B) any = true;
        ans += A;
        if (A > B) mm = min(mm, B);
    }

    if (!any) ans = 0;
    else      ans -= mm;
    cout << ans;


    return 0;
}
