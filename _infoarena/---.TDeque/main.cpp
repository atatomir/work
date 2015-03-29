#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

#define maxN 1011
#define x v[i]
#define cont (tmp.front() < tmp.back())
#define cont2 (tmp2.front() < tmp2.back())

long n,i,v[maxN];
deque<long> act,tmp,tmp2;
vector<char> Ans;

long getLeft(){
    tmp = act; long ans = 0;
    while((!(x>tmp.back() && x<tmp.front())) &&
          (!(x<tmp.back() && x<tmp.front() && cont)) &&
          (!(x>tmp.back() && x>tmp.front() && cont))){
        ans++;
        long t = tmp.back(); tmp.pop_back();
        tmp.push_front(t);
    }
    return ans;
}

long getRight(){
    tmp2 = act; long ans = 0;
    while((!(x>tmp2.back() && x<tmp2.front())) &&
          (!(x<tmp2.back() && x<tmp2.front() && cont2)) &&
          (!(x>tmp2.back() && x>tmp2.front() && cont2))){
        ans++;
        long t = tmp2.front(); tmp2.pop_front();
        tmp2.push_back(t);
    }
    return ans;
}


int main()
{
    freopen("tdeque.in","r",stdin);
    freopen("tdeque.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld",&v[i]);
    v[n+1] = 0;

    act.push_back(v[1]); Ans.push_back('1');
    act.push_back(v[2]); Ans.push_back('1');

    for(i=3;i<=n+1;i++){
        long val1 = getLeft();
        long val2 = getRight();

        if(val1 < val2){
            act = tmp; act.push_back(x);
            for(long j=1;j<=val1;j++) Ans.push_back('2');
            Ans.push_back('1');
        } else {
            act = tmp2; act.push_back(x);
            for(long j=1;j<=val2;j++) Ans.push_back('3');
            Ans.push_back('1');
        }
    }



    printf("%ld\n",Ans.size()-1);
    for(i=0;i<Ans.size()-1;i++) printf("%c",Ans[i]);

    return 0;
}
