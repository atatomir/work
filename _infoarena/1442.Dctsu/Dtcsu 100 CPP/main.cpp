#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define V 276997
#define mod 7013
#define maxBuf 10000

long long Q,i;
vector<long long> H[mod];

char Buff[maxBuf];
long pos,Ans;
long long x;

inline bool isDigit(char c){
    return c >= '0' && c <= '9';
}
long long getLong(){
    while(!isDigit(Buff[pos])){
        pos++;
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    long long Ans=0;
    while(isDigit(Buff[pos])){
        Ans = Ans*1LL*10 + (long long)Buff[pos++] - (long long)'0';
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    return Ans;
}

bool isGood(long sour,long long x){
    for(long i=0;i<H[sour].size();i++)
        if(H[sour][i] == x) return true;
    return false;
}

int main()
{
    freopen("dtcsu.in","r",stdin);
    freopen("dtcsu.out","w",stdout);
    fread(Buff,1,maxBuf,stdin);

    for(i=1;i<=V;i++){
        x = getLong();
        if(x&1) H[x%mod].push_back(x);
    }

    Q = getLong();
    for(;Q;Q--){
        x = getLong();
        if(x) x /= (x^(x-1))&x;
        if(isGood(x%mod,x)) Ans++;
    }

    printf("%ld\n",Ans);

    return 0;
}
