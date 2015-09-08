#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define inf 1e60

int n,m,i,pos;
pair<int, int> Point[maxN];

int stack_dim;
pair<double, int> Stack[maxN];

void addStack(int act) {
    double xx;
    while (stack_dim > 0) {
        int who = Stack[stack_dim].second;

        xx = (1.00 * Point[who].first * Point[who].first +
              1.00 * Point[who].second * Point[who].second -
              1.00 * Point[act].first * Point[act].first -
              1.00 * Point[act].second * Point[act].second ) /
             (2.00 * (Point[who].first - Point[act].first));

        if (xx > Stack[stack_dim-1].first) break;
        if (stack_dim == 1) break;

        stack_dim--;
    }

    if (stack_dim == 0) {
        Stack[++stack_dim] = mp(inf, act);
        return;
    }

    Stack[stack_dim].first = xx ;
    Stack[++stack_dim] = mp(inf, act);
}

int BinarySearch(int pos) {
    int ans = 0;
    int step = 1;

    while (2 * step <= stack_dim) step <<= 1;

    for (; step > 0; step >>= 1) {
        int aux = ans + step;
        if (aux > stack_dim) continue;

        if (Stack[aux].first <= pos) ans = aux;
    }

    return Stack[ans + 1].second;
}

long long dist(int xx1, int yy1, int xx2, int yy2) {
    return 1LL * (xx1 - xx2) * (xx1 - xx2) +
           1LL * (yy1 - yy2) * (yy1 - yy2) ;
}

int main()
{
    freopen("puncte.in","r",stdin);
    freopen("puncte.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%d%d", &Point[i].first, &Point[i].second);
    for (i = 1; i <= n; i++)
        if (Point[i].first != Point[i - 1].first)
            addStack(i);

    for (; m > 0; m--) {
        scanf("%d",&pos);
        int wh = BinarySearch(pos);

        printf("%lld\n", dist(Point[wh].first, Point[wh].second, pos, 0));
    }

    return 0;
}
