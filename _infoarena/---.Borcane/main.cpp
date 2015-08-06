#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <assert.h>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 111

int n,i,A,B,C,D;
pair<int,int> v[maxN];

void move(int s1,int s2,int d){
    v[s1].first--; v[s2].first--;
    v[d].first+=2;

    assert(v[s1].first >= 0);
    assert(v[s2].first >= 0);

    printf("%d %d %d\n",v[s1].second,v[s2].second,v[d].second);
}

int main()
{
    freopen("borcane.in","r",stdin);
    freopen("borcane.out","w",stdout);

    scanf("%d",&n);
    fordef(i,1,n) {
        scanf("%d",&v[i].first);
        v[i].second = i;
    }
    sort(v+1,v+n+1);

    fordef(i,1,n-2)
        while(v[i].first) move(i,i+1,n);

    if(v[n-1].first==0) return 0;
    A = n-1; B = n; C = 1; D = 2;

    if(v[A].first%3==1){
        move(A,B,C);
        move(B,C,D);
        move(B,C,A);

        move(A,D,B);
        move(A,D,B);
    } else
    if(v[A].first%3==2){
        move(A,B,C);
        move(A,B,D);

        move(C,D,B);
        move(C,D,B);
    }

    int cnt = v[A].first/3;
    fordef(i,1,cnt) move(A,B,C);
    fordef(i,1,2*cnt) move(A,C,B);

    //! checker
    fordef(i,1,n-1){
        if(v[i].first != 0) cerr << "Error " << v[i].first<< '\n';
    }

    return 0;
}
