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
#define lSon (node<<1)
#define rSon (lSon|1)

#define maxN 200011

class Aint{
    private:
        ll *left,*right,*center,*all,*prov,*sums;
        int n;
        ll pos,val,ans,qL,qR;
        vector<int> vv;

        void reload(int node){
            int ls = lSon;
            int rs = rSon;

            left[node] = max( left[ls],all[ls]+left[rs] );
            right[node] = max( right[rs],all[rs]+right[ls]);
            center[node] = max( right[ls]+left[rs] , max( center[ls] , center[rs] ) );
            all[node] = all[ls]+all[rs];
        }
        void makeTree(int node,int l,int r){
            if(l==r){
                left[node] = right[node] = center[node] = all[node] = prov[l];
                return;
            }

            int mid = (l+r)>>1;
            makeTree(lSon,l,mid);
            makeTree(rSon,mid+1,r);

            reload(node);
        }
        void _update(int node,int l,int r){
            if(l==r){
                left[node] = right[node] = center[node] = all[node] = val;
                return;
            }

            int mid = (l+r)>>1;
            if(pos<=mid) _update(lSon,l,mid);
            else         _update(rSon,mid+1,r);

            reload(node);
        }
        void _query(int node,int l,int r){
            if(qL<=l&&r<=qR){
                vv.push_back(node);
                ans = max(ans,center[node]);
                return;
            }

            int mid = (l+r)>>1;
            if(qL<=mid) _query(lSon,l,mid);
            if(qR> mid) _query(rSon,mid+1,r);
        }

    public:
        void init(int _n,ll *_left,ll *_right,ll *_center,ll *_all,ll *_prov,ll *_sums){
            n = _n;
            left = _left; right=_right;center=_center; all = _all;
            sums = _sums;

            prov = _prov;
            makeTree(1,1,n);
        }
        void update(int _pos,int _val){
            pos = _pos; val = _val;
            _update(1,1,n);
        }
        ll query(int l,int r){
            ans = 0; //! dubios dar adevarat
            vv.clear();
            qL = l ; qR = r;
            _query(1,1,n);

            int i,j;
            fordef(i,0,vv.size()-1) sums[i] = all[vv[i]];
            fordef(i,1,vv.size()-1) sums[i] += sums[i-1];
            for(i=0;i<vv.size();i++)
                for(j=i+1;j<vv.size();j++)
                    ans = max(ans, right[vv[i]]+left[vv[j]]+sums[j-1]-sums[i] );
            return ans;
        }
};

int n,i,m,op,x,y;
ll v[maxN];

//!-----------------
ll vleft[maxN<<2],vright[maxN<<2],vcenter[maxN<<2];
ll vall[maxN<<2],vsums[maxN<<2];
//!-----------------


int main()
{
    freopen("maxq.in","r",stdin);
    freopen("maxq.out","w",stdout);

    scanf("%d",&n);
    fordef(i,1,n) scanf("%lld",&v[i]);

    Aint aint;
    aint.init(n,vleft,vright,vcenter,vall,v,vsums);

    scanf("%d",&m);
    for(;m--;){
        scanf("%d %d %d",&op,&x,&y);
        if(op==0){
            x++;
            aint.update(x,y);
        } else {
            x++; y++;
            printf("%lld\n", aint.query(x,y) );
        }
    }

    return 0;
}
