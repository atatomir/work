#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 100011
#define maxK 32
#define all(V) V.begin(),V.end()

int n,k,i,j,v,ans;
char s[maxN];
int dp[maxN][maxK];
int val[maxN][maxK];

vector<int> st;

int main()
{
    freopen("blis.in","r",stdin);
    freopen("blis.out","w",stdout);

    scanf("%d\n",&k);
    scanf("%s",s+1); n = strlen(s+1); k=min(n,k);

    //! subpct a
    for(i=1;i<k;i++)
        if(s[i]=='1') v |= 1<<(k-1-i);

    for(i=k;i<=n;i++){
        v &= (1<<(k-1))-1;
        v <<= 1;
        if(s[i]=='1') v|=1;

        ans = max(ans,v);
    }
    printf("%d\n",ans);

    //! subpct b

    for(i=1;i<=n;i++){
        v = 0;
        for(j=1;j<=k;j++){
            if(i-j<0) break;
            if(s[i-j+1]=='1') v|=1<<(j-1);

            val[i][j]=v;
        }
    }

    st.push_back(-1);
    for(i=0;i<=n;i++){
        //! update
        for(j=1;j<=k;j++){
            if(i-j<0) break;

            int pos = dp[i][j];
            if(pos == st.size()) st.push_back( val[i][j] ); else
            if(val[i][j] < st[pos]) st[pos] = val[i][j];
        }

        //! query
        for(j=1;j<=k;j++){
            if(i+j>n) break;

            vector<int>::iterator it = lower_bound( all(st),val[i+j][j] );
            int pos = it - st.begin();
            dp[i+j][j]=pos;
        }
    }

    printf("%d",st.size()-1);

    return 0;
}
