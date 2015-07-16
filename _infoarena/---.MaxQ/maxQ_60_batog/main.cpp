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
#define inf (1LL<<60)

class Batog{
    public:
        long long *R,*smen;
        long long *maxi,*mini;
        long long *add;
        long long *local;
        int n,dim,cnt;

        int getLow(int id) { return (id-1)*dim+1; }
        int getHigh(int id) { return min(n, id*dim ); }
        int getBlock(int pos) { return (pos+dim-1)/dim; }
        void reload(int id){
            if(id<=0) return;
            int i;
            maxi[id] = -inf;
            mini[id] = inf;
            int low = getLow(id);
            int high = getHigh(id);
            long long locMin = R[low-1] + add[getBlock(low-1)];
            local[id] = -inf;
            fordef(i,low,high) {
                R[i] += add[id];
                mini[id] = min(mini[id],R[i]);
                maxi[id] = max(maxi[id],R[i]);

                local[id] = max(local[id], R[i]-locMin );
                locMin = min(locMin,R[i]);
            }
            add[id]=0;
        }

        //! -------------------------------------

        void init(int _n,long long *_R,long long *_smen,long long *_mini,long long *_maxi,long long *_add,long long* _local){
            n = _n; R = _R; smen = _smen; local = _local;
            mini = _mini; maxi = _maxi; add = _add;
            dim = (int)sqrt(n);
            cnt = (n+dim-1)/dim;
            int i;
            fordef(i,1,cnt) smen[i]=0;
            fordef(i,1,n) R[i] += R[i-1];
            fordef(i,1,cnt) reload(i);
        }
        int update(int pos,long long val){
            int block = getBlock(pos),i;
            fordef(i,block+1,cnt) {
                add[i] += val;
                mini[i] += val;
                maxi[i] += val;
            }

            int high = getHigh(block);
            fordef(i,pos,high) R[i] += val;
            reload(block);
        }

};

#define maxN 200011
int n,m,i,op,x,y;
long long R[maxN],_smen[maxN],mini[maxN],maxi[maxN],add[maxN],local[maxN];
long long rez[maxN];

int main()
{
    freopen("maxq.in","r",stdin);
    freopen("maxq.out","w",stdout);

    scanf("%d",&n);
    fordef(i,1,n) {scanf("%lld",&R[i]); rez[i]=R[i];}
    Batog smen ;
    smen.init(n,R,_smen,mini,maxi,add,local);

    scanf("%d",&m);
    for(;m--;){
        scanf("%d%d%d",&op,&x,&y);
        if(op==0){
            x++;
            smen.update(x, y-rez[x] );
            rez[x] = y;
        } else {
            x++; y++;
            long long ans = 0;
            long long last = R[x-1] + smen.add[smen.getBlock(x-1)];
            int fBlock = smen.getBlock(x);
            int lBlock = smen.getBlock(y);

            //smen.reload(fBlock);
            //smen.reload(lBlock);
            long long addi;

            if(lBlock-fBlock <= 1){
                smen.reload(fBlock);
                smen.reload(lBlock);
                fordef(i,x,y){
                    ans = max(ans,R[i]-last);
                    last = min(last,R[i]);
                }
                printf("%lld\n",ans);
                continue;
            }

            int high = smen.getHigh(fBlock); addi = smen.add[fBlock];
            fordef(i,x,high){
                ans = max(ans,R[i]+addi-last);
                last = min(last,R[i]+addi);
            }
            fordef(i,fBlock+1,lBlock-1){
                ans = max(ans,smen.local[i]);
                ans = max(ans,smen.maxi[i]-last);
                last = min(last,smen.mini[i]);
            }
            int low = smen.getLow(lBlock); addi = smen.add[lBlock];
            fordef(i,low,y){
                ans = max(ans,R[i]+addi-last);
                last = min(last,R[i]+addi);
            }

            printf("%lld\n",ans);
        }
    }

    return 0;
}
