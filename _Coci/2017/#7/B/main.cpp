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

#define maxN 400011

ll n, k, m, i;
ll path_size, path_kids, full_groups;
ll rem_teams, rem_pupils;

ll sol[maxN];

int main()
{
   // freopen("test.in","r",stdin);

    cin >> n >> k >> m;

    path_size = 2 * n - 2;
    path_kids = path_size * k;
    full_groups = m / path_kids;

    rem_teams = (m % path_kids) / k;
    rem_pupils = (m % path_kids) % k;

    for (i = 1; i <= path_size; i++) sol[i] = full_groups * k;
    for (i = 1; i <= rem_teams; i++) sol[i] += k;
    sol[rem_teams + 1] += rem_pupils;

    cout << sol[1] << ' ';
    for (i = 2; i < n; i++) {
        sol[i] += sol[path_size - i + 2];
        cout << sol[i] << ' ';
    }
    cout << sol[n];

    return 0;
}
