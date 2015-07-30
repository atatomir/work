#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 211
#define mod 1000003
#define INF 1000000000
#define lim 20

const char def[6]={'a','e','i','o','u','y'};

long n,i,j,Dim,voc,pas;
char s[maxN];
long Ans[maxN][maxN],Cnt[maxN][maxN],Op[maxN],Prov[maxN][maxN];;
bool ok;

long Sp[maxN];

int main()
{
    freopen("text2.in","r",stdin);
    freopen("text2.out","w",stdout);

    scanf("%s%ld",s+1,&n);
    Dim = strlen(s+1);

    for(i=1;i<=Dim;i++){
        for(j=0;j<6;j++){
            if(s[i] == def[j]){
                Op[++voc] = i;
                break;
            }
        }
    }

    for(i=Op[1];i<=Dim && i <= lim;i++) {
        Ans[1][i] = i*i;
        Cnt[1][i] = 1;
    }
    for(pas=2;pas<=n;pas++){
        for(i=Op[pas];i<=Dim;i++){
            Ans[pas][i] = INF;

            j = i; ok = false;
            while(!ok){
                for(long tmp=0;tmp<6;tmp++){
                    if(s[j] == def[tmp]){
                        ok = true; break;
                    }
                }
                j--;
            }
            long maxim = j;
            for(j = max(Op[pas-1],i-lim);j<=maxim;j++){
                Cnt[pas][i] += Cnt[pas-1][j];
                if(Cnt[pas][i] >= mod) Cnt[pas][i] -= mod;

                if(Cnt[pas-1][j]==0) continue;
                if(Ans[pas][i] > Ans[pas-1][j] + (i-j)*(i-j)){
                    Ans[pas][i] = Ans[pas-1][j] + (i-j)*(i-j);
                    Prov[pas][i] = j;
                }
            }
        }
    }

    printf("%ld\n%ld\n",Cnt[n][Dim],Ans[n][Dim]);

    pas = Dim;
    long nivel = n;
    for(i=1;i<=n;i++){
        Sp[i] = Prov[nivel][pas];
        pas = Prov[nivel--][pas];
    }

    i = 1; Sp[0] = Dim;
    for(j=n-1;j>=0;j--){
        while(i != Sp[j]){
            printf("%c",s[i++]);
        }
        printf("%c ",s[i++]);
    }

    return 0;
}
