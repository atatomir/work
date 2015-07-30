#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 30010

long n,i,a[maxN],poz,minim,tmp,mini,minj;

int main()
{
    freopen("secv7.in","r",stdin);
    freopen("secv7.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&a[i]);
        if(a[poz] < a[i]) poz = i;
        else
        if(a[poz] == a[i] && i != n) poz = i;
    }

    minim = 1000000000;
    if(poz != 1 && poz != n) {
        minim = a[poz] + a[1] + a[n];
        mini = 1; minj = n-1;
    }

    tmp = a[n];
    for(i=n-1;i>poz;i--){
        long val = a[poz] + tmp + a[i];
        if(minim > val){
            minim = val;
            mini = i-1; minj = i;
        }
        tmp = max(tmp,a[i]);
    }

    tmp = a[1];
    for(i=2;i<poz;i++){
        long val = a[poz] + tmp + a[i];
        if(minim > val){
            minim = val;
            mini = i-1; minj = i;
        }
        tmp = max(tmp,a[i]);
    }

    printf("%ld\n%ld %ld",minim,mini,minj);

    return 0;
}
