#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 50311
#define maxLog 17

int pr[maxLog][maxN];
class SuffixArray{
    private:
        char *S;
        int n,logg;
        //! pr[maxLog][maxN]

        struct Triple{
            int x,y,id;

            Triple(int _x,int _y,int _id){
                x = _x; y = _y; id = _id;
            }
            bool operator<(const Triple& who)const{
                if(x==who.x) return y < who.y;
                return x < who.x;
            }
            bool operator==(Triple& who){
                return (x==who.x)&&(y==who.y);
            }
        };

    public:
        void init(char *_S,int _n){
            S = _S; n = _n;
            for(logg=0; (1<<logg)<n ; logg++ );

            int i;
            vector<Triple> aux;

            fordef(i,1,n) pr[0][i] = S[i];
            for(int actLog=1;actLog<=logg;actLog++){
                int def = 1<<(actLog-1);
                aux.clear();

                fordef(i,1,n){
                    if(i+def<=n) aux.pb( Triple(pr[actLog-1][i],pr[actLog-1][i+def],i) );
                    else         aux.pb( Triple(pr[actLog-1][i],-1,i) );
                }

                sort(aux.begin(),aux.end());
                pr[actLog][ aux[0].id ] = 1;
                for(i=1;i<aux.size();i++){
                    if(aux[i-1]==aux[i]) pr[actLog][ aux[i].id ] = pr[actLog][ aux[i-1].id ];
                    else                 pr[actLog][ aux[i].id ] = pr[actLog][ aux[i-1].id ]+1;
                }
            }
        }
        int getOrder(int *dest){
            for(int i=1;i<=n;i++) dest[ pr[logg][i] ] = i;
        }
        int lcp(int posA,int posB){
            int ans =0;
            for(int actLog = logg;actLog>=0;actLog--){
                int def = (1<<actLog);
                if(pr[actLog][posA]==pr[actLog][posB]){
                    ans += def;
                    posA += def; posB+=def;
                }
            }
            return ans;
        }
};

int n,i;
char s[maxN];
SuffixArray SA;
int ord[maxN];
long long ans;

int main()
{
    freopen("ghicit.in","r",stdin);
    freopen("ghicit.out","w",stdout);

    gets(s+1);
    n = strlen(s+1);
    SA.init(s,n);

    SA.getOrder(ord);
    ans = (1LL*(n+1)*n)/2LL;
    fordef(i,2,n) ans -= SA.lcp( ord[i-1],ord[i] );
    printf("%lld",ans);

    return 0;
}
