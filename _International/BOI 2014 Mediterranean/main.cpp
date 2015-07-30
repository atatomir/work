/*
 *  Source (BOI 2014) : http://codeforces.com/blog/entry/13397
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 500100
#define bg first
#define en second
#define leftSon (nod << 1)
#define rightSon ((nod << 1)|1)
#define pb push_back
#define Max 1000000001

#define cin fin
#define cout fout

long n,m,i;
vector< pair<long,long> > v;
vector<long> aint[maxN << 2];
pair<long,long> pr;
long start,stop,shift;
long nodL,nodR;

ifstream fin("mediterranean.in");
ofstream fout("mediterranean.out");

void BuildAInt(long nod,long L,long R){
    if(L == R){
        aint[nod].pb(v[L-1].en);
        return;
    }
    long M = (L+R) >> 1;
    BuildAInt(leftSon,L,M);
    BuildAInt(rightSon,M+1,R);

    long first = leftSon,posf=0;
    long second = rightSon,poss=0;
    long minim,mini;

    while((posf < aint[first].size())&&(poss < aint[second].size())){
        minim = aint[first][posf]; mini = 1;
        if(aint[second][poss] < minim) {
            minim = aint[second][poss]; mini = 2;
        }
        aint[nod].pb(minim);
        if(mini == 1)
            posf++;
        else
            poss++;
    }
    while(posf < aint[first].size()) {
        aint[nod].pb(aint[first][posf]);
        posf++;
    }
    while(poss < aint[second].size()) {
        aint[nod].pb(aint[second][poss]);
        poss++;
    }
}

int check(long nod,long lim){
    long i=0,j=aint[nod].size()-1,m;
    do{
        m = (i+j) >> 1;
        if(lim < aint[nod][m])
            j = m-1;
        else
            i = m+1;
    }   while(i <= j);
    return j+1;
}

long Query(long nod,long L,long R,long qL,long qR){
    long ans=0;
    if(qL <= L && R <= qR){
        ans += check(nod,stop);
        return ans;
    }
    long M = (L+R) >> 1;
    if (qL <= M) ans += Query(leftSon,L,M,qL,qR);
    if (qR >  M) ans += Query(rightSon,M+1,R,qL,qR);
    return ans;
}

long cbL(long x){
    long i=0,j=n-1,m;
    do{
        m = (i+j) >> 1;
        if(x <= v[m].bg)
            j = m-1;
        else
            i = m+1;
    }   while(i<=j);
    return i;
}

long cbR(long x){
    long i=0,j=n-1,m;
    do{
        m = (i+j) >> 1;
        if(x < v[m].bg)
            j = m-1;
        else
            i = m+1;
    }   while(i<=j);
    return j;
}

int main()
{
    cin >> n;
    for(i=1;i<=n;i++) {
        cin >> pr.bg >> pr.en;
        v.pb(pr);
    }
    sort(v.begin(),v.end());

    BuildAInt(1,1,n);

    cin >> m;
    for(i=1;i<=m;i++){
        cin >> start >> stop;
        start += shift; stop+= shift;

        nodL = cbL(start); nodL++;
        nodR = cbR(stop); nodR++;
        shift = Query(1,1,n,nodL,nodR);
        cout << shift << '\n';
    }

    return 0;
}
