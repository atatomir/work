#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

#define maxn 200010

int n, m, r;
int g[maxn], x[maxn], y[maxn], elim[maxn];
int viz[maxn], cuplaj[maxn], cuplat[maxn];
vector<int> v[maxn];
vector<pair<int, int> > sol;

int cupleaza(int nod)
{
    int vecin;
    if(viz[nod])
        return 0;

    viz[nod]=1;
    for(int i=0; i<v[nod].size(); ++i)
    {
        vecin=y[v[nod][i]];
        if(!cuplaj[vecin])
        {
            cuplat[nod]=1;
            cuplaj[vecin]=nod;
            return 1;
        }
    }

    for(int i=0; i<v[nod].size(); ++i)
    {
        vecin=y[v[nod][i]];
        if(cuplaj[vecin]!=nod)
        {
            if(cupleaza(cuplaj[vecin]))
            {
                cuplat[nod]=1;
                cuplaj[vecin]=nod;
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    freopen("ar.in", "r", stdin);
    freopen("ar.out", "w", stdout);

    scanf("%d%d%d", &n, &m, &r);

    for(int i=1; i<=m; ++i)
    {
        scanf("%d%d", &x[i], &y[i]);

        ++g[x[i]];
        ++g[y[i]];
    }

    for(int i=1; i<=m; ++i)
    {
        if(g[x[i]]==r && g[y[i]]==r)
        {
            elim[i]=1;
            --g[x[i]];
            --g[y[i]];
        }
    }

    for(int i=1; i<=m; ++i)
    {
        if(g[x[i]]<g[y[i]])
            swap(x[i], y[i]);

        if((!elim[i]) && (g[x[i]] == r && g[y[i]] == r-1))
            v[x[i]].push_back(i);
    }

    int ok=1;
    while(ok)
    {
        ok=0;
        memset(viz, 0, sizeof(viz));
        for(int i=1; i<=n; ++i)
            if(!cuplat[i])
            {
                if(cupleaza(i))
                    ok=1;
            }
    }

    for(int i=1; i<=n; ++i)
        if(cuplaj[i]!=0)
            sol.push_back(make_pair(i, cuplaj[i]));

    for(int i=1; i<=m; ++i)
        if(elim[i]==1)
            sol.push_back(make_pair(x[i], y[i]));

    printf("%d\n", sol.size());
    for(int i=0; i<sol.size(); ++i)
        printf("%d %d\n", sol[i].first, sol[i].second);

    return 0;
}
