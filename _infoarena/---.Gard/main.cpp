#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 16011
#define maxK 111


class SlidingWindow {
    public:
        void init() {
            while(!data.empty()) data.pop_back();
        }

        void operator << ( pair<int,int> who ) {
            while (!data.empty()) {
                auto last = data.back();
                if (last.second > who.second) break;
                data.pop_back();
            }

            data.push_back( who );
        }

        void RemoveTo(int lim) {
            while (!data.empty()) {
                auto act = data.front();
                if ( act.first > lim) break;
                data.pop_front();
            }
        }

        int getBest() {
            if ( data.empty() ) return -1;
            return data.front().second;
        }

    private:
        deque< pair<int,int> > data; //! pos,val
};

struct Human {
    int lung; //! numar maxim de scanduri vopsite
    int pay;  //! tariful per scandura
    int stay; //! Scandura obligatorie

    bool operator<( const Human& who ) const {
        return stay < who.stay;
    }
    void read(){
        scanf("%d%d%d",&lung,&pay,&stay);
    }
};

int n,k,i;
Human H[maxK];
int dp[maxN];
int aux[maxN];
SlidingWindow SD;

void addHuman( const Human& who ) {
    int i;
    int lim = min(who.stay + who.lung,n+1);

    SD.init();
    for (i = n; i >= 0; i--) aux[i] = dp[i] + who.pay*(n-i+1);

    for (i = max( who.stay - who.lung , 0 ); i < who.stay; i++) SD << mp(i,aux[i]);
    for (i = who.stay; i < lim; i++) {
        int act = SD.getBest() - who.pay*(n-i+1);
        dp[i] = max( dp[i] , act );

        SD.RemoveTo(i - who.lung);
    }
    for (i = who.stay + who.lung; i <= n; i++) dp[i] = max(dp[i],dp[i-1]);
}

int main()
{
    freopen("gard.in","r",stdin);
    freopen("gard.out","w",stdout);

    scanf("%d%d",&n,&k);
    for (i = 1; i <= k; i++) H[i].read();
    sort(H+1,H+k+1);

    for (i = 1; i <= k; i++)
        addHuman( H[i] );
    printf("%d",dp[n]);

    return 0;
}
