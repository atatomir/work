#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

//#define DEBUG
#define maxN 1024
#define val first
#define id second
#define mp make_pair
#define PI pair<long,long>

long n,m,l,c,ll,cc,i,j,k,how;
long a[maxN][maxN]; //! matrix
long sum[maxN][maxN]; //! sums
long sB[maxN][maxN]; //! big sums
long sS[maxN][maxN]; //! small sums
long cW[maxN][maxN]; //! column window
long lW[maxN][maxN]; //! line window

long def[maxN]; //! for Sliding window
deque< pair<long,long> > DQ;

long ans=-(1<<30);
PI bigAns,smallAns;

inline void checkRemove(long pos){
    pos -= k;
    if(DQ.front().id<=pos) DQ.pop_front();
}

inline void addDQ(PI &p){
    while(!DQ.empty()){
        if(DQ.back().val < p.val) break;
        DQ.pop_back();
    }
    DQ.push_back(p);

    checkRemove(p.id);
}

void do_Sliding_Window(){
    //! k e dimensiunea
    //! aflam minimul
    long i;
    while(!DQ.empty()) DQ.pop_back();

    for(i=1;i<=how;i++){
        PI tmp = mp( def[i],i );
        addDQ( tmp );
        def[i] = DQ.front().val;
    }
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld %ld %ld %ld %ld",&m,&n,&c,&l,&cc,&ll); //! why?

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            scanf("%ld",&a[i][j]);
            sum[i][j] = a[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
        }
    }

    for(i=l;i<=n;i++)
        for(j=c;j<=m;j++)
            sB[i][j] = sum[i][j]-sum[i-l][j]-sum[i][j-c]+sum[i-l][j-c];

    for(i=ll;i<=n;i++)
        for(j=cc;j<=m;j++)
            sS[i][j] = sum[i][j]-sum[i-ll][j]-sum[i][j-cc]+sum[i-ll][j-cc];

    for(j=1;j<=m;j++){
        for(i=1;i<=n;i++) def[i]=sS[i][j];
        k = l-ll-1; how=n;
        do_Sliding_Window();
        for(i=1;i<=n;i++) cW[i][j] = def[i];
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++) def[j] = cW[i][j];
        k = c-cc-1; how=m;
        do_Sliding_Window();
        for(j=1;j<=m;j++) lW[i][j] = def[j];
    }

    for(i=l;i<=n;i++){
        for(j=c;j<=m;j++){
            long val = sB[i][j] - lW[i-1][j-1];
            if(val>ans){
                ans = val;
                bigAns = mp(i-l+1,j-c+1);
            }
        }
    }

    for(i=bigAns.first+ll;i<bigAns.first+l-1;i++){
        for(j=bigAns.second+cc;j<bigAns.second+c-1;j++){
            long val = sB[bigAns.first+l-1][bigAns.second+c-1] -
                       sS[i][j];
            if(val==ans){
                smallAns = mp(i-ll+1,j-cc+1);

                printf("%ld %ld\n%ld %ld",bigAns.second,bigAns.first,smallAns.second,smallAns.first);

                return 0;
            }
        }
    }

    return 0;
}
