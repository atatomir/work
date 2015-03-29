#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define mp make_pair
#define val first
#define xx second.first
#define yy second.second
#define maxN 505

typedef pair<long,pair<long,long> >  Elem;

long op,n,m,k,i,j,cont,nn,dist;
vector<Elem> A;
Elem e;

long lMin[maxN],lMax[maxN];

long ansMin;

long abss(long x){
    if(x < 0) return -x;
    return x;
}

int main()
{
    freopen("rascoala.in","r",stdin);
    freopen("rascoala.out","w",stdout);

    scanf("%ld %ld %ld %ld",&op,&n,&m,&k);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%ld",&e.val);
            e.xx = i; e.yy = j;
            A.push_back(e);
        }
    }
    sort(A.begin(),A.end());
    nn = n; n = n*m;

    for(i=1;i<n;i++){
        long need = i*(A[i].val-A[i-1].val);
        if(!need) continue;
        if(need  <= k){
            k -= need;
            cont = i;
        } else {
            ansMin = A[i-1].val + k/i;
            if(k < i) cont = max(cont,k); else cont = i;
            k = 0;
        }

        if(!k) break;
    }

    if(k) {
        ansMin = A[n-1].val + k/n;
        if(k >= n) cont = n; else cont = max(cont,k);
    }

    if(op == 1){
        printf("%ld\n%ld",cont,ansMin);
    } else {
        for(i=1;i<=nn;i++) lMin[i] = maxN;
        for(i=0;i<cont;i++){
            lMax[A[i].xx] = max(lMax[A[i].xx],A[i].yy);
            lMin[A[i].xx] = min(lMin[A[i].xx],A[i].yy);
        }

        for(i=1;i<=nn;i++){
            if(lMin[i] == maxN) continue;
            for(j=i;j<=nn;j++){
                if(lMin[j] == maxN) continue;
                dist = max(dist,j-i + abss(lMin[i]-lMax[j]));
                dist = max(dist,j-i + abss(lMin[j]-lMax[i]));
            }
        }

        printf("%ld",dist);
    }

    return 0;
}
