#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 100010
#define time first
#define pen second

struct cmp{
    bool operator()(long& a,long& b){
        return a < b;
    }
};

long n,i,j,x,y,timp,ini;
vector<pair<long,long> > task;

priority_queue<long,vector<long>,cmp> H;

long long penalty;

int main()
{
    freopen("procesor.in","r",stdin);
    freopen("procesor.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld %ld",&x,&y);
        task.push_back(make_pair(x,y));
        penalty = penalty + y;
    }
    sort(task.begin(),task.end());

    i = task.size()-1;
    ini = task[i].time;

    for(timp = ini;timp>=0;timp--){
        if(i >= 0)
        while(timp < task[i].time){
            H.push(task[i--].pen);
            if(i < 0) break;
        }

        if(H.empty()) continue;
        x = H.top(); H.pop();
        penalty = penalty -  x;
    }

    printf("%lld",penalty);

    return 0;
}
