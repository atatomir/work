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

const int maxN = 111;

int t, ti;
ll n, k, v, i;
string data[maxN];
vector<int> ans;


int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out", "w", stdout);

    cin >> t;
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        cin >> n >> k >> v;
        for (i = 0; i < n; i++) cin >> data[i];
        v = ((v - 1) * k) % n;

        ans.clear();
        for (i = 0; i < k; i++)
            ans.pb((v + i) % n);

        sort(ans.begin(), ans.end());

        cout << "Case #" << ti << ": ";
        for (auto e : ans) cout << data[e] << ' ';
        cout << '\n';
    }


    return 0;
}
