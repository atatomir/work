#include <iostream>
#include <fstream>

using namespace std;
ifstream f("calcule.in");
ofstream g("calcule.out");
int n,vect[100],nr[100];
void ordonare(int v[100],int n)
{int aux,i,j;
    for(i=1 ; i<=n-1 ; i++)
        for(j=i+1 ; j<= n ;j++)
        if(vect[i]>vect[j])
        {aux=vect[i];
        vect[i]=vect[j];
        vect[j]=aux;
        }


}
int cautare(int v[100],int c,int nr[1000])
{int i,j,sol,m,z,p,nrr=0;
  /*  for(i=1 ; i<=n-1 ; i++)
    {j=1;
        while(v[i]!=vect[j])
        {
            j++;
        }

        for(m=j+1 ; m<= n ; m++)
        {
            if(v[j+1]==v[m] && nr[j+1]==1)

            if(v[j+1]==v[m] && nr[j+1]!=1)
            {

                for(z=1 ; z<=n ; z++)
                {
                    if(v[z]==v[j+1] && v[i+1]<max)
                    {
                        sol=v[z];
                        max=v[i+1];
                    }
                }

             //   cout<<sol;
            }


        }


    } */
    for(i=1 ; i<= n-1 ; i++)
        {if(v[i]!=21000 && nr[i]==1)
            {for(j=1 ; j<= c ; j++)
                if(vect[j]==v[i])
                    j=p;
        for(j=i+1 ; j<=n ; j++)
            if(vect[p]==v[i])
            {
            v[i]=21000;
            }

            nrr++;}

          if(v[i]!=21000 && nr[i]!=1)
          {

          }

}


return nrr;




}

int main()
{ int n,k,v[1000],i,nr[100],j,vect[100],ok=1,o,c;
f>>n>>k;
for(i=1 ; i<=n ; i++)
f>>v[i];
j=1;
for(i=1 ; i<=n ; i++)
nr[i]=0;
for(i=1 ; i<=n ; i++)
  for(j=1 ; j<= n ;j++)

    {
      if(v[i]==v[j])
        nr[i]++;
    }

for(i=1 ; i<= n ; i++)
vect[i]=0;
j=1;
for(i=1 ; i<= n ; i++)
{   ok=1; c=j;
    if(nr[i]==1)
   {vect[j]=v[i];
    j++;
       ////

   }
    else
        for(o=1 ; o<=c && ok==1; o++)
            if(vect[o]==v[i])
                ok=0;
            if(ok==1)
                {vect[j]=v[i];

                j++;}   ////////


}

    ordonare(vect,n);
    g<<cautare(v,c,nr);

    return 0;
}
