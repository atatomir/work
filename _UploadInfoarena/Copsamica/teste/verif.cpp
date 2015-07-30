#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
#include <utility>
#include <vector>

using namespace std;

#define maxn 1010

ifstream fin("copsamica.in");
ifstream fok("copsamica.ok");
ifstream fout("copsamica.out");

int n;
int c[maxn][maxn], rec[maxn][maxn], mn[maxn], mp[maxn], nn[maxn];
vector<int> v[maxn], w[maxn];

void Msg(int pct, string msg)
{
    cout << pct << ' ' << msg;
    try
    {
        fin.close();
        fok.close();
        fout.close();
    }
    catch (string ex) {}
    exit(0);
}

void buildPath(int nod)
{
    int pz=0;

    int prev=nod;
    int cr=v[nod][0];
    int cc=w[nod][0];

    while(cr!=nod)
    {
        nn[++pz]=cr;
        mn[pz]=cc;
        if(v[cr][0]==prev)
        {
            prev=cr;
            cc=w[cr][1];
            cr=v[cr][1];
        }
        else
        {
            prev=cr;
            cc=w[cr][0];
            cr=v[cr][0];
        }
    }
    nn[++pz]=cr;
    mn[pz]=cc;

    if(pz<n)
        Msg(0, "Reteaua nu are forma ciclica!");

    mp[1]=mn[1];
    for(int i=2; i<=n; ++i)
        mp[i]=min(mn[i], mp[i-1]);

    int mcr=mn[n];

    for(int i=n-1; i>=1; --i)
    {
        rec[nod][nn[i]]=mp[i]+mcr;
        mcr=min(mcr, mn[i]);
    }
}

int checkSolution()
{
    for(int i=1; i<=n; ++i)
        if(v[i].size()!=2)
            Msg(0, "Reteaua nu are forma ciclica!");

    for(int i=1; i<=n; ++i)
        buildPath(i);

    for(int i=1; i<=n; ++i)
        for(int j=1; j<=n; ++j)
            if(rec[i][j]!=c[i][j])
                return 0;

    return 1;
}

void eval(int test)
{
    int csol, sol;
    fin>>n;
    for(int i=1; i<=n; ++i) 
        for(int j=i+1; j<=n; ++j) {
            fin>>c[i][j];
            c[j][i] = c[i][j];
        }
    
    int a, b, c;
    for(int i=1; i<=n; ++i)
    {
        fok>>a>>b>>c;
        v[i].clear();
        w[i].clear();
    }

    for(int i=1; i<=n; ++i)
    {
        if(!(fout>>a))
            Msg(0, "Fisier de iesire corupt!");

        if(a<1 || a>n)
            Msg(0, "Incorect!");

        if(!(fout>>b))
            Msg(0, "Fisier de iesire corupt!");

        if(b<1 || b>n)
            Msg(0, "Incorect!");

        if(!(fout>>c))
            Msg(0, "Fisier de iesire corupt!");

        if(c<0 || c>20000)
            Msg(0, "Cost in afara intervalului!");

        v[a].push_back(b);
        v[b].push_back(a);
        w[a].push_back(c);
        w[b].push_back(c);
    }

    if(!checkSolution())
        Msg(0, "Incorect!");
}


int main()
{
    if(!fout)
        Msg(0, "Fisier de iesire lipsa!");

    int tt;

    fin>>tt;

    for(int i=1; i<=tt; ++i)
        eval(i);

    Msg(10, "OK!");
	return 0;
}
