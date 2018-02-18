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

#define maxN 10011

ll n, i, a[maxN], b[maxN];
ll na, nb;

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) cin >> a[i];
    for (i = 1; i <= n; i++) cin >> b[i];

    for (i = 1; i <= n; i++) {
        if ((a[i] & 1) ^ (b[i] & 1)) {
            b[i]++;
            nb++;
        }

        if (a[i] > b[i]) {
            nb += a[i] - b[i];
            b[i] = a[i];
        } else {
            na += (b[i] - a[i]) / 2;
            a[i] = b[i];
        }
    }

    if (na >= nb)
        cout << "Yes";
    else
        cout << "No";


    return 0;
}
