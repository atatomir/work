#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define x first.first
#define y first.second
#define z second

long n,i,co;
vector<pair<pair<long,long>,long> > ans;

inline void add(long a ,long b,long c){
    ans.push_back(make_pair(make_pair(a,b),c));
}

int main()
{
    freopen("color5.in","r",stdin);
    freopen("color5.out","w",stdout);

    scanf("%ld",&n);
    if(n==3){
        for(i=0;i<n;i++) add(n,i,1);
        for(i=0;i<n;i++) add(i,(i+1)%n,1);
        co=1;
    } else {
        if(n>6)
            {for(i=0;i<n;i++) add(i,(i+1)%n,3);co=3;}
        else
            {for(i=0;i<n;i++) add(i,(i+1)%n,(i%2)+1);co=2;}
        for(i=0;i<n;i++) add(n,i,(i%2)+1);
    }

    printf("%ld\n",co);
    for(i=0;i<ans.size();i++) printf("%ld %ld %ld\n",ans[i].x,ans[i].y,ans[i].z);

    return 0;
}
