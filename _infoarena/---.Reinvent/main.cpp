#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 100011

int n,m,x,j,i,cnt,y;
vector<int> list[maxN];
int Town[maxN];
queue<int> Q;
int us[maxN],ans;
bool dest[maxN];
vector< pa(int,int) > Groups,tmp;

int main()
{
    freopen("reinvent.in","r",stdin);
    freopen("reinvent.out","w",stdout);

    scanf("%d%d%d",&n,&m,&cnt);
    fordef(i,1,m){
        scanf("%d%d",&x,&y);
        list[x].pb(y);
        list[y].pb(x);
    }
    fordef(i,1,cnt) scanf("%d",&Town[i]);

    ans = n+17;
    Groups.pb(mp(1,cnt));

    do{
        tmp = Groups; Groups.clear();
        foreach(tmp){
            pa(int,int) act = *it;
            if(act.first==act.second)
                Groups.pb(act);
            else{
                int mid = (act.first+act.second)>>1;
                Groups.pb( mp( act.first , mid ) );
                Groups.pb( mp( mid+1 , act.second ) );
            }
        }

        int pas = 0;
        fordef(i,1,n) dest[i]=false;
        while(!Q.empty()) Q.pop();
        fordef(i,1,n) us[i]=0;

        foreach(Groups){
            pas ^= 1;
            if(pas==1){
                fordef(j,it->first,it->second) {
                    us[Town[j]] = 1;
                    Q.push(Town[j]);
                }
            } else {
                fordef(j,it->first,it->second)
                    dest[Town[j]]=true;
            }
        }

        //! some stuff
        while(!Q.empty()){
            int node = Q.front(); Q.pop();
            foreach(list[node]){
                if(us[*it]) continue;
                if(dest[*it]) {
                    ans = min(ans,us[node]);
                    break;
                }

                us[*it] = us[node]+1;
                Q.push(*it);
            }
        }

    } while (Groups.size() != cnt);

    printf("%d",ans);

    return 0;
}
