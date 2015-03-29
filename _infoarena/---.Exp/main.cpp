#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#define maxNum 30000

typedef pair<long,long> mPair;

long d,n,i,cnt,x;
bool ciur[maxNum+11];
mPair P[3500]; // 3245

void cCiur(){
    for(long i=2;i*i<=maxNum;i++){
        if(ciur[i]) continue;
        for(long j=i*i;j<=maxNum;j+=i)
            ciur[j]=1;
    }

    for(long i=2;i<=maxNum;i++){
        if(ciur[i]) continue;
        P[++cnt] = make_pair(i,0);
    }
}

long cb(long x){
    long i=1,j=cnt,m;
    while(i<=j){
        m = (i+j)>>1;
        if(x <= P[m].first)
            j = m-1;
        else
            i = m+1;
    }
    return i;
}

int main()
{
    freopen("exp.in","r",stdin);
    freopen("exp.out","w",stdout);

    scanf("%ld%ld",&d,&n);
    cCiur();

    for(i=1;i<=n;i++){
        scanf("%ld",&x);
        long j = 1;
        while(x>=P[j].first*P[j].first){
            /*while(x % P[j].first == 0){
                x /= P[j].first;
                P[j].second++;
            }*/
            if(x % P[j].first) {j++;continue;}
            long pow=1,val=P[j].first;
            while(x%(val*val)==0 ) {val*=val;pow<<=1;}
            while(pow){
                if(x%val==0){
                    x /= val; P[j].second += pow;
                }
                pow>>=1; val = sqrt(val);
            }

            j++;
        }
        if(x!=1){
            P[cb(x)].second++;
        }
    }

    for(i=1;i<=cnt;i++){
        if(P[i].second % d){
            printf("0");
            return 0;
        }
        P[i].second /= d;
    }
    printf("1\n");
    for(i=1;i<=cnt;i++)
        if(P[i].second) printf("%ld %ld\n",P[i].first,P[i].second);


    return 0;
}
