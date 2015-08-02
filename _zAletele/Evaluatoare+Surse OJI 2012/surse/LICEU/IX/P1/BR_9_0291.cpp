#include <fstream>

using namespace std;
ifstream f("betasah.in");
ofstream g("betasah.out");
int n,d,k,m=0,b,i,o1,o2,s=0,p=0,j,x,y,z,t,v[1000][1000]={0};
int main()
{f>>n>>d>>k;
for(i=1;i<=d;i++)
{
    f>>t>>z;
    v[t][z]=3;
}
for(i=1;i<=k;i++)

{
    f>>x>>y;
    v[x][y]=2;
}
i=1;b=1;
while(i<=n)
{
    for(j=1;j<=b;j++)
    {
        if(v[i][j]!=2 && v[i][j]!=3)
        v[i][j]=1;
    }
    b++;
    i++;
}
i=1;b=1;
while(i<=n)
{
    for(j=1;j<=b;j++)
    {if(v[i][j]!=2) s++;
    if(v[i][j]==3)
    {o1=i;o2=j;
        while(o1>=1 && o2>=1 && o1<=n && o2<=n)
    {o2--;
    if(v[o1][o2]==1) {v[o1][o2]=4; p++;}
    }
    o1=i;o2=j;
    while(o1>=1 && o2>=1 && o1<=n && o2<=n)
    {o1--;
    o2--;
    if(v[o1][o2]==1) {v[o1][o2]=4; p++;}
    }
    o1=i;o2=j;
    while(o1>=1 && o2>=1 && o1<=n && o2<=n)
    {o1--;
    if(v[o1][o2]==1) {v[o1][o2]=4; p++;}
    }
    o1=i;o2=j;
    while(o1>=1 && o2>=1 && o1<=n && o2<=n)
    {o1--;
    o2++;
    if(v[o1][o2]==1) {v[o1][o2]=4; p++;}
    }
    o1=i;o2=j;
    while(o1>=1 && o2>=1 && o1<=n && o2<=n)
    {o2++;
    if(v[o1][o2]==1) {v[o1][o2]=4; p++;}
    }
    o1=i;o2=j;
    while(o1>=1 && o2>=1 && o1<=n && o2<=n)
    {o1++;
    o2++;
    if(v[o1][o2]==1) {v[o1][o2]=4; p++;}
    }
    o1=i;o2=j;
    while(o1>=1 && o2>=1 && o1<=n && o2<=n)
    {o1++;
    if(v[o1][o2]==1) {v[o1][o2]=4; p++;}
    }
    o1=i;o2=j;
    while(o1>=1 && o2>=1 && o1<=n && o2<=n)
    {o1++;
    o2--;
    if(v[o1][o2]==1) {v[o1][o2]=4; p++;}
    }
    }
    }
    if(m<s) m=s;
    s=0;
    b++;
    i++;
}
g<<m<<"\n"<<p;

    f.close();
    g.close();
    return 0;
}
