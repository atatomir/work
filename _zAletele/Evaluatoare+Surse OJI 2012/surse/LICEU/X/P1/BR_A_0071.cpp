#include <fstream>
using namespace std;
int a[51][51],np,p,x,y,i,j,n,l,x1,y1,dl[5]={0,-1,0,1,0},dc[5]={0,0,1,0,-1};
int qx[2501],qy[2501],w1,w2,b,nc,s,q;
int main()
{
    ifstream f("zona.in");
    ofstream g("zona.out");
    f>>x>>y>>n>>l;
    for(i=0;i<=n+1;i++)
        a[i][0]=a[i][n+1]=a[0][i]=a[n+1][i]=-2;
    a[x][y]=1;
    x1=x;y1=y;
    for(i=1;i<l;i++){
        f>>p;
        x1+=dl[p];y1+=dc[p];
        a[x1][y1]=i;
    }
    f>>p;
    np=l-a[x1+dl[p]][y1+dc[p]];
    g<<np<<'\n';
    x1+=dl[p];y1+=dc[p];
    for(i=1;i<=n;i++){
        j=1;
        while(a[i][j]==0)
            a[i][j++]=-2;
        j=n;
        while(a[i][j]==0)
            a[i][j--]=-2;
        j=1;
        while(a[j][i]==0)
            a[j++][i]=-2;
        j=n;
        while(a[j][i]==0)
            a[j--][i]=-2;
    }

    qx[1]=x1;qy[1]=y1;w1=w2=1;
    a[x1][y1]=-3;
    do{
        b=0;
        for(i=w1;i<=w2;i++)
            for(j=1;j<=4;j++)
                if(a[qx[i]+dl[j]][qy[i]+dc[j]]!=-2&&a[qx[i]+dl[j]][qy[i]+dc[j]]!=-3){
                    b++;
                    a[qx[i]+dl[j]][qy[i]+dc[j]]=-3;
                    qx[w2+b]=qx[i]+dl[j];
                    qy[w2+b]=qy[i]+dc[j];
                }
        w1=w2+1;w2+=b;
    }while(w1<=w2);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(a[i][j]==-3&&a[i][j+1]==-3&&a[i+1][j]==-3&&a[i+1][j+1]==-3)
             nc++;
    g<<nc<<'\n';
    f.close();
    g.close();
    return 0;
}


