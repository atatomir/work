#include<iostream>
#include<fstream>
int  a[4000][4000];
using namespace std;
ifstream f("clepsidru.in");
ofstream g("clepsidru.out");

int main()
{
    int n,i,j,s=0,d;
    long long b;
    f>>n>>b>>d;
    for(i=1;i<=d;i++);
      {

       for(j=1;j<=2;j++)
            f>>a[i][j];}


for(i=1;i<=d;i++);
      {

       for(j=1;j<=2;j++)
            if(j==1)
                s=s+a[i][j];
      }
g<<s;
f.close();
g.close();
}

