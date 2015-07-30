#include <iostream>
#include <fstream>
using namespace std;

int main()
{int v,p,s,i,j,k=0,q=0,a[100][100];
    ifstream f ("defrag.in");
    ofstream g ("defrag.out");
    f>>v;
    f>>p;
    f>>s;
    if (v==1)
    {for (i=1;i<=p;i++)
    {for (j=1;j<=s;j++)
        {f>>a[i][j];}
    }
    for (i=1;i<=p;i++)
    {for (j=1;j<=s;j++)
        {if (a[i][j]==0)
            k=k+1;
        }
    if (k==p)
        q=q+1;}
    g<<q;}
    if (v==2)
    {for (i=1;i<=p;i++)
       {for (j=1;j<=s;j++)
           {for (k=j+1;k<=s+1;k++)
               if (a[i][k]-a[i][j]==2 && s=2)
                  g<<"1"<<" ";
               if (a[i][k]-a[i][j]==1)
                  g<<"0"<<" ";
           }
       }

    }
    return 0;
}
