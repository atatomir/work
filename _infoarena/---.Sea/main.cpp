#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define x first
#define y second
#define maxS 411

typedef pair<double,double> Ship;

long n,m,i,nr;
Ship S[maxS];
vector<double> R;
double base;

int main()
{
    freopen("sea.in","r",stdin);
    freopen("sea.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++) scanf("%lf %lf",&S[i].x,&S[i].y);
    sort(S+1,S+n+1);
    for(;m;m--){
        scanf("%lf %ld",&base,&nr); R.clear();
        for(i=1;i<=n;i++) {
            if(S[i].x>base) break;
            R.push_back(sqrt((S[i].y)*(S[i].y)+(S[i].x-base)*(S[i].x-base)));
        }
        sort(R.begin(),R.end());
        printf("%.4lf\n",R[nr-1]);
    }

    return 0;
}
