#include <fstream>
#include <vector>

using namespace std;
ifstream f("expozitie.in");
ofstream g("expozitie.out");
void sol1(),sol2(),sol3();
int n,q,y,i,d[1010],s,Nr,P,C,T,M,R;
vector<int>S;
int main()
{
    f>>n>>q>>y;
    for(i=1;i<=n;i++)
    {
        f>>d[i];
        s+=d[i];
    }
    if(s>y)sol1();
    if(s==y)sol2();
    if(s<y)sol3();
    return 0;
}
void sol1()
{
    S.push_back(0);Nr=0;
    for(P=1,C=0;;P++)
    {
        if(C==0)
            Nr+=y;
        else
            if(Nr>=d[C])
                Nr-=d[C];
        C=C<n?C+1:0;
        if(C+Nr==0)
            break;
        S.push_back(Nr);
    }
    P=S.size();
    for(;q;q--)
    {
        f>>T>>C;
        M=(T-C+n+1)%(n+1);
        T=T-M;
        if(T<=0){ g<<"0\n";continue;}
        g<<S[T%P]<<"\n";
    }
}
void sol2()
{
    S.push_back(0);
    S.push_back(y);
    for(T=1;T<n;T++)
    {
        y-=d[T];
        S.push_back(y);
    }
    P=n+1;
    for(;q;q--)
    {
        f>>T>>C;
        M=(T-C+n+1)%(n+1);
        T=T-M;
        if(T<=0){ g<<"0\n";continue;}
        g<<S[T%P]<<"\n";
    }
}
void sol3()
{
    S.push_back(0);
    S.push_back(y);
    R=y-s;P=n+1;
    for(T=1;T<n;T++)
    {
        y-=d[T];
        S.push_back(y);
    }
    for(;q;q--)
    {
        f>>T>>C;
        M=(T-C+n+1)%(n+1);
        T=T-M;
        if(T<=0){ g<<"0\n";continue;}
        g<<R*(T/(n+1))+S[T%P]<<"\n";
    }
}
