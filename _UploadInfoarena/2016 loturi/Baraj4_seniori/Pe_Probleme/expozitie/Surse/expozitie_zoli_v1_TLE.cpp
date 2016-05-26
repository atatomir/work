//szabo zoltan liceul tehnologic "petru maior" reghin
#include <fstream>

using namespace std;
ifstream fin("expozitie.in");
ofstream fout("expozitie.out");
    int c[1000000],k,x[1000],n,q,y,i,kk,s,t,sum;
int main()
{

    fin>>n>>q>>y;
    for (i=1;i<=n;++i)
    {
        fin>>x[i];
        sum+=x[i];
    }
    if (sum>=y)
    {
        c[0]=0;k=0;
        do
        {
            k++;
            if (k%(n+1)==1)
                c[k]=c[k-1]+y;
            else
            {
                kk=(k-1) % (n+1);
                c[k]=c[k-1]>=x[kk]?c[k-1]-x[kk]:c[k-1];
            }

        }while (c[k] or k%(n+1));
    //    for (i=1;i<=k;++i)
    //        fout<<c[i]<<" ";
        for (i=1;i<=q;++i)
        {
            fin>>t>>s;
            if (t<=n)
                if (s>t or s==0)
                    fout<<0<<"\n";
                else
                    fout<<c[s]<<"\n";
            else
            {
                t=t%k;
                while (s!=t%(n+1))
                {
                    t--;
                    if (t<0) t=t+k;
                }
                fout<<c[t]<<"\n";
            }
        }
    }
    else
    {
        c[1]=y;
        for (i=2;i<=n;i++)
            c[i]=c[i-1]-x[i-1];
        kk=c[n]-x[n];
        for (i=1;i<=q;++i)
        {
            fin>>t>>s;
            if ((t<=n) and (s>t or s==0))
                fout<<0<<"\n";
            else
            {
                while (s!=t%(n+1))
                {
                    t--;
                    if (t<0) t=t+n+1;
                }
                fout<<(t/(n+1))*kk+c[s]<<"\n";

            }
        }
    }
    return 0;
}
