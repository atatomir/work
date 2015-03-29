#include <iostream>
#include <cstdio>
#include <cmath>

#define bulaneala 1e9

using namespace std;

long  n,m,i,pos=0,dim,ngr,x,actg,val,p,ans,lim;
char s[1300000];
int op;
long long a[100005],gr[400],sum[400],act;

long getLong() {
    long ans=0;
    while(s[pos] == ' ') pos++;
    while((s[pos]>='0')&&(s[pos] <='9')) {
        ans = ans*10 + s[pos] - '0';
        pos++;
    }
    return ans;
}

inline void reCalculate(long pos){
    long bg = (pos-1)*dim+1,en=pos*dim,i;
    long long val=0;
    gr[pos] = 0; sum[pos] = 0;
    for(i=en;i>=bg;i--){
        if(val <= a[i]){
            gr[pos] += a[i] - val+1;
            val = a[i]*2+1;
        } else {
            val += a[i];
        }
        sum[pos] += a[i];
    }
}

int main()
{
    freopen("kami.in","r",stdin);
    freopen("kami.out","w",stdout);

    scanf("%ld\n",&n);
    gets(s);
    for(i=1;i<=n;i++){
        a[i] = getLong();
    }

    dim = (long)sqrt((double)n);
    ngr = (n + dim -1)/dim;
    gr[0] = 1LL << 60;
    a[0] = gr[0];

    for(i=1;i<=ngr;i++)  reCalculate(i);

    scanf("%ld\n",&m);

    for(i=1;i<=m;i++){
        scanf("%d",&op);
        if(op == 0){
            scanf("%ld %ld\n",&x,&val);
            a[x] = val;
            reCalculate((x+dim-1)/dim);
        } else {
            scanf("%ld\n",&x);
            actg = (x+dim-1)/dim;

            act = a[x]; ans = -1; lim = dim*(actg-1);
            for(p=x-1;p>lim;p--) {
                if(a[p] < act) act = act+a[p]; else {ans = p; break;}
            }
            if(ans != -1){
                printf("%ld\n",ans);
            } else {
                actg--;
                while(gr[actg] <= act){
                    act += sum[actg--];
                    if(act > bulaneala) {ans = 0; break;}
                }
                p = dim * actg;
                if(ans == 0) p = 0;
                while(a[p] < act) {
                    act += a[p];
                    p--;
                }

                printf("%ld\n",p);
            }

        }
    }

    return 0;
}
