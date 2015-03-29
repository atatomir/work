#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long t;
long n,i,x,s,l1,l2,dim,val,tmp;
vector<long> v[2];

long ans,cont;

int main()
{
    freopen("palind2.in","r",stdin);
    freopen("palind2.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        v[0].clear(); v[1].clear();
        scanf("%ld",&n);
        for(i=1;i<=n;i++){
            scanf("%ld",&x);
            v[i%2].push_back(x);
        }

        ans = 0; cont = 1;
        sort(v[0].begin(),v[0].end());
        sort(v[1].begin(),v[1].end());

        for(s=0;s<=1;s++){
            dim = v[s].size(); if(!dim) continue;
            if(dim % 2 == 0){
                l1 = v[s][dim/2-1]; l2 = v[s][dim/2];
                cont *= l2-l1+1;
                val = l1;

                for(i=0;i<dim;i++){
                    tmp = val - v[s][i];
                    if(tmp < 0) tmp = -tmp;
                    ans += tmp;
                }
            } else {
                val = v[s][dim/2];
                for(i=0;i<dim;i++){
                    tmp = val - v[s][i];
                    if(tmp < 0) tmp = -tmp;
                    ans += tmp;
                }
            }

        }

        printf("%ld %ld\n",ans,cont);
    }
    return 0;
}
