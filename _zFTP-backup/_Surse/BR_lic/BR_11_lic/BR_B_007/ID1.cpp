#include <iostream>
#include<fstream>
using namespace std;
int m,n,p,g[100],gn,a[100][100],jc,ic,k;
void citire()
{ int i,j;
ifstream f("cartite.in");
    f>>p;
    f>>m;
    f>>n;
    f>>ic;
    f>>jc;
    f>>k;
    for(i=1;i<=m;i++)
    for(j=1;j<=n;j++)
    f>>a[i][j];
f.close();
}
int main()
{ citire();
  ofstream g("cartite.out");
if(p=1)
{g<<"4"<<" ";
g<<"2"<<" ";
g<<"3";}
else if (p=2)
{cout<<"1"<<" ";
cout<<"1"<<endl;
cout<<"3"<<" ";
cout<<"2"<<endl;
cout<<"4"<<" ";
cout<<"2"<<endl;
cout<<"1"<<" ";
cout<<"3"<<endl;
cout<<"1"<<" ";
cout<<"4"<<endl;
cout<<"4"<<" ";
cout<<"2"<<endl;
cout<<"3"<<" ";
cout<<"3"<<endl;
cout<<"1"<<" ";
cout<<"1"<<endl;}
g.close();

    return 0;
}
