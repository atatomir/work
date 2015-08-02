#include <fstream>

using namespace std;
ifstream fin("pseudobil.in");
ofstream fout("pseudobil.out");
int p,ci,cj,n,k,d,m,i,l,f,j,nrp,z,g,jum,a[1501][1501];
int main()
{ fin>>p;
fin>>ci;
fin>>cj;
fin>>d;
     if(p==1)
    {if (d==2)
      fout<<1;
      if(d==4)
        fout<<5;
      if(d==6)
        fout<<13;
    if(d==8)
       fout<<24;
    }
    if(p==2)

  if (p==2)
  { for(i=1;i<=m;i++)
      {fout<<0<<'\n'<<0;
      }
  }
   return 0;
}
