#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 111;

int n, i, p;
pair<int, int> A[maxN], B[maxN];
multiset<int> S;
int ans;

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) cin >> A[i].first >> A[i].second;
    for (i = 1; i <= n; i++) cin >> B[i].first >> B[i].second;

    sort(A + 1, A + n + 1);
    sort(B + 1, B + n + 1);

    for (i = 1; i <= n; i++) {
        while (p + 1 <= n && A[p + 1] <= B[i]) {
            S.insert(A[p + 1].second);
            p++;
        }

        auto it = S.lower_bound(B[i].second);
        if (it != S.begin()) {
            it--;
            ans++;
            S.erase(it);
        }
    }

    cout << ans;

    return 0;
}
