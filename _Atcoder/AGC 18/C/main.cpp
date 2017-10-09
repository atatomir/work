#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

int n, i;
ll X, Y, Z;
ll A[maxN], B[maxN], C[maxN];
ll sol, act, best;
ll le[maxN], ri[maxN];

vector<int> ord;
priority_queue<ll, vector<ll>, greater<ll> > H;

int main()
{
    freopen("test.in","r",stdin);

    cin >> X >> Y >> Z;
    n = X + Y + Z;
    for (i = 1; i <= n; i++) {
        cin >> A[i] >> B[i] >> C[i];
        sol += C[i];
        A[i] -= C[i];
        B[i] -= C[i];
        C[i] = 0;

        ord.pb(i);
    }

    sort(ord.begin(), ord.end(), [](int a, int b)->bool {
        return A[a] - B[a] < A[b] - B[b];
    });

    ord.pb(0);
    for (i = n; i > 0; i--) ord[i] = ord[i - 1];

    while (!H.empty()) H.pop();
    for (i = 1; i < Y; i++) H.push(B[ord[i]]), act += B[ord[i]];
    for (i = Y; i <= n; i++) {
        H.push(B[ord[i]]);
        act += B[ord[i]];
        if (i != Y) {
            act -= H.top();
            H.pop();
        }

        le[i] = act;
    }

    act = 0;
    while (!H.empty()) H.pop();
    for (i = n; i > n - X + 1; i--) H.push(A[ord[i]]), act += A[ord[i]];
    for (i = n - X + 1; i >= 1; i--) {
        H.push(A[ord[i]]);
        act += A[ord[i]];
        if (i != n - X + 1) {
            act -= H.top();
            H.pop();
        }

        ri[i] = act;
    }

    best = -(1LL << 60);
    for (i = Y; i + X <= n; i++)
        best = max(best, le[i] + ri[i + 1]);

    cout << best + sol;


    return 0;
}
