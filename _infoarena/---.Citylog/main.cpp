#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 100005
#define maxLog 6

long n,i,m,current,base,rep;
long a[maxN][maxLog];
long tip,x,y;

void Complete(long source){
    long x = a[source][0],i,j;
    for(i=1;i<=maxLog;i++){
        for(j=1;j<=9;j++) x = a[x][i-1];
        a[source][i] = x;
        if(x == 0) return;
    }
}

int main()
{
    freopen("citylog.in","r",stdin);
    freopen("citylog.out","w",stdout);

    scanf("%ld %ld\n",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld\n",&tip,&x,&y);
        x ^= current; y ^= current;
        if(tip == 0){
            a[x][0] = y;
            Complete(x);
        } else {
            base = 0;
            while(y){
                rep = y % 10; y /= 10;
                for(;rep;rep--) x = a[x][base];
                base++;
                if(x == 0) break;
            }
            current = x;
            printf("%ld\n",current);
        }
    }

    return 0;
}
