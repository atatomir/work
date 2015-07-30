#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

//#define DEBUG
#define maxN (1030)
#define am_valoare true

long n,i,j,op,x,y,l,b,r,t;
long aib[maxN][maxN];
long v;

inline long zrs(long x) { return (x^(x-1))&x; }
void add(long x,long y,long v){
    long _y=y;
    while(x<=n){
        y = _y;
        while(y<=n){
            aib[x][y] += v;
            y += zrs(y);
        }
        x += zrs(x);
    }
}
long sum(long x,long y){
    long ans = 0;
    long _y=y;
    while(x){
        y = _y;
        while(y){
            ans += aib[x][y];
            y -= zrs(y);
        }
        x -= zrs(x);
    }
    return ans;
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    while( am_valoare ){
        scanf("%d",&op);
        if(op==1){
            scanf("%ld %ld %ld\n",&x,&y,&v); x++; y++;
            add(x,y,v);
        }else
        if(op==2){
            scanf("%ld %ld %ld %ld\n",&l,&b,&r,&t); l++;b++;r++;t++;
            printf("%ld\n", sum(r,t)-sum(r,b-1)-sum(l-1,t)+sum(l-1,b-1) );
        }else
        if(op==3) { fflush(stdin); return 0;}
        else
        if(op==0)  {
            scanf("%ld\n",&n);
            //aib = vector< vector<long> >(n+10, vector<long>(n+10,0) );
        }
    }

    return 0;
}


