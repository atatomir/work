#include <iostream>
#include <fstream>

using namespace std;
int main ()
{
    int N,K,A[1001],i,inv=0,aux,dis=0,j,b[1001],apar=1,b1=0;
    short int p;
    bool cool=1;
    ifstream f("cool.in");
    ofstream g("cool.out");
    f >> p >> N >> K;
    for (i=1;i<=N;i++)
            f >> A[i];
  //  cout << "A ";
    if (p==1)
    {
        do
        {
            inv=0;
            for (i=1;i<K;i++)
                 if (A[i]>A[i+1]) {aux=A[i];
                                   A[i]=A[i+1];
                                   A[i+1]=aux;
                                   inv=1;}

        } while (inv==1);
    //    cout << " B ";
        for (i=1;i<K;i++)
             if (A[i]!=A[i+1]-1) cool=0;
        if (cool==0)
          {
//cout << " D ";
            for (i=2;i<K;i++)
                  {
                      if (A[i]!=A[i+1]&&A[i]!=A[i-1]) {b1++;
                                                       b[b1]=A[i];}
                  }
            if (A[1]!=A[2]) b1++;
            if (A[K]!=A[K-1]) b1++;
            g << b1;                  // RASPUNS la 1 : b1
          }
         if (cool==1) g << A[K];


    }
    if (p==2)
    {
         for (int k=1;k<=N-K+1;k++)
             {
                 for (i=k;i<=K;i++)
                      b[i]=A[k];
                 do
                 {
                    inv=0;
                    for (int k1=1;k1<K;k1++)
                         if (b[k1]>b[k1+1]) {aux=b[k1];
                                   b[k1]=b[k1+1];
                                   b[k1+1]=aux;
                                   inv=1;}

                 } while (inv==1);

                for (k1=1;k1<K;k1++)
                     if (b[k1]!=b[k1+1]-1) cool=0;
                if (cool==1)
                    {

                    }

             }

    }

    return 0;
}
