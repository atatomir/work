#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <assert.h>

using namespace std;

//#define DEBUG
#ifdef DEBUG
    #define myDebug
#endif // DEBUG

#define maxN 20011
#define maxM 57

long n,m,w,i,j;
long v[maxN],sor[maxN];
stack<long> notGood[maxM];
long cnt[maxM];

long R,how;
vector< vector<long> > ans;
vector<long> act;
vector<long> actCh;

long getNext(long col){
    if(notGood[col].empty()) return 0;
    while( v[ notGood[col].top() ] == sor[ notGood[col].top() ] ||
           v[ notGood[col].top() ] != col                        ) {
        notGood[col].pop();
        if(notGood[col].empty()) return 0;
    }

    return notGood[col].top();
}

void TryNewChange(long pos,long lim){
    act.clear();
    act.push_back(pos); lim--;
    long firstCol = v[pos];

    while(lim && getNext(sor[pos]) ){
        v[pos] = sor[pos];
        pos = getNext(sor[pos]);
        act.push_back(pos); lim--;
    }
    v[pos]=firstCol;
    if(v[pos]!=sor[pos])notGood[firstCol].push(pos);

    if(act.size()==1) return;

    act.push_back(act[0]);
    for(long i=0;i<act.size()-1;i++){
        actCh.push_back(act[i+1]);
        actCh.push_back(act[i]);
    }
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld %ld",&n,&m,&w);
    for(i=1;i<=n;i++){
        scanf("%ld",&v[i]);
        cnt[v[i]]++;
    }

    n=0;
    for(i=1;i<=m;i++){
        while(cnt[i]){
            sor[++n] = i;
            cnt[i]--;
        }
    }

    for(i=1;i<=n;i++)
        if(v[i]!=sor[i])
            notGood[ v[i] ].push(i);

    ans = vector< vector<long> >(0, vector<long>(0) );

    i=1;
    for(bool diff=true;diff;){
        diff=false; how=0; actCh.clear();

        #ifdef myDebug
            long vv = 0;
            for(long jj=1;jj<=n;jj++)
                if(v[jj]!=sor[jj]) vv++;
            cerr << "\n Unsolved: " << vv << "\n";
        #endif // DEBUG

        for(i=1;i<=n && how<w;i++){
            if(v[i]==sor[i]) continue;

            diff=true;
            TryNewChange(i,w-how);
            how += act.size()-1;
        }

        if(diff)ans.push_back(actCh);
    }

    printf("%ld\n",ans.size());
    for(i=0;i<ans.size();i++){
        printf("%ld ",ans[i].size()/2);
        for(j=0;j<ans[i].size();j++) printf("%ld ",ans[i][j]);
        printf("\n");
    }

    return 0;
}
