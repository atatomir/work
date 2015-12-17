#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

pair<int, int> p1, p2;
int ans;

int main()
{
    freopen("paint.in","r",stdin);
    freopen("paint.out", "w", stdout);

    scanf("%d%d", &p1.first, &p1.second);
    scanf("%d%d", &p2.first, &p2.second);

    if (p1.first > p2.first)
        swap(p1, p2);

    if (p1.second >= p2.first)
        ans = max(p1.second, p2.second) - p1.first;
    else
        ans = p1.second - p1.first + p2.second - p2.first;

    printf("%d", ans);


    return 0;
}
