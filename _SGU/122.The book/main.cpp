#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 1011
#define maxL 1000000

long n,i,j,x,len;
bool G[maxN][maxN];
long Ans[maxN << 1];
char s[maxL];
long pos;

void Invert(long i ,long j){
    while(i<j){
        long t = Ans[i] ; Ans[i] = Ans[j]; Ans[j] = t;
        i++; j--;
    }
}

int main()
{
    scanf("%ld\n",&n);
    for(i=1;i<=n;i++){
        gets(s); len = strlen(s); pos = 0;
        while(pos < len){
            while(s[pos] < '0' || s[pos] > '9') {
                pos++; if(pos == len) break;
            }
            if(pos == len) break;

            x = 0;
            while(s[pos] >= '0' && s[pos] <= '9'){
                x = x*10 + s[pos++] - '0';
                if(pos == len) break;
            }

            if(x) G[i][x] = true;
        }
    }

    for(i=1;i<=n;i++){
        Ans[i] = Ans[i+n] = i;
    }

    for(i=1;i<=n;i++){
        if(G[Ans[i]][Ans[i+1]]) continue;
        for(j=i+2;j<=n;j++){
            if(G[Ans[i]][Ans[j]] && G[Ans[i+1]][Ans[j+1]]){
                Invert(i+1,j);
                break;
            }
        }
        if(G[Ans[i]][Ans[i+1]]) continue;
        for(j=i-2;j>0;j--){
            if(G[Ans[i]][Ans[j]] && G[Ans[i+1]][Ans[j+1]]){
                Invert(j+1,i);
                break;
            }
        }
    }

    for(i=1;i<=n+1;i++) printf("%ld ",Ans[i]);

    return 0;
}
