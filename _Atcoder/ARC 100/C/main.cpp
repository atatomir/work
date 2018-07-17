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

int n, i, x;
vector<int> aux;
ll ans;

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> x;
        aux.pb(x - i);
    }

    sort(aux.begin(), aux.end());
    x = aux[aux.size() / 2];

    for (auto e : aux)
        ans += abs(1LL * x - e);

    cout << ans;


    return 0;
}
