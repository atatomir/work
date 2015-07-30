#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 805
#define x1 xx1
#define x2 xx2
#define y1 yy1
#define y2 yy2

long n,m,u,q,i,j,bit,cnt;
long smen[maxN][maxN]; //! atentie
long def['Z'+15];
char c;

long x1,x2,y1,y2;
long idL[1024],idC[1024]; //! atentie

vector<long> line,column;

long cBit(long x,long y){
    long v = smen[x][y];
    long ans=0;
    while(v){
        ans++;
        v = v&(v-1);
    }
    return ans;
}

/*long cbLine(long xx){
    long i=0,j=line.size()-1,m;
    while(i<=j){
        m = (i+j)>>1;
        if(xx < line[m])
            j = m-1;
        else
            i = m+1;
    }
    return j+1;
}
long cbColumn(long xx){
    long i=0,j=column.size()-1,m;
    while(i<=j){
        m = (i+j)>>1;
        if(xx < column[m])
            j = m-1;
        else
            i = m+1;
    }
    return j+1;
}
*/

int main()
{
    freopen("rox.in","r",stdin);
    freopen("rox.out","w",stdout);

    bit=1;
    for(c='A';c<='Z';c++){
        def[c]=bit;
        bit<<=1;
    }

    scanf("%ld%ld%ld\n",&n,&m,&u);
    for(i=1;i<=u;i++){
        scanf("%ld %ld %ld %ld %c\n",&x1,&y1,&x2,&y2,&c);
        line.push_back(x1); line.push_back(x2+1);
        column.push_back(y1); column.push_back(y2+1);
    } freopen("rox.in","r",stdin);

    //!! normalizare

    sort(line.begin(),line.end());
    cnt = 1;
    for(i=1;i<line.size();i++){
        if(line[i]!=line[i-1]){
            line[cnt++] = line[i];
        }
    } line.resize(cnt);
    for(i=0;i<line.size();i++) idL[line[i]]=i+1;

    sort(column.begin(),column.end());
    cnt=1;
    for(i=1;i<column.size();i++){
        if(column[i]!=column[i-1]){
            column[cnt++] = column[i];
        }
    } column.resize(cnt);
    for(i=0;i<column.size();i++) idC[column[i]]=i+1;

    for(i=1;i<=n;i++)
        if(idL[i]==0) idL[i] = idL[i-1];
    for(i=1;i<=m;i++)
        if(idC[i]==0) idC[i] = idC[i-1];

    //!! sf normalizare

    scanf("%ld%ld%ld\n",&n,&m,&u);
    for(i=1;i<=u;i++){
        scanf("%ld %ld %ld %ld %c\n",&x1,&y1,&x2,&y2,&c);
        bit = def[c];

        x1 = idL[x1]; x2 = idL[x2+1];
        y1 = idC[y1]; y2 = idC[y2+1];

        smen[x1][y1] ^= bit;
        smen[x2][y1] ^= bit;
        smen[x1][y2] ^= bit;
        smen[x2][y2] ^= bit;
    }

    for(i=1;i<=line.size();i++){
        for(j=1;j<=column.size();j++){
            smen[i][j] ^= smen[i-1][j]^smen[i][j-1]^smen[i-1][j-1];
        }
    }

    scanf("%ld",&q);
    for(i=1;i<=q;i++){
        scanf("%ld %ld",&x1,&y1);
        x1 = idL[x1]; y1 = idC[y1];
        printf("%ld\n",cBit(x1,y1));
    }

    return 0;
}
