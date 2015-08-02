#include <cstdio>
using namespace std;
int x,y,n,v,patrat,p,i,j,a[53][53],l,linie;
int main()
{
    freopen("zona.in","r",stdin);
    freopen("zona.out","w",stdout);
    scanf("%d%d%d%d",&x,&y,&n,&l);
    a[x][y]=1;
    for(i=1;i<=l;i++){
        scanf("%d",&p);
        if(p==1){x--;if(a[x][y]){v=a[x][y]-1;}a[x][y]=a[x+1][y]+1;}
        if(p==2){y++;if(a[x][y]){v=a[x][y]-1;}a[x][y]=a[x][y-1]+1;}
        if(p==3){x++;if(a[x][y]){v=a[x][y]-1;}a[x][y]=a[x-1][y]+1;}
        if(p==4){y--;if(a[x][y]){v=a[x][y]-1;}a[x][y]=a[x][y+1]+1;}
                     }
    for(i=0;i<=n-1;i++){
        linie=-1;
        for(j=0;j<=n;j++){
            if(linie>0){patrat++;}
            if((a[i][j]>v)&&(a[i+1][j]>v)){
                if((a[i][j]-a[i+1][j]==1)||(a[i+1][j]-a[i][j]==1)){linie*=-1;}
                if((a[i][j]-a[i+1][j]==l-v-1)||(a[i+1][j]-a[i][j]==l-v-1)){linie*=-1;}
                                          }
                         }
                       }
    printf("%d\n%d\n",l-v,patrat);
return 0;
}
