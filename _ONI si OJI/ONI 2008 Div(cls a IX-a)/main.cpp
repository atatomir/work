#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define maxM 30005
#define maxN 5005

#define right rright

long n,i,lim,rest;
char m[maxN];
vector<long> dp[maxM];
vector<long> act;

long put = 0,right=0,need,j,pos;
long ansi=10000,ansj=1000000000;

long cb(long s,long x){
    long i=0,j=dp[s].size()-1,m;
    while(i<=j){
        m = (i+j)/2;
        if(x <= dp[s][m])
            j = m-1;
        else
            i = m+1;
    }
    if(j == dp[s].size()) return 100000;
    return dp[s][j];
}

void verif(long l,long h) {
    if(l > h) return;

    if(l == 1 && h!= lim && m[h+1] == '0'){
        while(m[h+1] == '0' && h != lim) h++;

        long val = 0;
        for(long i=1;i<l;i++) val = (val * 10 + m[i]-'0')%n;
        for(long i=h+1;i<=lim;i++) val = (val * 10 + m[i]-'0')%n;


        if(h == lim) h--,val=0;
        if(val) return;
    }


    if(ansj-ansi > h-l) {
        ansi = l; ansj = h;
        return;
    } else
    if(ansj-ansi == h-l){
        long pos1,pos2;
        for(long i=1;i<=lim-(h-l+1);i++){
            pos1 = i; pos2 = i;
            if(pos1 >= l) pos1 += h-l+1;
            if(pos2 >= ansi) pos2 += h-l+1;

            if(m[pos1] > m[pos2]){
                ansi = l; ansj = h;
                return;
            }
             else
             if(m[pos1] < m[pos2]){
                return;}
        }

        if(l < ansi) {
            ansi = l; ansj = h;
        }
    }
}

int main()
{
    freopen("div.in","r",stdin);
    freopen("div.out","w",stdout);

    scanf("%ld\n%s",&n,m+1);
    lim = strlen(m+1);

    rest = 0;
    act.push_back(0); dp[0].push_back(0);
    for(i=1;i<=lim;i++){
        rest = rest* 10 + m[i] - '0';
        rest %= n;

        if(dp[rest].empty()) act.push_back(rest);
        dp[rest].push_back(i);
    }

    for(i=lim+1;i;i--){
        right = (right + put*(m[i]-'0'))%n;
        put = (put*10)%n;
        if(i == lim+1) put = 1;

        need = n - right;
        if(need == n) need = 0;

        for(j=0;j<act.size();j++){
            rest = act[j];
            if((rest*put)%n != need) continue;

            pos = cb(rest,i); pos++;

            verif(pos,i-1);
        }

    }

    if(ansj == 1000000000) ansi=ansj=0;
    printf("%ld %ld",ansi,ansj);

    return 0;
}
