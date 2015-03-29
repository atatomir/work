#include <cstdio>

#define mod 666013

using namespace std;

long n,m,i,pos;
long long x,cod,ans;
char s[1000005];

long long getLongLong() {
    long ans=0,semn=1;
    while(s[pos] == ' ') pos++;
    if(s[pos] == '-') {
        semn = -1;
        pos++;
    }
    while((s[pos]>='0')&&(s[pos] <= '9')){
        ans = ans*10 + s[pos] - '0';
        pos++;
    }
    return ans*semn;
}

int main()
{
    freopen("antocod.in","r",stdin);
    freopen("antocod.out","w",stdout);

    scanf("%ld %ld\n",&n,&m);
    gets(s);

    for(i=1;i<=m;i++){
        x = getLongLong();
        cod = (cod + x) % mod;
    }

    ans=1;
    while(n){
        if(n&1) ans = (ans*cod)% mod;
        cod = (cod*cod)% mod;
        n >>= 1;
    }

    printf("%lld\n",ans);

    return 0;
}
