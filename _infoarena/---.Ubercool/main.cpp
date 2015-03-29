#include <cstdio>
#include <cmath>

using namespace std;

long t,ti,i,pr[100005]={0},h=1e6;
char ciur[1000020];
long long x,v,max=1e18,pows[170000]={0};


inline void do_ciur() {
    for(i=2;i<=h;i++) ciur[i] = 1;
    t = (long)sqrt((double)h);
    for(i=2;i<=t;i++) {
        for(long j=i;j*i<=h;j++) ciur[i*j] = 0;
    }
    for(i=2;i<=h;i++) {
        if(ciur[i]) {
            pr[++pr[0]] = i;
            //printf("%ld ! %ld\n",pr[0],i);
        }
    }
}

inline int prim(long long x) {
    if (x <= 1e6) {
        return ciur[x];
    } else {
        for (long i=1;(i<=pr[0])&&(pr[i]*pr[i]<=x);i++)
            if (x % pr[i] == 0) return 0;
    }

    return 1;
}

void QSort(long l,long h) {
    long i=l,j=h;
    long long x=pows[(i+j)/2],y;
    do {
        while (pows[i] < x) i++;
        while (pows[j] > x) j--;
        if (i <= j) {
            y = pows[i]; pows[i] = pows[j]; pows[j] = y;
            i++; j--;
        }
    }   while (i<=j);
    if (l < j) QSort(l,j);
    if (i < h) QSort(i,h);
}

long cb(long long x) {
    long i=1,j=pows[0],m;
    do {
        m = (i+j)/2;
        if (x <= pows[m])
            j = m-1;
        else
            i = m+1;
    }   while(i <= j);
    if (pows[i] == x)
        return 1;
    else
        return 0;
}

int ubercool(long long x) {
    if (cb(x))
        return 1;
    else {
        v = (long long)sqrt((double)x);
        if (v*v == x) {
            return prim(v);
        } else return 0;
    }
}

int main()
{
    freopen("ubercool.in","r",stdin);
    freopen("ubercool.out","w",stdout);

    do_ciur();

    for (i=1;i<=pr[0];i++) {
       v = pr[i];
       while (max/v >= pr[i]) {
            v *= pr[i];
            pows[++pows[0]] = v;
       }
    }
    QSort(1,pows[0]);


    scanf("%ld\n",&t);
    for(ti=1;ti<=t;ti++) {
        scanf("%lld\n",&x);

        if (ubercool(x))
            printf("%s\n","DA");
        else
            printf("%s\n","NU");
    }

    return 0;
}
