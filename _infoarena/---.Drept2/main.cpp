#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 2000111

class SlidingWidow{
    public:
        void init(int _lim){
            data.clear();
            lim = _lim;
        }
        void add(int pos,int val){
            while (!data.empty()){
                auto act = data.back();
                if (act.second < val) break;
                data.pop_back();
            }
            data.push_back( mp(pos,val) );
            if (data.front().first <= pos-lim) data.pop_front();
        }
        int getBest(){
            if (data.empty()) return -1;
            return data.front().second;
        }

    private:
        deque< pair<int,int> > data;
        int lim;
};

int n,m,i,A,B;
int left_[maxN],right_[maxN];
long long ans;
SlidingWidow Sliding_left;
SlidingWidow Sliding_right;

void solve(int A,int B){
    Sliding_left.init(A); //! cauta maximul (add -)
    Sliding_right.init(A); //! cauta minimul (add +)

    for (int i=1;i<=n;i++){
        Sliding_left.add(i,-left_[i]);
        Sliding_right.add(i,right_[i]);

        if (i<A) continue;
        int act_left = -Sliding_left.getBest();
        int act_right =  Sliding_right.getBest();

        //cerr << act_left << ' ' << act_right << '-' << ans <<'\n';

        if(act_right-act_left+1 < B) continue;
        ans += 1LL*(act_right-act_left+1 - B + 1);
    }
}

int main()
{
    freopen("drept2.in","r",stdin);
    freopen("drept2.out","w",stdout);

    scanf("%d%d%d%d",&m,&n,&A,&B);
    for (i=1;i<=n;i++) {
        scanf("%d%d",&left_[i],&right_[i]);
        right_[i] += right_[i-1];
    }
    for (i=1;i<=n;i++) right_[i] += left_[i]-1;

    solve(A,B);
    if (A!=B) solve(B,A);

    printf("%lld\n",ans);

    return 0;
}
