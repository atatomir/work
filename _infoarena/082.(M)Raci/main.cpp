#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

#define pos first
#define val second
#define mp make_pair

long n,i,k,lung,v1,v2,val;
deque<pair<long,long> > Q[26];
char s[30],c1,c2;
long maxim = -1;

long getMax(long sour){
    while(!Q[sour].empty()){
        if(Q[sour].front().pos >= i-k) break;
        Q[sour].pop_front();
    }
    if(Q[sour].empty()) return 0;
    return Q[sour].front().val;
}

void putMax(long sour,long val){
    while(!Q[sour].empty()){
        if(Q[sour].front().val > val) break;
        Q[sour].pop_back();
    }
    Q[sour].push_back(mp(i,val));
    while(Q[sour].front().pos < i-k) Q[sour].pop_front();
}

int main()
{
    freopen("raci.in","r",stdin);
    freopen("raci.out","w",stdout);

    scanf("%ld %ld\n",&n,&k);
    for(i=1;i<=n;i++){
        scanf("%s",s);
        lung = strlen(s);
        c1 = s[0]; c2 = s[lung-1];
        v1 = c1 - 'a' ; v2 = c2 - 'a';

        val = getMax(v1) + 1;
        putMax(v2,val);
        maxim = max(val,maxim);
    }

    printf("%ld",maxim);

    return 0;
}
