#include <iostream>
#include<fstream>
using namespace std;
ifstream f("ferma.in");
ofstream g("ferma.out");
char a[401][401];
char b[401][401];
char x;
int v[30],t=0;
int k=0;
int y;
int dl[4]={-1,0,1,0};
int dc[4]={0,1,0,-1};
int contor=0;
int t2;
int m2=0;
char ch;
int cnt=0;
int OK=0;
struct pozitie
{
    int lin;
    int col;
}c[2000];
void fill(int i,int j)
{



        if(a[i][j]==x)
        {
            k++;
            if(k>m2)
            {
                m2=k;
                ch=b[i][j];
            }
            a[i][j]='@';


           for(int h=1;h<=4;h++)
           {
               fill(i+dl[h],j+dc[h]);
           }

        }
}
int main()
{
    f>>y;
    int i,j;
    int m,n;
    f>>m>>n;

        for(i=1;i<=m;i++)
        {
            for(j=1;j<=n;j++)
            {
                f>>a[i][j];
                b[i][j]=a[i][j];
            }

        }
         for(i=1;i<=m;i++)
                {
                    for(j=1;j<=n;j++)
                        {
                            if(a[i][j]!='@')
                                {
                                    x=a[i][j];
                                    k=0;
                                    fill(i,j);
                                    t++;
                                    v[t]=k;

                                }
                        }
                }

            int max=-1;
            for(i=1;i<=t;i++)
            {
                if(v[i]>max)
                {
                    max=v[i];
                }
            }
            if(y==1)

            {g<<max;}
    for(i=1;i<=m;i++)
    {

        for(j=1;j<=n;j++)
        {
            if(b[i][j]==ch)
            {
                cnt++;
                c[cnt].lin=i;
                c[cnt].col=j;
            }
        }
    }
    int ok=0;
    int r1,r2;
            for(i=1;i<=cnt;i++)
                {
                if(c[i].lin+2==c[i+1].lin)
                    {
                        ok=1;
                        r1=c[i].lin+1;
                        r2=c[i].col;
                        break;

                    }

                 if(c[i].col+2==c[i+1].col)
                    {
                        ok=1;
                        r2=c[i].col+1;
                        r1=c[i].lin;
                        break;
                    }
                }
                if(y==2)
                {
                    g<<r1<<" "<<r2<<'\n'<<ch;
                }
    f.close();
    g.close();
    return 0;
    }


