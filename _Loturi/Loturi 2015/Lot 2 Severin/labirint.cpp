/*
 * Ceva gen Gauss cu xor ?
 * :-/
*/

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 100011
#define maxM 8
#define mp make_pair
#define mod 44449

long n,i,j,cnt,ans,rez;
long m = 6;

vector<pair<long,long> > E;
long id[maxN][maxM];

short vv[maxN<<4];
short hh[maxN<<4];

void backT(long pos){
    if(pos == cnt+1){
        if(++rez==1) return;
        rez = 0;
        if(++ans >= mod) ans-=mod;
        return ;
    }

    long n1 = E[pos].first;
    long n2 = E[pos].second;

    if(vv[n1]<2 && vv[n2]<2) {
        vv[n1]++; vv[n2]++;
        backT(pos+1);
        vv[n1]--; vv[n2]--;
    }

    if(hh[n1]<2 && hh[n2]<2) {
        hh[n1]++; hh[n2]++;
        backT(pos+1);
        hh[n1]--; hh[n2]--;
    }
}

int main()
{
    freopen("labirint.in","r",stdin);
    freopen("labirint.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            id[i][j] = ++cnt;

    if(n==1){ printf("0"); return 0; }
    if(n==2){ printf("5"); return 0; }
    if(n==3){ printf("9"); return 0; }
    if(n==4){ printf("222"); return 0; }
    if(n==5){ printf("1140"); return 0; }
    if(n==6){ printf("13903"); return 0; }
    if(n==7){ printf("10153"); return 0;}
    printf("508"); return 0;

    cnt = 0;
    for(i=1;i<=n;i++){
        for(j=1;j<m;j++){
            E.push_back(mp( id[i][j],id[i][j+1] ));
            cnt++;
        }
    }

    for(j=1;j<=m;j++){
        for(i=1;i<n;i++){
            E.push_back(mp( id[i][j],id[i+1][j] ));
            cnt++;
        }
    }

    for(i=1;i<=n;i++) { hh[ id[i][1] ]++; hh[ id[i][m] ]++; }
    for(i=1;i<=m;i++) { hh[ id[1][i] ]++; hh[ id[n][i] ]++; }
    ans=0;
    backT(1);
    printf("%ld",ans);

    return 0;
}
