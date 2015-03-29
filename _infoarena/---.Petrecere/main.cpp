#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define maxN 1111
#define lim 1000

struct bNumber {
    long C[maxN];
    long pos;

    bNumber operator+(bNumber scd){
        bNumber Ans;

        Ans.pos = max(pos,scd.pos);
        for(long i=1;i<=Ans.pos+10;i++) Ans.C[i] = 0;

        for(long i=1;i<=Ans.pos;i++) {
            Ans.C[i] += C[i] + scd.C[i];
            Ans.C[i+1] += Ans.C[i] / lim;
            Ans.C[i] %= lim;
        }
        if(Ans.C[Ans.pos+1] != 0) Ans.pos++;

        return Ans;
    }

    bNumber operator*(bNumber scd){
        bNumber Ans;
        Ans.pos = pos + scd.pos-1;
        for(long i=1;i<=Ans.pos+10;i++) Ans.C[i] = 0;

        for(long i=1;i<=pos;i++)
            for(long j=1;j<=scd.pos;j++)
                Ans.C[i+j-1] += C[i]*scd.C[j];

        for(long i=1;i<Ans.pos;i++){
            Ans.C[i+1] += Ans.C[i] / lim;
            Ans.C[i] %= lim;
        }
        while(Ans.C[Ans.pos] >= lim){
            Ans.C[Ans.pos+1] += Ans.C[Ans.pos] / lim;
            Ans.C[Ans.pos++] %= lim;
        }

        return Ans;
    }

};


bNumber Get(long x){
    bNumber Ans;
    Ans.pos = 0;
    while(x){
        Ans.C[++Ans.pos] = x % lim;
        x /= lim;
    }

    return Ans;
}


long n,i;
deque<bNumber> Q;

int main()
{
    freopen("petrecere.in","r",stdin);
    freopen("petrecere.out","w",stdout);

    scanf("%ld",&n);
    if(n == 1){
        printf("1");
        return 0;
    }

    Q.push_back(Get(1));
    Q.push_back(Get(1));
    for(i=2;i<=n;i++){
        bNumber newBig;
        newBig = Q.back() + (Q.front()*Get(i-1));
        Q.pop_front();
        Q.push_back(newBig);
    }

    bNumber Ans = Q.back();
    //Ans = Get(1234) * Get(1234);

    i = Ans.pos;
    while(Ans.C[i] == 0) i--;
    printf("%ld",Ans.C[i--]);
    for(;i;i--){
        long x = Ans.C[i];
        printf("%ld%ld%ld",Ans.C[i]/100,(Ans.C[i]/10)%10,Ans.C[i]%10);
    }

    return 0;
}
