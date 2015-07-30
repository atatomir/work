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

#define maxS 5005
#define maxN 105
#define maxM 200011
#define maxLet 26

int n,m,i;
char s[maxN][maxS];
short dim[maxN];
short wh[maxN][maxS][maxLet];

char ch;
short cnt[maxN];
short st[maxN][maxS];
int let[maxN],ans;

void pre(int id){
    int i,j;
    dim[id] = strlen(s[id]+1);

    for(i=dim[id]-1;i>=0;i--){
        fordef(j,0,maxLet-1) wh[id][i][j] = wh[id][i+1][j];
        wh[id][i][ s[id][i+1]-'a' ] = i+1;
    }
}

int main()
{
    freopen("search.in","r",stdin);
    freopen("search.out","w",stdout);

    scanf("%d%d\n",&n,&m);
    fordef(i,1,n){
        scanf("%s\n",s[i]+1);
        pre(i);
    }

    fordef(i,1,n) st[i][ ++cnt[i] ] = 0;
    ans = n;

    for(;m--;){
        scanf("%c\n",&ch);
        if(ch=='-'){
            fordef(i,1,n){
                if(let[i]){
                    if(--let[i] == 0) ans++;
                    continue;
                }
                cnt[i]--;
            }
        } else {
            fordef(i,1,n){
                if(let[i]){
                    let[i]++;
                    continue;
                }

                int go = wh[i][ st[i][cnt[i]] ][ch-'a'];
                if(go==0){
                    ans--;
                    let[i]++;
                    continue;
                }
                st[i][ ++cnt[i] ] = go;
            }
        }

        printf("%d\n",ans);
    }

    return 0;
}
