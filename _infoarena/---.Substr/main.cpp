#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class SuffixArrays{
    private:
        struct Triple{
            long x,y,id;
            Triple(){};
            Triple(long _x,long _y,long _id){
                x = _x; y = _y; id = _id;
            }
            bool operator<(const Triple& who) const{
                if(who.x==x) return y < who.y;
                return x < who.x;
            }
        };

    public:
        vector<vector<long> > pr;
        vector<Triple> T;

        SuffixArrays(long n,char s[]){
            long log = 0,i,j;
            while(1<<(log+1)  <= n) log++;
            pr = vector<vector<long> >(log+1,vector<long>(n+2));

            for(i=1;i<=n;i++) pr[0][i] = s[i];

            T = vector<Triple>(n);
            for(i=1;i<=log;i++){
                for(j=1;j<=n;j++){
                    if(j+(1<<i) >n+1)
                        T[j-1] = Triple(pr[i-1][j],-1,j);
                    else
                        T[j-1] = Triple(pr[i-1][j],pr[i-1][j+(1<<(i-1))],j);
                }

                sort(T.begin(),T.end());
                for(j=0;j<n;j++) {
                    if(j==0 || T[j-1]<T[j]) pr[i][T[j].id] = j;
                    else                    pr[i][T[j].id] = pr[i][T[j-1].id];
                }
            }
        }

        long lcp(long x,long y){
            long ans=0;
            if(x==y) return pr[0].size()-2-x+1;
            for(long i=pr.size()-1;i>=0;i--){
                if(pr[i][x]==pr[i][y]){
                    ans += 1<<i;
                    x   += 1<<i;
                    y   += 1<<i;
                }
            }
            return ans;
        }
};

#define maxN 17000

long n,k,i,ans=1;
char s[maxN];

int main()
{
    freopen("substr.in","r",stdin);
    freopen("substr.out","w",stdout);

    scanf("%ld %ld\n%s",&n,&k,s+1);
    SuffixArrays SA(n,s);

    for(i=0;i+k-1<n;i++) ans = max(ans,SA.lcp(SA.T[i].id,SA.T[i+k-1].id));
    printf("%ld",ans);

    return 0;
}
