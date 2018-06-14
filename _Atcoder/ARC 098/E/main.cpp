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

const int maxN = 2018;

int n, k, q, i, j, ans;
int a[maxN];
vector<int> v, glob, loc;

void execute() {
    if (loc.size() < k) {
        loc.clear();
        return;
    }

    nth_element(loc.begin(), loc.begin() + (loc.size() - k), loc.end());
    //sort(loc.begin(), loc.end());
    loc.resize(loc.size() - k + 1);
    for (auto e : loc) glob.pb(e);

    loc.clear();
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &k, &q);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        v.pb(a[i]);
    }
    
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());

    ans = 1 << 30;
    for (auto base : v) {
        glob.clear();
        
        loc.clear();
        for (i = 1; i <= n; i++) {
            if (a[i] < base) {
                execute();
            } else {
                loc.pb(a[i]);
            }
        }
        execute();

        if (glob.size() < q) break;
        nth_element(glob.begin(), glob.begin() + q - 1, glob.end());
        //sort(glob.begin(), glob.end());

        //cerr << base << ' ' << '\n';
        //for (auto e : glob) cerr << e << ' ';
        //cerr << "\n\n";

        int maxi = glob[q - 1];
        ans = min(ans, maxi - base);
    }

    printf("%d", ans);

    return 0;
}
