#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define maxQ 150011
#define maxN 4011
#define INF 55555

long q,n,m,i,sum,s,d,nm;
long dp[2][maxQ];
long dim[maxN];

deque< long > DQ;
long gut[maxQ];

void vajaie(long how){
    while(!DQ.empty()) DQ.pop_back();
    long i;

    for(i=0;i<=q;i++){
        long v = dp[s][i];

        if(!DQ.empty())
        while( dp[s][DQ.back()] >= v ){
            DQ.pop_back();
            if(DQ.empty()) break;
        }
        DQ.push_back(i);

        if(DQ.front() == i-how) DQ.pop_front();

        gut[i] = dp[s][ DQ.front() ];
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    scanf("%ld %ld %ld",&q,&n,&m); nm = n+m;
    for(i=1;i<=nm;i++) scanf("%ld",&dim[i]);

    s = 0; d = 1; dp[s][0]=0;
    for(i=1;i<=q;i++) dp[s][i]=INF;

    for(i=1;i<=nm;i++){
        vajaie(dim[i]);
        for(sum=0;sum<=q;sum++){
            dp[d][sum] = min(dp[s][sum], gut[sum-1]+1 );

            if(sum- dim[i]<0) continue;

            if(i<=n)
                dp[d][sum] = min(dp[d][sum], dp[s][sum- dim[i] ] );
            else
                dp[d][sum] = min(dp[d][sum], dp[s][sum- dim[i] ]+1 );
        }

        swap(s,d);
    }

    printf("%ld",q-dp[s][q]);

    return 0;
}
