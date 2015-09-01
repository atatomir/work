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

#define maxN 60011
#define maxL 1000011

class SlidingWindow {
    public:
        void init() {
            while (!data.empty()) data.pop_back();
        }

        void add(int pos,int val) {
            while (!data.empty()) {
                auto last = data.back();
                if (last.second < val) break;
                data.pop_back();
            }

            data.push_back(mp(pos, val));
        }

        void removeTo(int limit) {
            while (!data.empty()) {
                auto old = data.front();
                if (old.first > limit) break;
                data.pop_front();
            }
        }

        int getBest() {
            return data.front().second;
        }
    private:
        deque< pair<int,int> > data;
        //! pos,val
};

int n,i,L;
int v[maxL];
pair<int,int> Intr[maxN];
int aux[maxN];
vector< pair<int,int> > useful;
SlidingWindow SD;

int pos;
int bonus;

bool cmp(const pair<int,int> &a,const pair<int,int> &b) {
    return a.second < b.second;
}

int main()
{
    freopen("cover.in","r",stdin);
    freopen("cover.out","w",stdout);

    scanf("%d%d",&n,&L);
    for (i = 1; i <= L; i++) scanf("%d",&v[i]);
    for (i = 1; i <= n; i++) scanf("%d%d",&Intr[i].first,&Intr[i].second);

    sort(Intr+1,Intr+n+1);
    aux[n+1] = L+3;
    aux[n] = Intr[n].second;
    for (i = n-1; i > 0; i--) aux[i] = min(aux[i+1], Intr[i].second);
    for (i = 1; i <= n; i++) {
        if (Intr[i].second < aux[i+1]) useful.pb(Intr[i]);
    }

    sort(useful.begin(),useful.end(),cmp);
    SD.init();

    pos = 0;
    for (auto elem:useful) {
        while (pos+1 <= elem.second) {
            pos++;
            SD.add(pos,v[pos]+bonus);
        }
        SD.removeTo(elem.first-1);

        bonus = SD.getBest();
    }

    printf("%d",bonus);

    return 0;
}
