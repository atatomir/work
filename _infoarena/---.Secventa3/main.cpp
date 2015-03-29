#include <cstdio>

using namespace std;


struct {
    long double v;
    long pos;
} deq[30005];

long n,i,l,u,j,c[30005],t[30005],op,mop,di,dj,dist;
long double left,right,mij,s[30005],minim[30005];

inline int check(long double x){
    long i;
    di = 1; dj = 0;

    for(i=1;i<=n;i++) {
        s[i] = (long double)c[i] - x*t[i] + s[i-1];

        while((di<=dj)&&(deq[dj].v >= s[i])) dj--;
        deq[++dj].v = s[i]; deq[dj].pos = i;
        while(deq[di].pos <= i - dist) di++;

        minim[i] = deq[di].v;

        if(i >= l) {
            if(s[i] - minim[i-l] >= 0)
                return 1;
        }

    }

    return 0;
}

int main()
{
    freopen("secv3.in","r",stdin);
    freopen("secv3.out","w",stdout);

    scanf("%ld %ld %ld\n",&n,&l,&u);
    for(i=1;i<=n;i++) scanf("%ld ",&c[i]);
    for(i=1;i<=n;i++) scanf("%ld ",&t[i]);

    left = 0; right = 1000; mop = 20; op = 0;
    dist = u-l+1;

    do {
        mij = (left + right)/2; op++;
        if (check(mij))
            left = mij;
        else
            right = mij;
    } while (op < mop);

    left = (left+right)/2;
    printf("%.2lf\n",(double)left);

    return 0;
}
