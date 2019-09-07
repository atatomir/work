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

const int maxN = 111;

int n;
int a[maxN];
vector<int> sol;

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int tms = 1; tms <= n; tms++) {
        int i;
        for (i = n - tms + 1; i > 0 && a[i] != i; i--);
        if (i == 0) {
            cout << -1;
            return 0;
        }

        sol.pb(i);
        for (int j = i; j <= n - tms; j++) 
            a[j] = a[j + 1];
    }

    reverse(sol.begin(), sol.end());
    for (auto e : sol) cout << e << '\n';


    return 0;
}
