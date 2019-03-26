#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

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
map<int, int> M;

int check(int x) {
    if (M[x] > 0) return M[x];

    M[x] = min(1 + check(x/2) + (x % 2), 1 + check(x/3) + (x % 3));
    return M[x];
}

int main()
{
    //freopen("test.in","r",stdin);

    int i;
    cin >> n;
    M[1] = 1;
    M[2] = 2;
    M[3] = 2;
    
    int v = 0;
    for (i = 1; i <= n; i++) 
        cerr << i << ' ' << check(i) -1 << '\n',
        v = max(v, check(i) - 1);

    cerr << v << '!';
 
    cout << check(n) - 1;


    return 0;
}

