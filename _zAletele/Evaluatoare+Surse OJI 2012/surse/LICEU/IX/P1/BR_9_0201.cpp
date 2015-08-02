#include <fstream>
using namespace std;
//n = nr randuri
//d = nr dame
//k = nr gri
int d,n,k,x[1001],y[1001],z[1001],t[1001],i,tabla[1001][1001],j,m=-1,s,aux,q,w;
int main()
{
    ifstream in("betasah.in");
    ofstream out("betasah.out");
    in>>n>>d>>k;
    for(i=1;i<=d;i++)
        in>>x[i]>>y[i];
    for(i=1;i<=k;i++)
        in>>z[i]>>t[i];
    in.close();
    //bordare
    for(i=0;i<=n+1;i++)
    {

        tabla[0][i]=1;
        tabla[i][0]=1;
        tabla[i][n+1]=1;
        tabla[n+1][i]=1;
        tabla[i][i+1]=1;
    }
    for(i=0;i<=n+1;i++)
    {
        tabla[z[i]][t[i]]=1;
        tabla[x[i]][y[i]]=1;
    }
    //cautare max
    for(i=1;i<=n;i++)
        {
            s=0;
            for(j=1;j<=n;j++)
                if(tabla[1][i]==0)
                {
                    if(tabla[i][j]==0)
                    s++;
                }
                else
                    break;
            if(s>=m)
            m=s;
        }
    //cautare miscari unice disponibile
    s=0;
    for(i=1;i<=d;i++)
    {
            q=x[i];w=y[i];
            //N
            if(tabla[q-1][w]==0)
            {
                s++;
                tabla[q-1][w]=1;
                for(j=1;j<=n;j++)
                if(tabla[q-1-j][w]==0)
                {
                    s++;
                    tabla[q-1-j][w]=1;
                }
                else break;

            }
            //NE
            if(tabla[q-1][w+1]==0)
            {
                s++;
                tabla[q-1][w+1]=1;
                for(j=1;j<=n;j++)
                if(tabla[q-1-j][w+1+j]==0)
                {
                    s++;
                    tabla[q-1-j][w+1+j]=1;
                } else break;
            }
            //E
            if(tabla[q][w+1]==0)
            {
                s++;
                tabla[q][w+1]=1;
                for(j=1;j<=n;j++)
                if(tabla[q][w+1+j]==0)
                {
                    s++;
                    tabla[q][w+1+j]=1;
                } else break;
            }
            //SE
            if(tabla[q+1][w+1]==0)
            {
                s++;
                tabla[q+1][w+1]=1;
                for(j=1;j<=n;j++)
                if(tabla[q+1+j][w+1+j]==0)
                {
                    s++;
                    tabla[q+1+j][w+1+j]=1;
                } else break;
            }
            //S
            if(tabla[q+1][w]==0)
            {
                s++;
                tabla[q+1][w]=1;
                for(j=1;j<=n;j++)
                if(tabla[q+1+j][w]==0)
                {
                    s++;
                    tabla[q+1+j][w]=1;
                } else break;
            }
            //SW
            if(tabla[q+1][w-1]==0)
            {
                s++;
                tabla[q+1][w-1]=1;
                for(j=1;j<=n;j++)
                if(tabla[q+1+j][w-1-j]==0)
                {
                    s++;
                    tabla[q+1+j][w-1-j]=1;
                } else break;
            }
            //W
            if(tabla[q][w-1]==0)
            {
                s++;
                tabla[q][w-1]=1;
                for(j=1;j<=n;j++)
                if(tabla[q][w-1-j]==0)
                {
                    s++;
                    tabla[q][w-1-j]=1;
                } else break;
            }
            //NW
            if(tabla[q-1][w-1]==0)
            {
                s++;
                tabla[q-1][w-1]=1;
                for(j=1;j<=n;j++)
                if(tabla[q-1-j][w-1-j]==0)
                {
                    s++;
                    tabla[q-1-j][w-1-j]=1;
                } else break;
            }
        }
    //afisare
    out<<m<<'\n';
    out<<s<<'\n';
}
