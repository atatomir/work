#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 2000011
#define lSon (node<<1)
#define rSon ((node<<1)|1)

long HH;

        long cMin[maxN<<3];
        long cMax[maxN<<3];
        bool flag[maxN<<3];

        void setIt(long node,long _cMin,long _cMax){
            cMin[node] = _cMin;
            cMax[node] = _cMax;
        }
        void goNext(long node,long lA,long rA,long lB,long rB){
            //! A e prioritar

            /*if(rB<=lB) setIt(node,lA,rA);
            if(lA<=lB&&rA>=lB) setIt(node,lA,rB);
            if(lB<=lA&&rA<=rB) setIt(node,lA,rA);
            if(lA<=lB&&rB<=rA) setIt(node,lB,rB);
            if(rA<=rB&&lB>=lA&&lB<=rA) setIt(node,lB,rA);
            if(lB>=rA) setIt(node,rA,rA);*/

            cMin[node] = max(lA,lB);
            cMin[node] = min(cMin[node],rA);
            cMax[node] = min(rA,rB);
            cMax[node] = max(cMax[node],lA);
        }

        void init(){
            memset(cMin,0,sizeof(cMin));
            memset(cMax,0,sizeof(cMax));
            memset(flag,0,sizeof(flag));
        }
        void reUpdate(long node){
            cMin[node] = min(cMin[lSon],cMin[rSon]);
            cMax[node] = max(cMax[lSon],cMax[rSon]);
        }
        void UpdateMin(long node,long l,long r,long qL,long qR){ //! for add
            if(qL<=l && r<=qR){ //! do lazy
                cMin[node] = max(cMin[node],HH);
                if(cMin[node]>cMax[node]) cMax[node]=cMin[node];

                return;
            }
            goNext(lSon,cMin[node],cMax[node],cMin[lSon],cMax[lSon]);
            goNext(rSon,cMin[node],cMax[node],cMin[rSon],cMax[rSon]);

            long mid = (l+r)>>1;
            if(qL<=mid) UpdateMin(lSon,l,mid,qL,qR);
            if(qR> mid) UpdateMin(rSon,mid+1,r,qL,qR);

            reUpdate(node);
        }
        void UpdateMax(long node,long l,long r,long qL,long qR){ //! for remove
            if(qL<=l && r<=qR){ //! do lazy
                cMax[node] = min(cMax[node],HH);
                if(cMin[node]>cMax[node]) cMin[node]=cMax[node];

                return;
            }
            goNext(lSon,cMin[node],cMax[node],cMin[lSon],cMax[lSon]);
            goNext(rSon,cMin[node],cMax[node],cMin[rSon],cMax[rSon]);

            long mid = (l+r)>>1;
            if(qL<=mid) UpdateMax(lSon,l,mid,qL,qR);
            if(qR> mid) UpdateMax(rSon,mid+1,r,qL,qR);

            reUpdate(node);
        }
        void getResult(long node,long l,long r){
            if(l==r) {printf("%ld\n",cMin[node]);return;}

            goNext(lSon,cMin[node],cMax[node],cMin[lSon],cMax[lSon]);
            goNext(rSon,cMin[node],cMax[node],cMin[rSon],cMax[rSon]);

            long mid = (l+r)>>1;
            getResult(lSon,l,mid);
            getResult(rSon,mid+1,r);
        }

long n,m,i,op,l,r;

int main()
{
    //freopen("test.in","r",stdin);

    init();

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld %ld",&op,&l,&r,&HH); l++; r++;
        if(op==1) UpdateMin(1,1,n,l,r);
        else      UpdateMax(1,1,n,l,r);
    }

    getResult(1,1,n);

    return 0;
}

