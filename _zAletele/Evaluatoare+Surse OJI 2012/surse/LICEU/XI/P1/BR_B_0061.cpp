#include<fstream>

using namespace std;

ifstream in("biperm.in");
ofstream out("biperm.out");
struct biperm
{
    int x,y;
}v[10001];
int n,s[10001],aux,k;
long nr;
int main()
{
    in>>n;
    for (int i=1;i<=n;i++)
        in>>v[i].x;
    for (int i=1;i<=n;i++)
        in>>v[i].y;
    for (int i=1;i<=n;i++)
        s[v[i].x]++;
    for (int i=1;i<=n;i++)
        if (s[v[i].x]==1 && v[i].x!=v[i].y)
            k=1;
    for (int i=1;i<=n;i++)
        if (s[v[i].x]==2)
        {
            nr++;
            s[v[i].x]=1;
        }
    for (int i=1;i<=n;i++)
        if (s[v[i].x]==2)
            {
                s[v[i].x]=1;
                aux=v[i].x;
                v[i].x=v[i].y;
                v[i].y=aux;
            }
    if (nr>0)
        out<<2*nr*(k+1)<<" "<<nr<<'\n';
    else
        out<<"1"<<'\n';

    for (int i=1;i<=n;i++)
        out<<v[i].x<<" ";

    out<<'\n';

    for (int i=1;i<=n;i++)
        out<<v[i].y<<" ";

    in.close();
    out.close();
    return 0;
}
