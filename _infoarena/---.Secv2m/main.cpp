#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long
#define inf 10000000000

#define maxN 2016
#define pii pair<int, pair<int, int> >
#define mpp(a,b,c) mp(a,mp(b, c))

int n, m, l, i;
int A[maxN], B[maxN], work[maxN];
pii ans = mpp(inf, 0, 0);
deque<int> DQ;

void solve(int p1, int p2) {
    int p_start = p1;

    work[p1] = A[p1] + B[p2];
    while (!DQ.empty()) DQ.pop_back();
    DQ.pb(p1);

    for (p1++, p2++; p1 <= n && p2 <= m; p1++, p2++) {
        work[p1] = A[p1] + B[p2];

        while (!DQ.empty()) {
            if (work[ DQ.back() ] > work[p1]) break;
            DQ.pop_back();
        }

        DQ.push_back(p1);
        if (DQ.front() + l <= p1) DQ.pop_front();

        //! test actual solution
        if (p1 - p_start + 1 >= l) ans = min(ans, mpp( work[DQ.front()], p1 - l + 1, p2 - l + 1 ));
    }
}

int main()
{
    freopen("secv2m.in","r",stdin);
    freopen("secv2m.out","w",stdout);

    scanf("%d%d%d", &n, &m, &l);
    for (i = 1; i <= n; i++) scanf("%d", &A[i]);
    for (i = 1; i <= m; i++) scanf("%d", &B[i]);

    solve(1, 1);
    for (i = 2; i <= n; i++) solve(i, 1);
    for (i = 2; i <= m; i++) solve(1, i);

    printf("%d\n%d %d\n", ans.first, ans.second.first, ans.second.second);

    return 0;
}
