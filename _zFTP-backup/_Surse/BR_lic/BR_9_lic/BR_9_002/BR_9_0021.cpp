#include <fstream>

using namespace std;
ifstream fin("cool.in");
ofstream fout("cool.out");
int p,n,k,a[5003],i,j,l=1,maxi,nrd,pi=1,nrs,lungimea,vmin,check,ok,aux,sch,vmax=0,sc,b[5003],m;

int main()
{   fin>>p;
    fin>>n;
    fin>>k;
for(i=1;i<=n;i++)
  fin>>a[i];

//for(i=l;i<1+k;i++)
//     b[i]=a[i];
  if(p==1)
  {   do{sch=0;
      for(m=1;m<k;m++)
         if(a[m]>a[m+1])
          {aux=a[m+1];
           a[m+1]=a[m];
           a[m]=aux;
          sch=1;
          }



     }while(sch!=0);
ok=1;
for(m=1;m<k;m++)
   {if(a[m+1]!=a[m]+1)
        ok=0;
   }

for(m=1;m<=k;m++)
b[a[m]]++;


 if(ok==1)
{sc++;
   fout<<a[k];
}
else{ for(i=1;i<=k;i++)
        if(b[a[i]]==1)
           nrd++;
        fout<<nrd;
}
}
else
{
vmin=9999;
vmax=0;
check=0;
i=pi;

while(b[a[i]]==0)
  {b[a[i]]++;
   if(vmin>a[i])
      vmin=a[i];
   if(vmax<a[i]);
      vmax=a[i];
      i++;

  }
for(i=vmin;i<=vmax;i++)
      if(b[a[i]]>1)
      check=1;


   if(check==0)
   lungimea=vmax-vmin+1;


fout<<lungimea<<'\n'<<1;
}


    fin.close();
    fout.close();
    return 0;
}
