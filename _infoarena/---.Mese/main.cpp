#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 100111
#define itt vector<long>::iterator

long n,s,i,dad,age,rez;
vector<long> list[maxN];

short act[maxN];


void dfs(long node){
    vector<long> tmp;
    tmp.clear();
    for(itt it=list[node].begin();it!=list[node].end();it++) {
        dfs(*it);
        tmp.push_back(act[*it]);
    }

    if(list[node].empty()){
        rez++;
        return;
    }

    sort(tmp.begin(),tmp.end());
    for(i=0;i<tmp.size();i++){
        if(act[node]+tmp[i]>s) break;
        act[node] += tmp[i];
    }

    rez += 1-i;
}

int main()
{
    freopen("mese.in","r",stdin);
    freopen("mese.out","w",stdout);

    scanf("%ld %ld",&n,&s);
    for(i=1;i<=n;i++){
        scanf("%ld %ld",&dad,&age);
        list[dad].push_back(i);
        act[i] = age;
    }

    dfs(0);
    printf("%ld",rez);

    return 0;
}
