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

const int maxN = 200011;

int n, i, mid;
pair<int, int> data[maxN];
int b[maxN];

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &data[i].first);
        data[i].second = i;
    }

    sort(data + 1, data + n + 1);
    mid = n / 2;

    for (i = 1; i <= mid; i++) b[data[i].second] = data[mid + 1].first;
    for (i = mid + 1; i <= n; i++) b[data[i].second] = data[mid].first;

    for (i = 1; i <= n; i++) printf("%d\n", b[i]);


    return 0;
}
