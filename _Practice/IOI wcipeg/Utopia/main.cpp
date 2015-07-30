#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#ifndef ONLINE_JUDGE
    #define DEBUG
#endif
#define maxN 10001
#define inv(yepi) (yepi>0?'-':'+')
#define wr(x) ( x>0? printf("+%ld",x):printf("%ld",x)  );

long n,i,x;
long a[2][maxN];
char ch[2][maxN];
vector<long> ans[2];

void goThere(long def,long pos,char sgn,long pas){
    if(pos==0 || pos==n+1) return;
    if(sgn=='-') a[def][pos]*=-1;
    goThere(def,pos+pas, inv(a[def][pos]) , pas );
}

void solve(long def){
    sort(a[def]+1,a[def]+n+1);

    long i,j,k;
    for(k=1,i=1;k<n;k++)
        if(ch[def][k]==ch[def][k+1]) i++;
    j=i;

    if(ch[def][1]=='-') a[def][i] *= -1;
    goThere(def,i+1, inv(a[def][i]) , +1 );
    goThere(def,i-1, inv(a[def][i]) , -1 );


    ans[def].push_back( a[def][i] );
    for(k=2;k<=n;k++){
        if(ch[def][k]!=ch[def][k-1]) ans[def].push_back( a[def][++j] );
        else                         ans[def].push_back( a[def][--i] );
    }
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld",&a[0][i]);
    for(i=1;i<=n;i++) scanf("%ld",&a[1][i]);

    for(i=1;i<=n;i++){
        scanf("%ld",&x);
        if(x==1||x==4) ch[0][i] = '+'; else ch[0][i] = '-';
        if(x==1||x==2) ch[1][i] = '+'; else ch[1][i] = '-';
    }

    solve(0);
    solve(1);

    for(i=1;i<=n;i++){
        wr(ans[0][i-1]);
        printf(" ");
        wr(ans[1][i-1]);
        printf("\n");
    }

    return 0;
}
