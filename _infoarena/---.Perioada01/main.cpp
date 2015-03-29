#include <iostream>
#include <cstdio>
  
using namespace std;
  
#define maxN 3000111
  
long n,i,m,pos,x,cont,per,q;
long a[maxN],pr[maxN],Ans;
  
inline void make_pref() {
    pr[1] = 0; q =0;
    for(i=2;i<=a[0];i++) {
        while((q != 0)&&(a[q+1] != a[i])) q = pr[q];
        if (a[q+1] == a[i]) q++;
        pr[i] = q;
    }
}
  
int main()
{
    freopen("perioada01.in","r",stdin);
    freopen("perioada01.out","w",stdout);
  
    scanf("%ld %ld",&n,&m);
  
    scanf("%ld",&x);
    per = 1000000001;
    if(x > 1) {
        per = x-1;
        a[0] = 1; a[1] = (x-1)<<1;
    }
    a[++a[0]] = 1; pos = x;
  
    for(i=2;i<=m;i++){
        scanf("%ld",&x);
        cont = x - pos - 1;
        if(cont){
            if(cont > per){
                a[++a[0]] = (cont-per)<<1;
                a[++a[0]] = per<<1;
            } else {
                a[++a[0]] = cont<<1;
            }
        }
        a[++a[0]] = 1;
        pos = x;
    }
  
    if(pos < n) a[++a[0]] = (n-pos)<<1;
    make_pref();
  
    per = a[0] - pr[a[0]];
    if(a[0] % per || per == a[0]){
        printf("-1");
    } else {
        for(i=1;i<=per;i++){
            if(a[i] > 1) Ans += a[i] >> 1; else Ans++;
        }
        printf("%ld",Ans);
    }
  
    return 0;
}