#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 15011

int t,n,i;
int box[maxN];
int human[maxN];

int box_[maxN];
int human_[maxN];
int count_;

void moveAll(int act_human,int act_box) {
    int val = min(box_[act_box], human_[act_human]);
    box_[act_box] -= val;
    human_[act_human] -= val;

    count_ += val;
}

int Test(int howMany) {
    memcpy(box_, box, sizeof(box));
    memcpy(human_, human, sizeof(human));
    count_ = howMany;

    human_[1] -= howMany;
    box_[1] -= howMany;
    moveAll(1, n);

    for (int i = 2; i <= n; i++) {
        moveAll(i, i - 1);
        moveAll(i, i);
    }

    return count_;
}

int main()
{
    freopen("bile5.in","r",stdin);
    freopen("bile5.out","w",stdout);

    for (scanf("%d",&t); t > 0; t--) {
        scanf("%d",&n);
        for (i = 1; i <= n; i++) scanf("%d%d",&box[i],&human[i]);
        int limit = min(box[1], human[1]);

        int y_begin = Test(0);
        int y_end = Test(limit);

        int xx = (y_end - y_begin + limit) / 2;
        int yy = Test(xx);

        int cons_begin = 0 + (yy - y_begin);
        int cons_end = limit - (yy - y_end);

        for (i = 0; i < cons_begin; i++) {
            printf("%d\n",y_begin);
            y_begin++;
        }
        for (i = cons_begin; i <= cons_end; i++)
            printf("%d\n",y_begin);
        for (i = cons_end + 1; i <= limit; i++) {
            y_begin--;
            printf("%d\n",y_begin);
        }
    }


    return 0;
}
