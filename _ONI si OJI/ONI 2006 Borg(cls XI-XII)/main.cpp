#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 25
#define mod 30103
#define long int

long n,m,h,k,i,N;
long Cn[maxN],Cm[maxN],Ch[maxN];
long Ck[maxN*maxN*maxN];
long a,b,c,ans;

long myPow(long a,long b){
    long ans = 1;
    while(b){
        if(b&1)ans = (ans*a)%mod;
        b>>=1;
        a = (a*a)%mod;
    }
    return ans;
}

long inv(long x){
    return myPow(x,mod-2);
}

long mm(long x){
    while(x<0) x+=mod;
    while(x>=mod) x-=mod;
    return x;
}

int main()
{
    freopen("borg.in","r",stdin);
    freopen("borg.out","w",stdout);

    scanf("%d %d %d %d",&n,&m,&h,&k);

    memset(Cn,0,sizeof(Cn));
    memset(Cm,0,sizeof(Cm));
    memset(Ch,0,sizeof(Ch));
    memset(Ck,0,sizeof(Ck));

    Cn[1] = n; Cn[0]=1;
    for(i=1;i<n;i++) Cn[i+1] = ((Cn[i]*(n-i))%mod*inv(i+1))%mod;
    Cm[1] = m; Cm[0]=1;
    for(i=1;i<m;i++) Cm[i+1] = ((Cm[i]*(m-i))%mod*inv(i+1))%mod;
    Ch[1] = h; Ch[0]=1;
    for(i=1;i<h;i++) Ch[i+1] = ((Ch[i]*(h-i))%mod*inv(i+1))%mod;

    Ck[k] = 1; N = n*m*h;
    for(i=k;i<N;i++) Ck[i+1] = ((Ck[i]*(i+1))%mod*inv(i+1-k))%mod;

    ans=0;
    for(a=0;a<=n;a++){
        for(b=0;b<=m;b++){
            for(c=0;c<=h;c++){
                long sgn = 1;
                if((a+b+c)&1) sgn=-1;

                sgn = mm(sgn*Cn[a] );
                sgn = mm(sgn*Cm[b] );
                sgn = mm(sgn*Ch[c] );
                sgn = mm(sgn*Ck[(n-a)*(m-b)*(h-c)] );

                ans = mm(ans+sgn);
            }
        }
    }

    printf("%d",ans);
    //cerr << ans;

    return 0;
}
