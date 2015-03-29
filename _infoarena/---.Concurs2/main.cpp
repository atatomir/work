#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define maxJ 55
#define cnt first
#define city second

typedef pair<long,long> myPair;

long n,i,jud,id,last;
vector<long> E[maxJ];
vector<long> sel;

struct compi{
    bool operator()(myPair& a,myPair& b){
        return a.cnt < b.cnt;
    }
};

priority_queue<myPair,vector<myPair> ,compi> Q;


bool cmp(long a,long b){
    return E[a].size() > E[b].size();
}
bool invcmp(long a,long b){
    return a>b;
}

inline void write(long a){
    long aa = E[a][E[a].size()-1]; E[a].pop_back();

    printf("%ld %ld\n",a,aa);
}


int main()
{
    freopen("concurs2.in","r",stdin);
    freopen("concurs2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld %ld",&jud,&id);
        E[jud].push_back(id);
    }

    for(i=1;i<=50;i++){
        if(!E[i].size()) continue;
        sel.push_back(i);
        Q.push(make_pair(E[i].size(),i));
        sort(E[i].begin(),E[i].end(),invcmp);
    }

    printf("%ld\n",sel.size());
    for(i=0;i<sel.size();i++) printf("%ld ",E[sel[i]].size()); printf("\n");
    sort(sel.begin(),sel.end(),cmp);

    while(!Q.empty()){
        pair<long,long> get,tmp;

        get = Q.top(); Q.pop();
        if(get.city == last && !Q.empty()){
            tmp = get;
            get = Q.top(); Q.pop();
            Q.push(tmp);
        }

        write(get.city); get.cnt--;
        if(get.cnt) Q.push(get);

        last = get.city;
    }


    return 0;
}
