#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

#define x first
#define y second
#define maxN 100011

typedef pair<long,long> Point;

long n,p,i,t,p1,p2,cont;
Point Pts[maxN];

bool Good(long a,long b,long c){
    long val = Pts[a].x*Pts[b].y - Pts[b].x*Pts[a].y +
               Pts[b].x*Pts[c].y - Pts[c].x*Pts[b].y +
               Pts[c].x*Pts[a].y - Pts[a].x*Pts[c].y ;
    return val == 0;
}

int main()
{
    freopen("findinglines.in","r",stdin);
    freopen("findinglines.out","w",stdout);

    scanf("%ld %ld",&n,&p);
    if((n*p) % 100 == 0){
        p = (n*p)/100;
    } else {
        p = (n*p)/100+1;
    }

    if(n == 1){
        printf("possible");
        return 0;
    }

    for(i=1;i<=n;i++) scanf("%ld %ld",&Pts[i].x,&Pts[i].y);

    srand(time(NULL));

    for(t=500;t;t--){
        p1 = rand()%n + 1;
        p2 = rand()%n + 1;
        if(p1 == p2) continue;

        cont = 0;
        for(i=1;i<=n;i++){
            if(Good(p1,p2,i)){
                cont++;
                if(cont == p){
                    printf("possible");
                    return 0;
                }
            }
        }
    }

    printf("impossible");
    return 0;
}
