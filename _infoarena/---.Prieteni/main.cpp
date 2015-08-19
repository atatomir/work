#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

int n,i,cost;
int v[maxN];
int dp[maxN];
bool couple[maxN];

void Move(int from_1,int from_2,int to){
    printf("%d %d\n",v[from_1],v[from_2]);
    if (to != -1) printf("%d\n",v[to]);

    cost += v[from_2];
    if (to != -1) cost += v[to];
}

void Type_one(int pos){
    Move(1,pos,1);
}
void Type_two(int pos_1,int pos_2){
    Move(1,2,1);
    Move(pos_1,pos_2,2);
}

int main()
{
    freopen("prieteni.in","r",stdin);
    freopen("prieteni.out","w",stdout);

    scanf("%d",&n);
    for (i = 1; i <= n; i++) scanf("%d",&v[i]);
    sort(v+1,v+n+1);

    if (n == 1) {
        printf("%d",v[1]);
        return 0;
    }
    if (n == 2) {
        printf("%d",v[2]);
        return 0;
    }

    dp[3] = v[1]+v[3]; couple[3] = false;
    for (i = 4; i <= n; i++) {
        int byOne = dp[i-1] + v[i] + v[1];
        int byTwo = dp[i-2] + v[2] + v[1] + v[i] + v[2];

        if (byOne < byTwo) {
            dp[i] = byOne;
            couple[i] = false;
        } else {
            dp[i] = byTwo;
            couple[i] = true;
        }
    }

    for (i = n; i != 2; ){
        if (couple[i]) {
            Type_two(i-1,i);
            i -= 2;
        } else {
            Type_one(i);
            i--;
        }
    }
    Move(1,2,-1);
    printf("%d",cost);

    return 0;
}
