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
const int bts = 28;

int n, i;
int A[maxN], B[maxN];

int act;
vector<int> aux;
int ans, here;

int get(int act, int l, int r) {
    auto it1 = lower_bound(aux.begin(), aux.end(), l - act);
    auto it2 = lower_bound(aux.begin(), aux.end(), r - act);
    return it2 - it1;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) cin >> A[i];
    for (i = 1; i <= n; i++) cin >> B[i];

    for (int cnt = 0; cnt <= bts; cnt++) {
        aux.clear();
        for (i = 1; i <= n; i++)
            aux.pb(B[i] & ((1 << (cnt + 1)) - 1));
        sort(aux.begin(), aux.end());

        for (i = 1; i <= n; i++) {
            act = A[i] & ((1 << (cnt + 1)) - 1);
            here = get(act, 1 << cnt, 1 << (cnt + 1));
            here += get(act, (1 << cnt) + (1 << (cnt + 1)), 1 << (cnt + 2));
            ans ^= (here & 1) << cnt;
        }
    }

    cout << ans;


    return 0;
}
