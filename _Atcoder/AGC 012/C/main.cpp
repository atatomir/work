#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

ll n, i, dd, bit;
deque<int> val;


int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld", &n); n++;
    for (bit = 1; (bit << 1) <= n; bit <<= 1);

    //val.push_back(++dd);
    for (bit >>= 1; bit > 0; bit >>= 1) {
        val.push_back(++dd);
        if (n & bit) val.push_front(++dd);
    }

    printf("%lld\n", 2 * dd);
    while (!val.empty()) {
        printf("%d ", val.front());
        val.pop_front();
    }

    for (i = 1; i <= dd; i++) printf("%lld ", i);



    return 0;
}
