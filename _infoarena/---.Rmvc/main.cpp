#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 99
#define maxM 333

int n,m,i;
pair<int,int> E[maxM];
bool added[maxN];
int alrdn;

int ans;
vector<int> sel;

void Try(int step) {
    if (alrdn >= ans) return;
    if (step == m+1 ) {

        ans = alrdn;
        sel.clear();
        for (int i = 1; i <= n; i++)
            if (added[i]) sel.pb(i);

        return;
    }

    int x = E[step].first;
    int y = E[step].second;

    if (added[x] || added[y]) {
        Try(step+1);
    } else {
        alrdn++;
        added[x] = true;
        Try(step+1);
        added[x] = false;
        alrdn--;

        alrdn++;
        added[y] = true;
        Try(step+1);
        added[y] = false;
        alrdn--;
    }
}

int main()
{
    freopen("rmvc.in","r",stdin);
    freopen("rmvc.out","w",stdout);

    scanf("%d%d",&n,&m);
    for (i = 1; i <= m; i++) scanf("%d%d",&E[i].first,&E[i].second);
    random_shuffle(E+1,E+m+1);

    ans = 19;
    Try(1);
    printf("%d\n",ans);
    for (auto e:sel) printf("%d ",e);

    return 0;
}
