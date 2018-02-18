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

#define maxN 100011

int n, i, j, t1, t2;
vector<int> data;

int ask(int pos) {
    string s;

    cout << pos << endl;
    cin >> s;

    if (s == "Vacant") exit(0);
    if (s == "Male") return 1;
    return 0;
}

void solve(int l, int r, int t1, int t2) {
    if (l + 1 == r)
        ask((data[l] + 1) % n);

    int mid = (l + r) >> 1;
    int tt = ask(data[mid]);

    if (tt == t1)
        solve(mid, r, tt, t2);
    else
        solve(l, mid, t1, tt);
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (i = 0; i != 1; i = (i + 2) % n) data.pb(i);
    data.pb(1);

    t1 = ask(0);
    t2 = ask(1);

    solve(0, data.size() - 1, t1, t2);



    return 0;
}
