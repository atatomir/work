#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

#define val first
#define cnt second.first
#define act second.second
#define mp make_pair
#define maxN 10111

typedef pair<long,pair<long,bool> > Switch;

long n,i,j,x,y,d;
vector<Switch> Line,Column;

long Field,best,Act;
bool Active[maxN];

bool cmp(const Switch& a,const Switch& b){
    if(a.val == b.val) return a.act < b.act;
    return a.val < b.val;
}

int main()
{
    freopen("drept3.in","r",stdin);
    freopen("drept3.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld %ld %ld",&x,&y,&d);
        Line.push_back(mp(x,mp(i,true)));
        Line.push_back(mp(x+d,mp(i,false)));
        Column.push_back(mp(y,mp(i,true)));
        Column.push_back(mp(y+d,mp(i,false)));
    }

    sort(Line.begin(),Line.end(),cmp);
    sort(Column.begin(),Column.end(),cmp);

    long lastX=0,lastY=0;
    for(i=0;i<Line.size();i++){
        long lX = Line[i].val - lastX;
        long lY = 0; Act = 0;
        if(lX){
            for(j=0;j<Column.size();j++){
                if(!Active[Column[j].cnt]) continue;
                if(Act) lY += Column[j].val - lastY;
                best = max(Act,best);
                if(Column[j].act) Act++; else Act--;

                lastY = Column[j].val;
            }
        }
        Field += lX*lY;
        Active[Line[i].cnt] = Line[i].act;
        lastX = Line[i].val;
    }

    printf("%ld\n%ld",Field,best);

    return 0;
}
