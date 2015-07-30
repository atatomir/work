#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back

#define maxN 112
#define maxLet 27

int n,m,q,i;
char ch,s[maxN];
bool Tr[maxLet][maxLet];
bool Div[maxLet][maxLet][maxLet];
vector< pair<char,char> > wh[maxLet];

short dp[maxN][maxN][maxLet];

bool compute(int l,int r,char _ch){
    int ch = _ch-'A',i;
    if(l==r) return (Tr[ch][s[l]-'a']);
    if(dp[l][r][ch] == 1) return true;
    if(dp[l][r][ch] == -1) return false;

    //! we need to compute the dp for l,r,ch
    foreach(wh[ch]){
        char c1 = it->first;
        char c2 = it->second;

        fordef(i,l,r-1){
            if(compute(l,i,c1)&&compute(i+1,r,c2)){
                dp[l][r][ch]=1;
                return true;
            }
        }
    }

    dp[l][r][ch] = -1;
    return false;
}

int main()
{
    freopen("minerale.in","r",stdin);
    freopen("minerale.out","w",stdout);

    scanf("%d%d\n",&m,&q);
    fordef(i,1,m){
        scanf("%c %s\n",&ch,s+1);

        if(s[2]=='\0'){ //! -> stabil
            Tr[ ch-'A' ][ s[1]-'a' ] = true;
        } else { //! -> instabil
            Div[ ch-'A' ][ s[1]-'A' ][ s[2]-'A' ] = true;
            wh[ ch-'A' ].pb(mp(s[1],s[2]));
        }
    }

    for(;q--;){
        memset(s,0,sizeof(s));
        scanf("%s\n",s+1); n = strlen(s+1);
        memset(dp,0,sizeof(dp));

        if( compute(1,n,'S') ) printf("1\n"); else {
            bool found = false;
            fordef(ch,'A','Z'){
                if(compute(1,n,ch)) {
                    found = true;
                    break;
                }
            }
            if(found) printf("2\n");
            else      printf("0\n");
        }
    }


    return 0;
}
