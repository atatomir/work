#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define lung first
#define sour second
#define maxK 111
#define mp make_pair
#define value first
#define n1 second.first
#define n2 second.second
#define act P[col]
#define INF 1000000000

typedef pair<long,long> Point;
typedef pair<long,pair<long,long> > Line;

long n,d,i;
vector<Point> P[maxK];
Line Ans[maxK];
bool Sorted[maxK];
double Answer;

long pos,col;

inline long abss(long x){
    if(x < 0) return -x;
    return x;
}
void Verify(long s,long x,long col){
    long i=0,j=act.size()-1,m;
    while(i<=j){
        m = (i+j)/2;
        if(x <= act[m].lung)
            j = m-1;
        else
            i = m+1;
    }

    if(i < act.size()){
        long newAns = abss(x-act[i].lung);
        if(newAns < Ans[col].value || (newAns == Ans[col].value && act[i].sour < Ans[col].n1)){
            Ans[col].value = newAns;
            Ans[col].n1 = act[i].sour;
            Ans[col].n2 = s;
        }
    }
    if(j >= 0){
        long newAns = abss(x-act[j].lung);
        if(newAns < Ans[col].value || (newAns == Ans[col].value && act[j].sour < Ans[col].n1)){
            Ans[col].value = newAns;
            Ans[col].n1 = act[j].sour;
            Ans[col].n2 = s;
        }
    }
}

double sqr(double x){
    return x*x;
}

int main()
{
    freopen("stalpi3.in","r",stdin);
    freopen("stalpi3.out","w",stdout);

    scanf("%ld %ld",&n,&d);
    for(i=1;i<maxK;i++) Ans[i].value = INF;

    for(i=1;i<=n;i++){
        scanf("%ld %ld",&pos,&col);
        P[col].push_back(mp(pos,i));
    }

    for(i=1;i<=n;i++){
        scanf("%ld %ld",&pos,&col);
        if(!Sorted[col]){
            Sorted[col] = true;
            if(P[col].size() > 1)sort(P[col].begin(),P[col].end());
        }

        Verify(i,pos,col);
    }

    Answer = 0;
    for(i=1;i<maxK;i++){
        if(Ans[i].value == INF) continue;
        Answer += sqrt(sqr(double(d)) + sqr(double(Ans[i].value)));
    }

    printf("%.3lf\n",Answer);
    for(i=1;i<maxK;i++){
        if(Ans[i].value == INF) continue;
        printf("%ld %ld\n",Ans[i].n1,Ans[i].n2);
    }

    return 0;
}
