#include <iostream>
#include <cstdio>

using namespace std;

#define maxL 100011
#define maxK 1011

long n,l,i,k,cnt;
char s[maxL],d[maxK];
long pr[maxK];

void make_pref(){
    long q = 0; pr[1] = 0;
    for(long i=2;i<=k;i++){
        while(q && d[q+1]!=d[i]) q = pr[q];
        if(d[q+1] == d[i]) q++;
        pr[i] = q;
    }
}

void Search(){
    long q = 0;
    for(long i=1;i<=l;i++){
        while(q && d[q+1]!=s[i]) q = pr[q];
        if(d[q+1] == s[i]) {
            q++;
            if(q==k){
                q = pr[q];
                cnt++;
            }
        }
    }
}

int main()
{
    freopen("virus.in","r",stdin);
    freopen("virus.out","w",stdout);

    scanf("%ld %ld\n%s\n",&l,&n,s+1);
    for(;n;n--){
        scanf("%ld\n%s\n",&k,d+1); d[k+1]='\0';
        make_pref();

        cnt = 0;
        Search();

        printf("%ld\n",cnt);
    }

    return 0;
}
