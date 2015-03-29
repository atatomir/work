#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

typedef pair<long,long> Point;
typedef set<Point>::iterator myIter;

long n,i,x,y;
set<Point> S;

int main()
{
    freopen("sea2.in","r",stdin);
    freopen("sea2.out","w",stdout);

    scanf("%ld",&n);
    for(;n;n--){
        scanf("%ld %ld",&x,&y);
        Point p = make_pair(x,y);

        myIter it = S.upper_bound(p);
        if(it != S.end() && it->second > p.second){
            printf("-1\n");
            continue;
        }
        myIter itL = it;
        while(itL!=S.begin()){
            myIter back = itL; back--;
            if(back->second<p.second) itL--; else break;
        }
        S.erase(itL,it);
        S.insert(p);

        printf("%ld\n",S.size());
    }

    return 0;
}
