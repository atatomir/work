#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<long,pair<long,long> > Cell;

#define par first
#define xx second.first
#define yy second.second
#define mp make_pair
#define maxN 50

#define long long long

long n,m,i,x,y,lim;
Cell C[maxN*maxN];
vector<long> list[maxN][maxN];
long Ans[maxN][maxN];

long pos;
char s[300];

queue<long> Q;

bool isDigit(char c){
    return c >= '0' && c <= '9';
}
long getLong(){
    while(!isDigit(s[pos])) pos++;
    long Ans=0;
    while(isDigit(s[pos])) Ans = Ans*10 + s[pos++] - '0';
    return Ans;
}

void Recurs(long nod){
    for(long i=0;i<list[C[nod].xx][C[nod].yy].size();i++){
        long newNod = list[C[nod].xx][C[nod].yy][i];
        C[newNod].par--;
        Ans[C[newNod].xx][C[newNod].yy] += Ans[C[nod].xx][C[nod].yy];
        if(!C[newNod].par) Recurs(newNod);
    }
}

int main()
{
    freopen("mxl.in","r",stdin);
    freopen("mxl.out","w",stdout);

    scanf("%lld%lld\n",&n,&m);
    for(i=1;i<=m;i++){
        gets(s); pos = 0; lim = strlen(s);
        x = getLong(); y = getLong();
        C[i] = mp(0,mp(x,y));

        while(pos < lim){
            long val = getLong();
            if(s[pos] == ':'){
                long val2 = getLong();
                C[i].par++;
                list[val][val2].push_back(i);
            } else {
                Ans[x][y] += val;
            }
        }
    }

    for(i=1;i<=m;i++)
        if(!C[i].par) Q.push(i);

    while(!Q.empty()){
        long nod = Q.front(); Q.pop();
        Recurs(nod);
    }

    for(i=1;i<=n;i++){
        for(long j=1;j<=n;j++) printf("%lld ",Ans[i][j]);
        printf("\n");
    }

    return 0;
}
