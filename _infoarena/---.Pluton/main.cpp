#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long n,i,j,x,d,act;
vector<pair<long,pair<long,long> > > V;
vector<long> tmp;

long best,cnt,start,plut;

int main()
{
    freopen("pluton.in","r",stdin);
    freopen("pluton.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&x);
        d = x; tmp.clear();
        while(d){
            tmp.push_back(d%10);
            d/=10;
        }

        sort(tmp.begin(),tmp.end());
        for(j=tmp.size()-1;j>=0;j--){
            d = d*10 + tmp[j];
        }

        V.push_back(make_pair(d,make_pair(x,i)));
    }
    sort(V.begin(),V.end());

    for(i=0;i<V.size();i+=act){
        act = 1; plut++;
        while(V[i+act].first == V[i].first&&i+act<V.size()) act++;
        if(act > best){
            best = act;
            cnt = 1; start = i;
        }else
        if(act == best) cnt++;
    }

    printf("%ld\n%ld\n%ld\n",plut,best,cnt);
    for(i=0;i<best;i++) printf("%ld ",V[i+start].second.first);


    return 0;
}
