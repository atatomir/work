#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 200011

int n,i,ansCount;
vector<int> ans[maxN];
bitset<maxN> us;

int main()
{
    freopen("dubi.in","r",stdin);
    freopen("dubi.out","w",stdout);

    us.reset();

    scanf("%d",&n);
    for (i = 1; i <= n; i++) {
        if (us[i]) continue;

        int step = 1;
        while (step <= i) step <<= 1;

        ansCount++;
        for (int j = i; j <= n; j += step, step <<= 1) {
            us[j] = true;
            ans[ansCount].pb( j );
        }
    }

    printf("%d\n",ansCount);
    for (i = 1; i <= ansCount; i++){
        printf("%d ",ans[i].size());
        for (auto e: ans[i]) printf("%d ",e);
        printf("\n");
    }

    return 0;
}
