#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN (1<<21)

long n,m,i,lim;
char a[maxN],b[maxN],t[maxN<<1];

long how[maxN<<1];
long st,fin;

long fr[maxN],bk[maxN];
long ans[maxN];

void do_magic(){
    long i;
    st = 0; fin = 0;
    memset(how,0,sizeof(how));

    for(i=1;i<=m+1;i++) t[i] = b[i];
    for(i=1;i<=n+1;i++) t[m+1+i] = a[i];

    long dim = n+m+2; a[dim] = '#';
    for(i=2;i<dim;i++){
        if(i<=fin) how[i] = min(how[i-st+1],fin-i+1);
        while(t[ i+how[i] ] == t[ how[i]+1 ]) how[i]++;

        if(fin < i+how[i]-1){
            st = i;
            fin = (i+how[i]-1);
        }
    }
}

void swapA(){
    long i=1, j=n;
    while(i<=j)swap(a[i++],a[j--]);
}
void swapB(){
    long i=1, j=m;
    while(i<=j)swap(b[i++],b[j--]);
}
void swapBK(){
    long i=1, j=n;
    while(i<=j)swap(bk[i++],bk[j--]);
}

int main()
{
    freopen("aparitii.in","r",stdin);
    freopen("aparitii.out","w",stdout);

    scanf("%s\n%s",a+1,b+1);
    n = strlen(a+1);
    m = strlen(b+1);

    a[n+1] = b[m+1] = '@';

    do_magic();
    for(i=m+2;i<=n+m+1;i++) fr[i-m-1] = how[i];

    swapA(); swapB();

    do_magic();
    for(i=m+2;i<=n+m+1;i++) bk[i-m-1] = how[i];
    swapBK();

    lim = m/2;
    for(i=1;i+m<=n+1;i++){
        long v = min(lim, min( fr[i],bk[i+m-1] ) );
        ans[v]++;
    }

    for(i=lim;i;i--) ans[i] += ans[i+1];
    for(i=1;i<=lim;i++)printf("%ld\n",ans[i]);

    return 0;
}
