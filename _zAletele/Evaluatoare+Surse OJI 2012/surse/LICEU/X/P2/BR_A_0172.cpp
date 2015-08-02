#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream f("zona.in");
    ofstream g("zona.out.");
    int a[52][52],l,x,y,n,v[2502],i,j,nr;
    f>>x>>y>>n>>l;
    for(i=1;i<=l;i++)
        f>>v[i];
    a[x][y]=1;
    nr=0;
    for(i=1;i<=l;i++)
        {
            if(v[i]==1)
                x--;

            if(v[i]==2)
                y++;
            if(v[i]==3)
                x++;
            if(v[i]==4)
                y--;
            a[x][y]=1;

       }
       cout<<nr<<endl;
    for(i=1;i<=n;i++)
        {for(j=1;j<=n;j++)
            cout<<a[i][j];

        }

    return 0;
}
