#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int a[2005];
char s[2005];
long n,i,v;

inline void div2() {
    for(i=n;i>=1;i--){
        a[i-1] += 10 * (a[i] % 2);
        a[i] /= 2;
    }
    while(a[n] == 0) n--;
}

inline void decr(long x){
    a[1] -= x;
    while(a[1] < 0) a[1] += 10,a[2]--;
    for(i=2;i<=n;i++){
        while(a[i] < 0) a[i] += 10,a[i+1]--;
    }
    while(a[n] == 0) n--;
}


int main()
{
    freopen("minge.in","r",stdin);
    freopen("minge.out","w",stdout);

    scanf("%s",s);
    n = strlen(s);

    for(i=0;i<n;i++) a[n-i] = s[i] - '0';

    if(a[1] % 2 == 1){
        decr(1);
        div2();
    } else {
        v = a[2]*10+a[1];
        if(v % 4 == 0){
            div2();
            decr(1);
        } else {
            div2();
            decr(2);
        }
    }

    for(i=n;i>=1;i--) printf("%d",a[i]);

    return 0;
}
