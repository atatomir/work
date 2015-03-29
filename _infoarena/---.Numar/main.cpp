#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<long,long> > ans;
long n,i,sum,tmp,p,q;

int main()
{
    freopen("numar.in","r",stdin);
    freopen("numar.out","w",stdout);

    scanf("%ld",&n);
    sum = 0;
    for(i=1;i+sum <=n;i++){
        sum += i;
        tmp = n - sum;
        if(tmp % i == 0){
            p = 1 + tmp/i; q = i;
            ans.push_back(make_pair(p,q));
            q += 2* (p-1) + 1; p = -(p-1);
            ans.push_back(make_pair(p,q));
        }
    }

    sort(ans.begin(),ans.end());
    for(i=ans.size()-1;i>=0;i--){
        if(ans[i].second == 1) continue;

        printf("%ld %ld\n",ans[i].first,ans[i].second);
    }

    return 0;
}
