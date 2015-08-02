#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 10011

struct Intv{
    long val,beg;
};
Intv mp(long begg,long vall){
    Intv ans;
    ans.beg=begg;ans.val=vall;
    return ans;
}
bool cmp(const Intv& a,const Intv& b){return a.beg<b.beg;}

long t,n,m,i,x,y,vv,j;
vector<Intv> act[maxN];
vector<Intv> tmp;

long ans[maxN],sum[maxN];

bool Check(){
    for(i=n;i;i--){
        sort(act[i].begin(),act[i].end(),cmp); tmp.clear();
        for(j=0;j<act[i].size();j++){
            long def = act[i][j].beg,dVal=act[i][j].val;
            tmp.push_back(act[i][j]);
            while(j<act[i].size()-1 && act[i][j+1].beg==def) {
                j++;
                if(act[i][j].val!=dVal) return false;
            }
        }
        act[i].clear();
        if(tmp.size()) act[i].push_back(tmp[tmp.size()-1]);

        for(j=tmp.size()-2;j>=0;j--){
            Intv now = tmp[j];
            act[act[i][0].beg-1].push_back(mp(now.beg,now.val^act[i][0].val));
        }
    }

    for(i=1;i<=n;i++){
        if(act[i].size()==0) {
            sum[i] = sum[i-1];
            continue;
        }
        ans[i] = act[i][0].val ^ (sum[i-1]^sum[act[i][0].beg-1]);
    }
    return true;
}

int main()
{
    freopen("bazaconii.in","r",stdin);
    freopen("bazaconii.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%ld %ld",&n,&m);
        for(i=1;i<=n;i++) act[i].clear();

        for(i=1;i<=m;i++){
            scanf("%ld%ld%ld",&x,&y,&vv);
            act[y].push_back(mp(x,vv));
        }

        if(!Check())
            printf("-1\n");
        else{
            for(i=1;i<=n;i++) printf("%ld ",ans[i]);
            printf("\n");
        }
    }


    return 0;
}
