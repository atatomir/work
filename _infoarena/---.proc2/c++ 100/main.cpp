#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

typedef pair<long,long> task;
#define s first
#define d second
#define id first
#define stop second

#define maxM 100005

struct compare{
    bool operator()(const task& a,const task& b){
        return a.stop > b.stop;
    }
};
struct newComp{
    bool operator()(const long& a,const long& b){
        return a > b;
    }
};

bool cmp(const task& a,const task& b){
    return a.s < b.s;
}

long n,m,i,idd;
task a[maxM],elem;
priority_queue<task,vector<task>,compare> busy;
priority_queue<long,vector<long>,newComp> ready;


int main()
{
    freopen("proc2.in","r",stdin);
    freopen("proc2.out","w",stdout);

    scanf("%ld %ld\n",&n,&m);
    n = min(n,m);

    for(i=1;i<=m;i++){
        scanf("%ld %ld\n",&a[i].s,&a[i].d);
    }
    sort(a+1,a+m+1);

    for(i=1;i<=n;i++) ready.push(i);

    for(i=1;i<=m;i++){
        while(!busy.empty()){
            elem = busy.top();
            if(elem.stop > a[i].s) break;
            busy.pop();
            ready.push(elem.id);
        }
        idd = ready.top(); ready.pop();
        busy.push(make_pair(idd,a[i].s + a[i].d));
        printf("%ld\n",idd);
    }

    return 0;
}
