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

const int maxN = 211;

ll n, k, i, cnt;
ll ans;

void brute() {
    int i, cnt, j, k, n;
    int sg[maxN];
    vector<int> aux;

    k = 5;
    n = 80;

    for (i = 0; i < k; i++) sg[i] = 0;
    for (i = k; i <= n; i++) {
        cnt = i / k;
        aux.clear();
        for (j = 1; j <= cnt; j++) aux.pb(sg[i - j]);
        sort(aux.begin(), aux.end());
        aux.resize(unique(aux.begin(), aux.end()) - aux.begin());
        aux.pb(-1);

        sg[i] = 0;
        while (aux[sg[i]] == sg[i]) sg[i]++;
    }

    for (i = 0; i <= n; i++) cerr << sg[i] << ' ';
}

ll slow(ll n, ll k) {
    if (n < k) return 0;
    if (n % k == 0) return n / k;
    return slow(n - (n / k) - 1, k);
}

ll solve(ll n, ll k) {
    ll dif, low, tms;

    while (true) {
        if (n < k) return 0;
        if (n % k == 0) return n / k;

        dif = (n / k) + 1;
        low = (n / k) * k + 1;

        tms = ((n - low) / dif) + 1;
        n -= tms * dif;
    }

}

int main()
{
    //freopen("test.in","r",stdin);

    //brute();

    /*int i, j;
    for (i = 1; i <= 100; i++)
        for (j = 1; j <= 100; j++)
            if (slow(i, j) != solve(i, j))
                cerr << i << ' ' << j << '\n';*/

    cin >> cnt;
    for (i = 1; i <= cnt; i++) {
        cin >> n >> k;
        ans ^= solve(n, k);
    }

    if (ans != 0)
        cout << "Takahashi";
    else
        cout << "Aoki";


    return 0;
}
