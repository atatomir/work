#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 1024*1024

long n,i;
long long a[maxN];
long p;

long long ans,ansP1,ansP2;

void goNext(){
    while(p+1<n && a[p+1]-a[i]<=a[n]-a[p+1]) p++;
}

int main()
{
    freopen("3secv.in","r",stdin);
    freopen("3secv.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&a[i]);
        a[i] += a[i-1];
    }

    i = 1; p=2; goNext(); ans = 1<<30;
    for(i=1;i<=n-2;i++){
        goNext();
        if(p>i){
            long long a1 = a[i];
            long long a2 = a[p]-a[i];
            long long a3 = a[n]-a[p];

            long long mMin = min(min(a1,a2),a3);
            long long mMax = max(max(a1,a2),a3);
            long long mM = mMax-mMin;

            if(ans>mM || (ans==mM && i==ansP1 && p<ansP2)){
                ans = mM;
                ansP1 = i; ansP2 = p;
            }
        }
        if(p+1<=n){ //! mereu valabil
            p++;

            long long a1 = a[i];
            long long a2 = a[p]-a[i];
            long long a3 = a[n]-a[p];

            long long mMin = min(min(a1,a2),a3);
            long long mMax = max(max(a1,a2),a3);
            long long mM = mMax-mMin;

            if(ans>mM || (ans==mM && i==ansP1 && p<ansP2)){
                ans = mM;
                ansP1 = i; ansP2 = p;
            }

            p--;
        }
    }

    printf("%lld %lld",ansP1,ansP2);

    return 0;
}
