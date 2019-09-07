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

int n;

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    cout << (n * (n - 1)) / 2 - (n / 2)<< '\n';
    int target = (n % 2) ? n : n + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (i + j == target) continue;
            cout << i << ' ' << j << '\n';
        }
    }


    return 0;
}
