#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000000

int n, i, j, k;
bool win[maxN];
int cnt;

int main()
{
    cin >> n >> k;
    cerr << '\n';

    win[0] = false;
    for (i = 1; i <= n; i++) {
        win[i] = false;
        for (j = 2; j <= k; j++)
            if (win[ i / j ] == false)
                win[i] = true;


        //cerr << i << ' ' << win[i] << '\n';
        if (win[i] == win[i-1]) {
            cnt++;
        } else {
            cerr << i - cnt << ' ' << i - 1 << ' ' << win[i-1] << '\n';
            cnt = 1;
        }
    }

    return 0;
}
