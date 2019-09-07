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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 5011;
const ll inf = 1LL << 60;

int n;
int p[maxN];
ll A, B; // A right, B left
ll on_left[maxN];
ll on_right[maxN];
ll dp[maxN];

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%lld%lld", &n, &A, &B);
    for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
    p[n + 1] = n + 1;

    dp[0] = 0;
    for (int i = 1; i <= n + 1; i++) {
        dp[i] = inf;

        for (int j = i - 1; j >= 0; j--) {
            if (p[j] < p[i]) {
                if (on_left[j] + on_right[i] != i - j - 1) continue;
                dp[i] = min(dp[i], dp[j] + on_left[j] * B + on_right[i] * A);
            } else {
                on_left[j]++;
                on_right[i]++; 
            }
        }
    }

    printf("%lld", dp[n + 1]);




    return 0;
}
