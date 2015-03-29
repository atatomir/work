#include <cstdio>

using namespace std;

long n,k,a[16005],i,maxim=0;
long long sum=0,left,right,mid;


inline int check(long long x) {
    long trans=0;
    long long act = 0;
    for(i=1;i<=n;i++){
        if (act + a[i] <= x)
            act += a[i];
        else {
            trans++;
            act =a[i];
        }
    }
    if (trans < k)
        return 1;
    else
        return 0;
}

int main()
{
    freopen("transport.in","r",stdin);
    freopen("transport.out","w",stdout);

    scanf("%ld %ld\n",&n,&k);
    for(i=1;i<=n;i++){
       scanf("%ld\n",&a[i]);
       sum += a[i];
       if (maxim < a[i]) maxim = a[i];
    }

    left = maxim; right = sum;
    do {
        mid = (left+right)/2;
        if(check(mid))
            right = mid-1;
        else
            left = mid+1;
    }   while(left<=right);
    printf("%lld\n",left);

    return 0;
}
