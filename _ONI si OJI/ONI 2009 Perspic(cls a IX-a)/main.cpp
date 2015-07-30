#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 111
#define maxDiv 1300
#define maxCiur 10000
#define mod 13007
#define long int


long n,m,i,j,t,cont,temp;
long a[maxN][maxN];
long C[maxN],L[maxN];
char ch[10];
long corr[maxN*maxN];
long x,y,x2,y2;

long divs[maxDiv];
long aPow[maxDiv];
bool Erath[maxCiur];

long ans;

inline long getX(long pos){
    return (pos+n-1)/n;
}
inline long getY(long pos){
    pos = pos % n;
    if(!pos) pos = n;
    return pos;
}

void Ciur(){
    Erath[1] = true; cont=0;
    for(long i=2;i<=maxCiur;i++){
        if(Erath[i] == false){
            divs[++cont] = i;
            for(long j = i*i;j<=maxCiur;j = j + i) Erath[j] = true;
        }
    }
}

long ciclu(long nod){
    if(corr[nod] != -1) {
        temp = corr[nod];
        corr[nod] = -1;
        return ciclu(temp)+1;
    }
    return 0;
}

long myPow(long a,long b){
    long ans = 1;
    while(b){
        if(b&1) ans = (ans * a) % mod;
        a = (a*a)% mod;
        b >>= 1;
    }
    return ans;
}

int main()
{
    freopen("perspic.in","r",stdin);
    freopen("perspic.out","w",stdout);

    scanf("%d%d", &n, &m);
    for(i=1;i<=n*n;i++){
        a[getX(i)][getY(i)] = i;
    }
    for(i=1;i<=n;i++) L[i]=C[i]=i;

    for(i=1;i<=m;i++){
        scanf("%s%d%d", ch, &x, &y);
        if(ch[0] == 'C'){
            t = C[x]; C[x] = C[y]; C[y] = t;
        } else
        if(ch[0] == 'R'){
            t = L[x]; L[x] = L[y]; L[y] = t;
        } else
        if(ch[0] == 'E'){
            scanf("%d%d", &x2, &y2);
            t = a[L[x]][C[y]];
            a[L[x]][C[y]] = a[L[x2]][C[y2]];
            a[L[x2]][C[y2]] = t;
        }

        //scanf("\n");
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            long line=L[i],column=C[j];
            long elem = a[line][column];
            corr[n*(getX(elem)-1)+getY(elem)] = (i-1)*n+j;
        }
    }

    Ciur();

    for(i=1;i<=n*n;i++){
        if(corr[i] == -1) continue;
        long val = ciclu(i);

        for(i=1;divs[i] <= val;i++){
            if(val % divs[i] == 0){
                t = myPow(divs[i],aPow[i]);
                if(val % t == 0){
                    val /= t;
                    while(val % divs[i] == 0) aPow[i]++,val /= divs[i];
                }
            }
        }
    }

    ans = 1;
    for(i=1;i<=cont;i++){
        ans = (ans * myPow(divs[i],aPow[i]))% mod;
    }

    if(ans == 1) ans = 0;
    printf("%d\n",ans);

    return 0;
}
