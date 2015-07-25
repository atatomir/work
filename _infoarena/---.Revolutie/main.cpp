#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 130

#ifndef INFOARENA
    #define DEBUG
#endif // INFOARENA

int n,i,j,x;
vector<int> list[maxN];
int l[maxN],r[maxN];
bool us[maxN];

int wh[maxN],pos[maxN];
int a[maxN][maxN];

vector< pa( char,pa(int,int) ) > ans;

bool pairUp(int node){
    if(us[node]) return false;
    us[node] = true;

    foreach(list[node]){
        if(!r[*it]){
            l[node] = *it;
            r[*it] = node;
            return true;
        }
    }

    foreach(list[node]){
        if(pairUp( r[*it] )){
            l[node] = *it;
            r[*it] = node;
            return true;
        }
    }
    return false;
}

int main()
{
    freopen("revolutie.in","r",stdin);
    freopen("revolutie.out","w",stdout);

    srand(time(NULL));

    scanf("%d",&n);
    fordef(i,1,n){
        fordef(j,1,n){
            scanf("%d",&x); a[i][j] = x;
            if(x==1) list[ i ].pb( j );
        }
    }

    //! some debug
    #ifdef DEBUG
        fordef(i,1,n) list[i].clear();
        fordef(i,1,n){
            fordef(j,1,n){
                x = rand()%2; a[i][j] = x;
                if(x==1) list[ i ].pb( j );
            }
    }
    #endif // DEBUG

    bool found=true;
    while(found){
        found = false;
        memset(us,0,sizeof(us));
        fordef(i,1,n)
            if(!l[i]) found |= pairUp(i);
    }

    fordef(i,1,n){
        if(!l[i]){
            printf("-1");
            return 0;
        }

        //! unde se afla linia ce va fi plasata a i-a
        wh[ l[i] ] = i;
        //! ce coloana este ocupata pe linia i
        pos[i] = l[i];
    }

    fordef(i,1,n){
        if(wh[i] == i) continue;

        ans.pb( mp('L',mp(i,wh[i])) );

        int ppos = pos[i];
        pos[ wh[i] ] = pos[i]; pos[i] = i;
        wh[ ppos ] = wh[i];  wh[i] = i;
    }

    printf("%d\n",ans.size());
    foreach(ans) printf("%c %d %d\n",it->first,it->second.first,it->second.second);

    //! check the result
    #ifdef DEBUG
        foreach(ans)
            fordef(i,1,n) swap( a[it->second.first][i] , a[it->second.second][i] );
        fordef(i,1,n){
            if(a[i][i]==0){
                cerr << "Error on line : " << i ;
                return 0;
            }
        }
        cerr << "Good!";
    #endif


    return 0;
}
