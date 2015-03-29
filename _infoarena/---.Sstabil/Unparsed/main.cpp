#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 1000111

long n,i,li,x,t,cont;
vector<long> v;
long ans[maxN];

int main()
{
    freopen("sstabil.in","r",stdin);
    freopen("sstabil.out","w",stdout);

    scanf("%ld",&n);
    long nn=n; n = 0;
    for(i=1;i<=nn;i++){
        scanf("%ld",&x);
        if(x) v.push_back(x),n++;
    }

    for(i=0;i < n-1-i;i++) {t=v[i];v[i]=v[n-i-1];v[n-1-i]=t;}

    cont = 1; ans[1] = v[0];
    li = 0;

    for(i=1;i<n;i++){
        if(ans[cont] + ans[cont+1] > 9) cont++,li = i-1;
        if(ans[cont+1] + v[i] > 9) {
            ans[cont] += v[++li];
            ans[cont+1] -= v[li];
            i--;
        } else {
            ans[cont+1] += v[i];
        }
    }

    if(ans[cont] + ans[cont+1] > 9)
        cont++;
    else
        ans[cont] += ans[cont+1];

    for(i=cont;i;i--) printf("%ld",ans[i]);

    return 0;
}
