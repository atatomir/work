#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define maxVal 10111
#define maxBuf 1000000
#define INF 1000000000000000

char Buff[maxBuf];
long pos;

long n,i;
queue<long long> iQ,Q;
long long Ans,x;
long ap[maxVal];

inline bool isDigit(char c){
    return c >= '0' && c <= '9';
}
long getLong(){
    while(!isDigit(Buff[pos])){
        pos++;
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    long ans = 0;
    while(isDigit(Buff[pos])){
        ans = ans*10 + Buff[pos++] - '0';
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    return ans;
}

int main()
{
    freopen("k1.in","r",stdin);
    freopen("k1.out","w",stdout);

    n = getLong();
    for(i=1;i<=n;i++) ap[getLong()]++;

    for(i=0;i<maxVal;i++){
        for(;ap[i];ap[i]--) iQ.push(i);
    }

    while(n > 1){
        long long nod[2];
        bool second;

        for(i=0;i<2;i++){
            second = false;
            if(!iQ.empty()) nod[i] = iQ.front(); else nod[i]=INF;
            if(!Q.empty())
                if(Q.front() < nod[i]){
                    nod[i] = Q.front();
                    second = true;
                }

            if(!second) iQ.pop(); else Q.pop();
        }

        long long newNod = nod[0] + nod[1];
        Ans += newNod;
        Q.push(newNod); n--;
    }

    printf("%lld",Ans);

    return 0;
}
