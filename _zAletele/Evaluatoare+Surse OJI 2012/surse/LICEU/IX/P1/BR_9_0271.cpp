#include<iostream>
#include<fstream>
using namespace std;
int main()
{
    int nrlincol,dame,kgri,i,j,k,M[101][101],alb,albMax,x,y,xmare,nrposibilitati,xdama[101],ydama[101]/*,xreplacer,yreplacer*/;
    ifstream f1("betasah.in");
    ofstream f2("betasah.out");
    f1>>nrlincol>>dame>>kgri;
    for (i=1;i<=nrlincol;i++)
    {
        for (k=1;k<=nrlincol;k++)
        {
            M[i][k]=-2;
        }
        for (j=1;j<=i;j++)
        {
            M[i][j]=0;
        }
    }
    for (i=1;i<=dame;i++)
    {
        f1>>xdama[i]>>ydama[i];
        M[xdama[i]][ydama[i]]=1;
    }
    for (i=1;i<=kgri;i++)
    {
        f1>>x>>y;
        M[x][y]=-1;
    }
    albMax=0;
    for (i=1;i<=nrlincol;i++)
    {
        alb=0;
        for (j=1;j<=nrlincol;j++)
        {
            if ((M[i][j]==0)||(M[i][j]==1))
            {
                alb=alb+1;
            }
        }
        if (alb>albMax)
        {
            albMax=alb;
            xmare=i;
        }
    }
    f2<<xmare<<"\n";
    nrposibilitati=0;/*
    for (i=1;i<=dame;i++)
    {
        for (j=1;j<=8;j++)
        {
            if (j==1)
            {
                xreplacer=xdama[i];
                yreplacer=ydama[i];
                while ((M[xreplacer][yreplacer]!=-1)&&(M[xreplacer][yreplacer]!=1))
                {
                    xreplacer-=1;
                    yreplacer=yreplacer;
                    if  ((M[xreplacer][yreplacer]==-1)||(M[xreplacer][yreplacer]==1))
                    {
                        break;
                    }
                    else
                    {
                        if (M[xreplacer][yreplacer]==0)
                        {
                            nrposibilitati=nrposibilitati+1;
                            M[xreplacer][yreplacer]=3;
                        }
                    }
                }
            }
            if (j==2)
            {
                xreplacer=xdama[i];
                yreplacer=ydama[i];
                while ((M[xreplacer][yreplacer]!=-1)&&(M[xreplacer][yreplacer]!=1))
                {
                    xreplacer=xreplacer-1;
                    yreplacer=yreplacer-1;
                    if  ((M[xreplacer][yreplacer]==-1)||(M[xreplacer][yreplacer]==1))
                    {
                        break;
                    }
                    else
                    {
                         if (M[xreplacer][yreplacer]==0)
                        {
                            nrposibilitati=nrposibilitati+1;
                            M[xreplacer][yreplacer]=3;
                        }
                    }
                }
            }
            if (j==3)
            {
                xreplacer=xdama[i];
                yreplacer=ydama[i];
                while ((M[xreplacer][yreplacer]!=-1)&&(M[xreplacer][yreplacer]!=1))
                {
                    xreplacer=xreplacer;
                    yreplacer=yreplacer+1;
                    if  ((M[xreplacer][yreplacer]==-1)||(M[xreplacer][yreplacer]==1))
                    {
                        break;
                    }
                    else
                    {
                         if (M[xreplacer][yreplacer]==0)
                        {
                            nrposibilitati=nrposibilitati+1;
                            M[xreplacer][yreplacer]=3;
                        }
                    }
                }
            }
            if (j==4)
            {
                xreplacer=xdama[i];
                yreplacer=ydama[i];
                while ((M[xreplacer][yreplacer]!=-1)&&(M[xreplacer][yreplacer]!=1))
                {
                    xreplacer=xreplacer+1;
                    yreplacer=yreplacer+1;
                    if  ((M[xreplacer][yreplacer]==-1)||(M[xreplacer][yreplacer]==1))
                    {
                        break;
                    }
                    else
                    {
                         if (M[xreplacer][yreplacer]==0)
                        {
                            nrposibilitati=nrposibilitati+1;
                            M[xreplacer][yreplacer]=3;
                        }
                    }
                }
            }
            if (j==5)
            {
                xreplacer=xdama[i];
                yreplacer=ydama[i];
                while ((M[xreplacer][yreplacer]!=-1)&&(M[xreplacer][yreplacer]!=1))
                {
                    xreplacer=xreplacer+1;
                    yreplacer=yreplacer;
                    if  ((M[xreplacer][yreplacer]==-1)||(M[xreplacer][yreplacer]==1))
                    {
                        break;
                    }
                    else
                    {
                         if (M[xreplacer][yreplacer]==0)
                        {
                            nrposibilitati=nrposibilitati+1;
                            M[xreplacer][yreplacer]=3;
                        }
                    }
                }
            }
            if (j==6)
            {
                xreplacer=xdama[i];
                yreplacer=ydama[i];
                while ((M[xreplacer][yreplacer]!=-1)&&(M[xreplacer][yreplacer]!=1))
                {
                    xreplacer=xreplacer+1;
                    yreplacer=yreplacer-1;
                    if  ((M[xreplacer][yreplacer]==-1)||(M[xreplacer][yreplacer]==1))
                    {
                        break;
                    }
                    else
                    {
                        if (M[xreplacer][yreplacer]==0)
                        {
                            nrposibilitati=nrposibilitati+1;
                            M[xreplacer][yreplacer]=3;
                        }
                    }
                }
            }
            if (j==7)
            {
                xreplacer=xdama[i];
                yreplacer=ydama[i];
                while ((M[xreplacer][yreplacer]!=-1)&&(M[xreplacer][yreplacer]!=1))
                {
                    xreplacer=xreplacer;
                    yreplacer=yreplacer-1;
                    if  ((M[xreplacer][yreplacer]==-1)||(M[xreplacer][yreplacer]==1))
                    {
                        break;
                    }
                    else
                    {
                         if (M[xreplacer][yreplacer]==0)
                        {
                            nrposibilitati=nrposibilitati+1;
                            M[xreplacer][yreplacer]=3;
                        }
                    }
                }
            }
            if (j==8)
            {
                xreplacer=xdama[i];
                yreplacer=ydama[i];
                while ((M[xreplacer][yreplacer]!=-1)&&(M[xreplacer][yreplacer]!=1))
                {
                    xreplacer=xreplacer-1;
                    yreplacer=yreplacer-1;
                    if  ((M[xreplacer][yreplacer]==-1)||(M[xreplacer][yreplacer]==1))
                    {
                        break;
                    }
                    else
                    {
                         if (M[xreplacer][yreplacer]==0)
                        {
                            nrposibilitati=nrposibilitati+1;
                            M[xreplacer][yreplacer]=3;
                        }
                    }
                }
            }
        }
    }*/
    f2<<nrposibilitati;
    return 0;
}
