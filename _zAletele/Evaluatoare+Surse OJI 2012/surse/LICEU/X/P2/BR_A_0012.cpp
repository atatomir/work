#include <iostream>
#include <fstream>

using namespace std;
int v[51][51];
int x,y,n,l;
int a;
int main()
{
    ifstream f("zona.in");
    ofstream g("zona.out");
    f>>x>>y>>n>>l;
    int i,j,k;
    int nr=0;
    int nrt=0;
    int r=0;
    int u=0;

    i=x;
    j=y;

    for(k=1;k<=l;k++)
    {
        f>>a;
        if(a==3)
        {
            i+=1;
        }
        else if(a==1)
        {
            i-=1;
        }
        if(a==4)
        {
            if(u==2)
            {
                nrt+=r-2;
                r=0;
            }
            u=4;
            j-=1;
        }
        if(a==2)
        {
            if(u==4)
            {
                nrt+=r-2;
                r=0;
            }
            u=2;
            j+=1;
        }
        r++;
        v[i][j]++;
        if(v[i][j]==2)
        {
            int dx,dy;
            if(x>i)
            dx=x-i;
            else dx=i-x;
            if(y>j)
            dy=y-j;
            else dy=j-y;
            g<<l-dx-dy<<endl;
            cout<<l-dx-dy<<endl;
        }
        nr++;
    }
    g<<nrt;
    cout<<nrt;
}
