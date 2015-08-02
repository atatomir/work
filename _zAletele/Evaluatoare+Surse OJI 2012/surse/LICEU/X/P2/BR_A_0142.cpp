#include <iostream>
#include <fstream>

using namespace std;

fstream f("zona.in",ios::in);
fstream g("zona.out",ios::out);

short poz[51][51],i,j,n,lin,col,mut,x,pozgasit,poz1,cmin[51],cmax[51],lmin,lmax,nrp;

int main()
{
    f>>lin>>col>>n>>mut;
    poz[lin][col]=1;
    pozgasit=0;
    for (i=1;i<=mut;i++)
    {
        f>>x;
        if (x==1)
        {
            if (poz[lin-1][col]==0) {
                                        poz[lin-1][col]=poz[lin][col]+1;
                                        lin--;
            }
                                else {
                                        pozgasit=poz[lin][col]+1-poz[lin-1][col];
                                        poz1=poz[lin-1][col];

                                        break;
                                        }
        }
        if (x==2)
        {
            if (poz[lin][col+1]==0) {
                                        poz[lin][col+1]=poz[lin][col]+1;
                                        col++;
            }
                                else {
                                       pozgasit=poz[lin][col]+1-poz[lin][col+1];
                                       poz1=poz[lin][col+1];
                                       break;
                                        }
        }
        if (x==3)
        {
            if (poz[lin+1][col]==0)
            {
                poz[lin+1][col]=poz[lin][col]+1;
                lin++;
            }
            else
            {
                pozgasit=poz[lin][col]+1-poz[lin+1][col];
                poz1=poz[lin+1][col];
                break;
            }
        }
        if (x==4)
        {
            if (poz[lin][col-1]==0)
            {
            poz[lin][col-1]=poz[lin][col]+1;
            col--;
            }
            else
            {
                pozgasit=poz[lin][col]+1-poz[lin][col-1];
                poz1=poz[lin][col-1];
                break;
            }
        }
    }
    g<<pozgasit<<endl;
    for (i=0;i<=n;i++)
    {
        cmin[i]=n+1;
        cmax[i]=0;
    }
    lmin=n;
    lmax=0;
    for (i=0;i<=n;i++)
        for (j=0;j<=n;j++)
        {
            if (poz[i][j]>=poz1)
            {
                if (i>lmax) lmax=i;
                if (i<lmin) lmin=i;
                if (j>cmax[i]) cmax[i]=j;
                if (j<cmin[i]) cmin[i]=j;
            }
        }
    nrp=0;
    for (i=lmin+1;i<=lmax;i++)
    {
        nrp=nrp+cmax[i]-cmin[i];
    }
    g<<nrp;
    f.close();g.close();

    return 0;
}
