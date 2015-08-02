#include <fstream>

using namespace std;

int main()
{ int N,ab,c2,c3,c4,cN,cs1,cs2,ci,max,max1,max2, ba;
ifstream f ("martisoare.in");
ofstream g ("martisoare.out");
f>>N>>ab>>c2>>c3>>c4>>cN;
{g<<ab%10; g<<endl;
g<<ab/10;}
max=0;
g<<endl;
f>>ba;
if(ba>max)
   {g<<ba;}
 if(ba<max)
   {g<<max;}

if(c2>max1)
   {g<<c2;}
 if(c2<max1)
   if(c3>max1)
   {g<<c3;}
  if(c3<max1)
  if(c4>max1)
   {g<<c4;}
  if(c4<max1)
    if(cN>max1)
   {g<<cN;}
  if(cN<max1)

    return 0;
}
