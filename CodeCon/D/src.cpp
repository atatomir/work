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

ostream& operator<<(ostream& cerr, vector<int> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 111;

int n, k, d, i, j, ans = 1;
int g[maxN];

void check(int conf) {
    int i, j;
    vector<int> aux = {};
    vector<int> here = {};



    for (i = 0; i < n; i++) 
        if ((conf >> i) & 1)
            aux.pb(i), here.pb(g[i + 1]);


    for (i = 1; i < aux.size(); i++)
        if (aux[i] - aux[i - 1] < d)
            return;

    sort(here.begin(), here.end());
    here.resize(unique(here.begin(), here.end()) - here.begin());
    ans = max(ans, (int)here.size());

}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> k >> d;
    for (i = 1; i <= n; i++) cin >> g[i];

    for (int conf = (1 << n) - 1; conf > 0; conf--)
        check(conf);

    cout << ans;

    return 0;
}
