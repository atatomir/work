#include <cstdio>

using namespace std;
long yyy,vv,maax,li,co,cerinta,n,m,i,lin,col,a[510][510],x,y,pct,max,fav,pass[500][500],val[500][500];
void sp(long lin, long col, long pas)
    {
    if (max<pas) max=pas;
    a[lin][col]=-1; fav--; //aa=lin[col]=2;
    if (a[lin-1][col]==4)
        sp(lin-1,col,pas+1);
    if (a[lin+1][col]==2)
        sp(lin+1,col,pas+1);
    if (a[lin][col-1]==1)
        sp(lin,col-1,pas+1);
    if (a[lin][col+1]==3)
        sp(lin,col+1,pas+1);
    }
/*long maxdr(long lin, long col)
    {
    long maximus;
    if (aa[lin][col]==1) return val[lin][col];
            else
            {
            maximus=-1; aa[lin][col]=1;
            if (a[lin-1][col]==4)
                {
                x=maxdr(lin-1,col)+1000;
                if (maximus<x)
                    maximus=x;
                }
            if (a[lin+1][col]==2)
                {
                x=maxdr(lin+1,col)+1000;
                if (maximus<x)
                    maximus=x;
                }
            if (a[lin][col-1]==1)
                {
                x=maxdr(lin,col-1)+1000;
                if (maximus<x)
                    maximus=x;
                }
            if (a[lin][col+1]==3)
                {
                x=maxdr(lin,col+1)+1000;
                if (maximus<x)
                    maximus=x;
                }
            //
            val[lin][col]=maximus;
            return maximus;
            }
    }*/
long gfi(long lin, long col)
    {
    if (pass[lin][col]==1) return val[lin][col];
            else
            switch (a[lin][col])
                {
                case 1: {val[lin][col]=gfi(lin,col+1)+1000; pass[lin][col]=1; return val[lin][col]; break;}
                case 2: {val[lin][col]=gfi(lin-1,col)+1000; pass[lin][col]=1; return val[lin][col]; break;}
                case 3: {val[lin][col]=gfi(lin,col-1)+1000; pass[lin][col]=1; return val[lin][col]; break;}
                case 4: {val[lin][col]=gfi(lin+1,col)+1000; pass[lin][col]=1; return val[lin][col]; break;}
                }
    }
long maxd(long lin, long col)
    {
    if (pass[lin][col]==1)
            return val[lin][col];
            else
            {
            li=lin; co=col;
            do{
            if (pass[li][co]!=1)
            {
            pass[li][co]=5;
            x=li; y=co;
            switch (a[li][co])
                {
                case 1: {y++; break;}
                case 2: {x--; break;}
                case 3: {y--; break;}
                case 4: {x++; break;}
                }
            li=x; co=y;
            }
            }while ((pass[li][co]!=5)&&(pass[li][co]!=1));
            if (pass[li][co]==1)
                return gfi(lin,col);
            //
            pct=0;
            do{
            pass[li][co]=2;
            x=li; y=co;
            switch (a[li][co])
                {
                case 1: {y++; break;}
                case 2: {x--; break;}
                case 3: {y--; break;}
                case 4: {x++; break;}
                }
            li=x; co=y; pct++;
            }while(pass[li][co]!=2);
            //
            /*pct=0;
            do{
            pas[li][co]=3;
            x=li; y=co;
            switch (a[li][co])
                {
                case 1: {y++; break;}
                case 2: {x--; break;}
                case 3: {y--; break;}
                case 4: {x++; break;}
                }
            li=x; co=y; pct++;
            }while(pas[li][co]!=3);*/
            //
            do{
            pass[li][co]=1; val[li][co]=pct*1000;
            x=li; y=co;
            switch (a[li][co])
                {
                case 1: {y++; break;}
                case 2: {x--; break;}
                case 3: {y--; break;}
                case 4: {x++; break;}
                }
            li=x; co=y;
            }while(pass[li][co]!=1);
            return gfi(lin,col);
            }
    }
int main()
{
freopen("arrows.in","r",stdin);
freopen("arrows.out","w",stdout);
scanf("%ld",&cerinta);
scanf("%ld%ld",&n,&m);
for (i=1; i<=n; i++)
    for (y=1; y<=m; y++)
        scanf("%ld",&a[i][y]);
scanf("%ld%ld",&lin,&col); max=-1;
if (cerinta==1)
    {
    do{
    x=lin; y=col;
    switch (a[lin][col])
        {
        case 1: {y++; break;}
        case 2: {x--; break;}
        case 3: {y--; break;}
        case 4: {x++; break;}
        }
    a[lin][col]=0;
    lin=x; col=y;
    pct++;
    }while(a[lin][col]>0);
    if ((lin>0)&&(lin<=n)&&(col>0)&&(col<=m)) pct*=1000;
    printf("%ld",pct);
    }
    else
    {
    fav=n*m;
    for (i=1; i<=n; i++)
            {
            if(a[i][1]==3) sp(i,1,1);
            if(a[i][m]==1) sp(i,m,1);
            }
    for (y=1; y<=m; y++)
            {
            if(a[1][y]==2) sp(1,y,1);
            if(a[n][y]==4) sp(n,y,1);
            }
    if (cerinta==2)
        {
        printf("%ld",fav);
        }
    if (cerinta==3)
        {
        for (i=1; i<=n; i++)
                for (yyy=1; yyy<=m; yyy++)
                    if ((a[i][yyy]>0)&&(a[i][yyy]<5))
                    {
                    if (val[i][yyy]==0) {val[i][yyy]=1000; pass[i][yyy]=0;}
                    val[i][yyy]=maxd(i,yyy);
                    vv=val[i][yyy];
                    if (maax<vv)
                        maax=vv;
                    }
        printf("%ld",maax);
        }
    }
return 0;
}
