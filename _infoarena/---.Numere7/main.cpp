#include <iostream>
#include <cstdio>

using namespace std;

#define maxCN 20

unsigned long long n,x,nr,i,cf,how,j;
unsigned long long cnt[10];
bool good;

unsigned long long C[maxCN+5][maxCN+5];
char s[maxCN+5],ss[maxCN+5];

void preProcess(){
    long i,j;
    for(i=1;i<=maxCN;i++){
        C[i][1]=i;
        for(j=2;j<=i;j++) C[i][j] = C[i-1][j-1]+C[i-1][j];
    }
}

int main()
{
    freopen("numere7.in","r",stdin);
    freopen("numere7.out","w",stdout);

    scanf("%lld %s",&n,ss);
    if(n==0){
        printf("-1");
        return 0;
    }
    i=0;
    while(ss[i]!='\0'){
        long cf = ss[i]-'0';
        cnt[cf]++; nr++; i++;
    }

    preProcess();
    for(i=1;i<=nr;i++){
        good=false;
        for(cf=0;cf<10;cf++){
            if(i==1 && cf==0) continue;
            if(cnt[cf]==0) continue;

            cnt[cf]--; how=1;
            long tmp = nr-i;
            for(j=0;j<10;j++){
                if(cnt[j]==0) continue;
                how *= C[tmp][cnt[j]];
                tmp -= cnt[j];
            }

            if(how>=n){
                s[i]=cf+'0'; good=true;
                break;
            } else {
                n -= how;
                cnt[cf]++;
            }
        }
        if(good==false) break;
    }

    if(good) printf("%s",s+1); else printf("-1");

    return 0;
}
