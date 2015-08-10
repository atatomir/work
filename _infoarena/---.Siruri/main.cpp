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

#define maxN 200011
#define maxLog 19

int prefix[maxLog][maxN];
class SuffixArray{
    private:
        int dim,logg;
        int *S;

        struct Triple{
            int x,y,id;
            Triple(int _x,int _y,int _id){
                x = _x; y = _y;
                id = _id;
            }

            bool operator<(const Triple& who)const{
                if(x==who.x) return (y<who.y);
                return (x<who.x);
            }
            bool operator==(const Triple& who){
                return (x==who.x)&&(y==who.y);
            }
        };

    public:
        void init(int _dim,int *_S){
            int i;
            vector<Triple> wh;
            dim = _dim ; S = _S;
            logg=0; while( (1<<logg)<dim ) logg++;

            for(i=1;i<=dim;i++) prefix[0][i] = S[i];
            for(int actLog=1;actLog<=logg;actLog++){
                wh.clear();
                int def = 1<<(actLog-1);
                for(i=1;i<=dim;i++){
                    if(i+def<=dim) wh.pb( Triple( prefix[actLog-1][i] , prefix[actLog-1][i+def] , i) );
                    else           wh.pb( Triple( prefix[actLog-1][i] , -100001 ,i) );
                }

                sort(wh.begin(),wh.end());
                prefix[actLog][ wh[0].id ] = 1;
                for(i=1;i<wh.size();i++){
                    if(wh[i]==wh[i-1]) prefix[actLog][ wh[i].id ] = prefix[actLog][ wh[i-1].id ] ;
                    else               prefix[actLog][ wh[i].id ] = prefix[actLog][ wh[i-1].id ]+1 ;
                }
            }
        }
        int lcp(int A,int B){
            int ans = 0;
            for(int actLog = logg;actLog>=0;actLog--){
                int def = 1<<actLog;
                if(prefix[actLog][A] == prefix[actLog][B]) {
                    A+=def; B+=def;
                    ans+=def;
                }
            }
            return ans;
        }
        void getOrder(int *dest){
            for(int i=1;i<=dim;i++) dest[ prefix[logg][i] ] = i;
        }
};

int n,m,i,p1,p2,lim,ans,ansX,ansY;
int a[maxN],b[maxN],v[maxN];
SuffixArray SA;
int order[maxN];

int main()
{
    freopen("siruri.in","r",stdin);
    freopen("siruri.out","w",stdout);

    scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);
    for(i=1;i<=m;i++) scanf("%d",&b[i]);

    for(i=1;i<n;i++) v[i] = a[i+1]-a[i];
    v[n--] = -100001;
    for(i=1;i<m;i++) v[n+1+i] =  b[i]-b[i+1];
    m--;

    SA.init(n+m+1,v);
    SA.getOrder(order);
    lim = n+1; ans = 0;
    ansX = 1; ansY = 1;

    p2 = 2; //! pe poz 1 e elem delimitator
    for(p1=2;p1<=n+m+1;p1++){
        bool prov1 = (order[p1]<lim);
        bool prov2 = (order[p2]<lim);

        while(prov1==prov2 && p2<=n+m+1) {
            p2++;
            prov2 = (order[p2]<lim);
        }
        if(p2>n+m+1) break;

        int aux = SA.lcp( order[p1],order[p2] );
        if(aux > ans){
            ans = aux;
            if(prov1) {
                ansX = order[p1];
                ansY = order[p2]-n-1;
            } else {
                ansX = order[p2];
                ansY = order[p1]-n-1;
            }
        }
    }

    printf("%d %d %d",ans+1,ansX,ansY);


    return 0;
}
