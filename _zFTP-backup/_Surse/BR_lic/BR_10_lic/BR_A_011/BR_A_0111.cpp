#include <iostream>
#include <fstream>
using namespace std;
int main()
{ifstream f("ferma.in");
ofstream g("ferma.out");
int v,i,j,m,n,max,mov=0,galben=0,albastru=0,verde=0,rosu=0;
char d[400][400];
f>>v;
f>>m>>n;
for(i=1;i<=m;i++)
{for(j=1;j<=n;j++)
f>>d[i][j];}
if(v==1)
{for(i=1;i<=m;i++)
{for(j=1;j<=n;j++)
if(d[i][j]==d[i][j+1])
{if(d[i][j]=='r')
rosu++;
else if(d[i][j]=='m')
mov++;
else if(d[i][j]=='g')
galben++;
else if(d[i][j]=='a')
albastru++;
else verde++;}
}
max=rosu;
if(max>=rosu&&max>=mov&&max>=galben&&max>=albastru&&max>=verde)
g<<max-1;
max=mov;
if(max>=rosu&&max>=mov&&max>=galben&&max>=albastru&&max>=verde)
g<<max-1;
max=galben;
if(max>=rosu&&max>=mov&&max>=galben&&max>=albastru&&max>=verde)
g<<max-1;
max=albastru;
if(max>=rosu&&max>=mov&&max>=galben&&max>=albastru&&max>=verde)
g<<max-1;
max=verde;
if(max>=rosu&&max>=mov&&max>=galben&&max>=albastru&&max>=verde)
g<<max-1;
}
else
{
    {for(j=1;j<=n;j++)
if(d[i][j]==d[i][j+1])
{if(d[i][j]=='r')
rosu++;
else if(d[i][j]=='m')
mov++;
else if(d[i][j]=='g')
galben++;
else if(d[i][j]=='a')
albastru++;
else verde++;}
}
for(i=1;i<=m;i++)
{for(j=1;j<=n;j++)
if((d[i][j]==d[i][j+2])&&(d[i][j+1]=='r')&&(d[i][j]!=d[i][j+1]))
{{rosu++;}
g<<i<<" "<<j+1<<" ";
}else if((d[i][j]==d[i][j+2])&&(d[i][j+1]=='m')&&(d[i][j]!=d[i][j+1]))
{{mov++;}
g<<i<<" "<<j+1<<" ";
}else if((d[i][j]==d[i][j+2])&&(d[i][j+1]=='g')&&(d[i][j]!=d[i][j+1]))
{{galben++;}
g<<i<<" "<<j+1<<" ";
}else if((d[i][j]==d[i][j+2])&&(d[i][j+1]=='a')&&(d[i][j]!=d[i][j+1]))
{{albastru++;}
g<<i<<" "<<j+1<<" ";
}
else if((d[i][j]==d[i][j+2])&&(d[i][j+1]=='v')&&(d[i][j]!=d[i][j+1]))
{{verde++;
g<<i<<" "<<j+1<<" ";
}
}
}
g<<endl;
{max=rosu;
if(max>=rosu&&max>=mov&&max>=galben&&max>=albastru&&max>=verde)
g<<"r";
max=mov;
if(max>=rosu&&max>=mov&&max>=galben&&max>=albastru&&max>=verde)
g<<"m";
max=galben;
if(max>=rosu&&max>=mov&&max>=galben&&max>=albastru&&max>=verde)
g<<"g";
max=albastru;
if(max>=rosu&&max>=mov&&max>=galben&&max>=albastru&&max>=verde)
g<<"a";
max=verde;
if(max>=rosu&&max>=mov&&max>=galben&&max>=albastru&&max>=verde)
g<<"v";
}
}
f.close();
g.close();
    return 0;
}
