#include <fstream>

using namespace std;

int a[1005][1005], p;
void numara(int sx, int sy, int incx, int incy, int pr)
{
    int sw=1, ssx, ssy;
    ssx=sx+incx;
    ssy=sy+incy;
    while(sw)
    {
        if(!a[ssx][ssy])
        {
            a[ssx][ssy]=2;
            p++;
            ssx+=incx;
            ssy+=incy;
        }
        else sw=0;
    }
}
int main()
{
    ifstream read("betasah.in");
    ofstream write("betasah.out");
    int n, d, k, i, j, x[105], y[105], z, t, m, c, cxy=0;
    read>>n>>d>>k;
    for(i=1; i<=d; i++)
    {
        read>>x[cxy]>>y[cxy];
        a[x[cxy]][y[cxy]]=1;
        cxy++;
    }
    for(i=1; i<=k; i++)
    {
        read>>z>>t;
        a[z][t]=2;
    }
    read.close();
    for(i=0; i<=n; i++)
        a[i][0]=2;
    a[0][1]=2;
    for(i=1; i<=n; i++)
        a[i][i+1]=2;
    for(i=0; i<=n+1; i++)
        a[n+1][i]=2;
    m=0;
    for(i=1; i<=n; i++)
    {
        c=0;
        for(j=1; j<=i+1; j++)
            if(!a[i][j] || a[i][j]==1)
                c++;
        if(c>m) m=c;
    }
    write<<m<<'\n';
    p=0;
    for(i=0; i<cxy; i++)
    {
        numara(x[i], y[i], 1, 0, p);
        numara(x[i], y[i], -1, 0, p);
        numara(x[i], y[i], 0, 1, p);
        numara(x[i], y[i], 0, -1, p);
        numara(x[i], y[i], 1, 1, p);
        numara(x[i], y[i], 1, -1, p);
        numara(x[i], y[i], -1, 1, p);
        numara(x[i], y[i], -1, -1, p);
    }
    write<<p<<'\n';
    write.close();
    return 0;
}
