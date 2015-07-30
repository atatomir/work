//Prof. Vitelaru Sofia
#include <fstream>
#include<algorithm>
using namespace std;
ifstream f("casa.in");
ofstream g("casa.out");
struct matrice{
  int l,c;
}q[100010];
int a[100010];
int dx[4]={0,1,-1,0}, dy[4]={1,0,0,-1},dx1[]={0,-1,1,0},dy1[]={-1,0,0,1};
char dir1[]="ESNV";
int var,i,j,n,lmax,cmax,cmin,v,m,nr,lmin;
char ch;int dir[256];
int cmp(matrice a, matrice b){
    if(a.l==b.l)
        return a.c<b.c;
    return a.l<b.l;
}
int main()
{
f>>var;
dir['E']=0;dir['S']=1;dir['N']=2;dir['V']=3;
if(var==1){
        f>>n;
    q[1].l=1;
    q[1].c=1;cmin=lmin=1000000000;
    for(i=2;i<=n;i++){
        f>>v>>ch;
        q[i].l=q[v].l+dx[dir[ch]];
        q[i].c=q[v].c+dy[dir[ch]];
        if(q[i].l>lmax)
                lmax=q[i].l;
        if(q[i].l<lmin){
            lmin=q[i].l;
        }
        if(q[i].c>cmax)
              cmax=q[i].c;
        if(q[i].c<cmin)
            cmin=q[i].c;
    }
   if(cmin<=0){
       cmax+=(-cmin)+1;
       for(i=1;i<=n;i++)
            q[i].c+=(-cmin)+1;
   }

      if(lmin<=0){
         lmax+=(-lmin);
         for(i=1;i<=n;i++)
            q[i].l+=(-lmin)+1;
      }

     g<<lmax<<" "<<cmax<<'\n';



  sort(q+1,q+n+1,cmp);

int k=1;
for(i=1;i<=lmax;i++)
{
    for(j=1;j<=cmax;j++)
         if(i==q[k].l&&j==q[k].c)
           {
              g<<1<<" ";k++;
           }
         else
            g<<0<<" ";


    g<<'\n';
}
return 0;
}
f>>n>>m;
int x,c1;
for(i=1;i<=n;i++)
  for(j=1;j<=m;j++){
    f>>x;
    if(x==1){
        nr++;
        if(nr==1)
            c1=j;
        a[(i-1)*m+j]=-1;

    }
  }
g<<nr<<" "<<c1<<'\n';

q[1].l=1;q[1].c=c1;
a[c1]=1;
int p=1,u=1;
nr=1;
while(p<=u){
    for(int k=0;k<4;k++)
    {
        int l=q[p].l+dx[k];
        int c=q[p].c+dy[k];
        int t=(l-1)*m+c;
        if(l>=1&&l<=n&&c>=1&&c<=m&&a[t]==-1){
            nr++;
            g<<a[(q[p].l-1)*m+q[p].c]<<" "<<dir1[k]<<'\n';
            a[t]=nr;
            u++;
            q[u].l=l;
            q[u].c=c;

        }
    }
    p++;
}

return 0;
}


