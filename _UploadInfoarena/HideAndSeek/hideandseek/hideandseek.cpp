#include <cstdio>
#include <algorithm>
#include <vector>
#define ll (long long)
#define nmax 1000100
#define ctg first
#define ind second
#define mp make_pair
using namespace std;

FILE *f,*g;
int n;
long long k1,k2;
int v[nmax];
int p[2][nmax];
int r[nmax];
pair<int,int> wh[nmax];
vector <vector<int>> cyc;


long long d,X,Y;
void extins(long long a,long long b,long long &X ,long long &Y) {
    if (b==0)
    {
        d=a;
        X=1;
        Y=0;
        return ;
    }
    long long X0,Y0;
    extins(b,a%b,X0,Y0);
    X=Y0;
    Y=X0-(a/b)*Y0;
}

void ciclu(int ind , int x)
{
    cyc[cyc.size()-1].push_back(x);
    wh[x].ctg = cyc.size()-1;
    wh[x].ind = cyc[cyc.size()-1].size()-1;

    if (wh[v[x]].ctg == -1)
    {
        ciclu(ind,v[x]);
    }
}


void mult()
{
    for (int i=1;i<=n;i++)
        r[i] = p[0][p[1][i]];
}

void compute(int k, long long A)
{
    int i,size,ct,index;
    long long r;


    for (i=1;i<=n;i++)
    {
        ct = wh[i].first;
        index = wh[i].ind;
        size = cyc[ct].size();

        r =ll ( ll (ll A % size) ) %size;
        r = ll (ll r+index) % size;
        if (r<0) r+=size;
        p[k][i] = cyc[ct][r];
    }
}

int main()
{
    f=fopen("hideandseek.in","r");
    g=fopen("hideandseek.out","w");

    fscanf(f,"%d%lld%lld",&n,&k1,&k2);
    extins(k1,k2,X,Y);

    for (int i=1;i<=n;i++)
    {
        fscanf(f,"%d",&v[i]);
        wh[i].ctg = -1;
    }

    cyc.clear();
    for (int i=1;i<=n;i++)
        if (wh[i].ctg == -1)
            {
                vector <int> ax;
                cyc.push_back(ax);
                ciclu(0,i);
            }
    compute(0,X);


    for (int i=1;i<=n;i++)
    {
        fscanf(f,"%d",&v[i]);
        wh[i].ctg = -1;
    }


   for (int i=1;i<=n;i++)
        if (wh[i].ctg == -1)
        {
            vector <int> ax;
            cyc.push_back(ax);
            ciclu(1,i);
        }
    compute(1,Y);

    mult();

    for (int i=1;i<=n;i++)
        fprintf(g,"%d ",r[i]);

    return 0;
}
