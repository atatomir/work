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

const int limit = 30000;

int n, nn, i, even, odd, sumi;
vector<int> sol;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    even = 2;
    odd = 3;

    nn = n;
    sumi += even;
    sol.pb(even); even += 2; n--;

    if (nn % 2 == 1) {
        sumi += even;
        sol.pb(even); even += 2; n--;

        sumi += even;
        sol.pb(even); even += 2; n--;
    }



    while (odd + 6 <= limit && n >= 2) {
        sol.pb(odd);
        sol.pb(odd + 6);
        odd += 12;
        n -= 2;
    }

    while (n > 0) {
        sol.pb(even);
        sumi += even;
        even += 2;
        n--;
    }

    for (i = sol.size() - 1; sol[i] % 2 == 1; i--);

    while (sumi % 3 != 0) {
        sol[i] += 2;
        sumi += 2;
    }

    if (nn == 3) sol = {2, 5, 63};
    if (nn == 4) sol = {2, 5, 20, 63};

    for (auto e : sol) cout << e << ' ';


    return 0;
}
