#include<fstream>
//using namespace std;
ifstream f ("triunghi.in");
ofstream g ("triunghi.out");
int main()
{
long long v[50];
long min;
int i,n,x,j;
f>>v;
f>>n;
f>>k;
f>>min;
v[1]=min;
for (i=2;i<=n;i++)
        {f>>v[i];
         if (v[i]<min)
            min=v[i];
        }
if (v==1)
{g<<min;
x=min;
  for (i=2;i<=k;i++)
  {x=x*3+1;
  g<<x<<" ";}
}
x=v[1]+13;
if (v==2)
    {for(i=1;i<=n;i++)
    g<<v[i];
    for (j=n+1;j<=k;j++)
        {x=x*3;
        x=x-3;
        g<<x;
        }
    }

f.close();
g.close();



return 0;
}
