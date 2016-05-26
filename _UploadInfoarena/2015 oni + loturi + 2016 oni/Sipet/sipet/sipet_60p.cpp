///prof. Gorea Claudiu-Cristian
///Colegiul National Al. Papiu Ilarian Tg-Mures

#include <fstream>

using namespace std;
ifstream fin ("sipet.in");
ofstream fout("sipet.out");
int n,i,j,p1,p2,p3,t1,t2,t3,s1,s2,rest,smax,rmax,v1,v2,v3,stop,r,k;


int prim(int x)
{
    int d=2;
    while(d*d<=x)
        if (x%d==0) return 0;
        else d++;
    return 1;
}
int main()
{
    int t,teste;
fin>>teste;
for(t=1;t<=teste;t++)
{
    fin>>n>>p1;
    while(prim(p1)==0) p1++;
    p2=p1+1;
    while(prim(p2)==0) p2++;
    p3=p2+1;
    while(prim(p3)==0) p3++;
    smax=0; rmax=0;
    stop=0;
    //fout<<p1<<' '<<p2<<' '<<p3<<endl;
    for(r=0;r<p1 && stop==0;r++)
    {
       t1=(n-r)/p1;
       for(i=t1;i>=0 && stop==0;i--)
       {
        s1=i*p1;     ///suma1
        t2=(n-r-s1)/p2;
        for(j=t2;j>=0 && stop==0;j--)
        {
            s2=j*p2;  ///suma2
       //     fout<<r<<' '<<i<<' '<<j<<endl;
            k=(n-r-s1-s2)/p3;
            rest=(n-r-s1-s2)%p3;
            if(rest==0 && i+j+k>smax)
            {
                stop=1;
                v1=i;
                v2=j;
                v3=k;
                smax=v1+v2+v3;
                rmax=r;
            }
        }
    }
}
    fout<<smax<<' '<<v1<<' '<<v2<<' '<<v3<<' '<<rmax<<endl;
}
    return 0;
}
