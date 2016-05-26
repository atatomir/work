#include <cstdio>
#include <tuple>
#include <vector>

using namespace std;

#define maxn 400010
#define mlog 20
#define inf 1000000000

int n, m, nr;
int st[mlog][maxn];
int stk[maxn], st0;
int f[maxn], pz, p[maxn], l[maxn], r[maxn], lvl[maxn];
int aint[8*maxn], lm[8*maxn], rm[8*maxn], sum[8*maxn];
tuple<int, int, int> op[maxn];
vector<int> v[maxn];

void df(int nod)
{
    f[nod]=1;

    lvl[nod]=lvl[st[0][nod]]+1;

    for(int i=1; st[i-1][st[i-1][nod]]!=0; ++i)
        st[i][nod]=st[i-1][st[i-1][nod]];

    p[++pz]=nod;
    l[nod]=pz;

    for(int i=0; i<v[nod].size(); ++i)
    {
        int fiu=v[nod][i];

        if(f[fiu]==1)
            continue;

        st[0][fiu]=nod;
        df(fiu);
    }

    r[nod]=pz;
}

void updateVal(int nod)
{
    sum[nod]=sum[nod*2]+sum[nod*2+1];
    aint[nod]=max(aint[nod*2], aint[nod*2+1]);

    lm[nod]=inf;
    rm[nod]=0;

    for(int i=0; i<2; ++i)
        if(aint[nod*2+i]==aint[nod])
        {
            lm[nod]=min(lm[nod], lm[nod*2+i]);
            rm[nod]=max(rm[nod], rm[nod*2+i]);
        }
}

void build(int nod, int left, int right)
{
    if(left==right)
    {
        if(p[left]<=n)
        {
            sum[nod]=1;
            aint[nod]=lvl[p[left]];
        }

        lm[nod]=rm[nod]=left;
        return;
    }

    int med = (left+right)/2;

    build(nod*2, left, med);
    build(nod*2+1, med+1, right);

    updateVal(nod);
}

void update(int nod, int left, int right, int poz, int val)
{
    if(left==right)
    {
        sum[nod]=val;
        aint[nod]=val*lvl[p[left]];
        lm[nod]=rm[nod]=left*val;
        return;
    }

    int med=(left+right)/2;

    if(poz<=med)
        update(nod*2, left, med, poz, val);
    else
        update(nod*2+1, med+1, right, poz, val);

    updateVal(nod);
}

void getNodes(int nod, int left, int right, int qleft, int qright)
{
    if(qleft<=left && right<=qright)
    {
        stk[++st0]=nod;
        return;
    }

    int med=(left+right)/2;

    if(qleft<=med)
        getNodes(nod*2, left, med, qleft, qright);
    if(med<qright)
        getNodes(nod*2+1, med+1, right, qleft, qright);
}

int lca(int x, int y)
{
    if(x==y)
        return x;

    if(lvl[x]<lvl[y])
        swap(x, y);

    for(int i=mlog-1; i>=0; --i)
        if(lvl[st[i][x]]>=lvl[y])
            x=st[i][x];

    if(x==y)
        return x;

    for(int i=mlog-1; i>=0; --i)
        if(st[i][x]!=st[i][y])
        {
            x=st[i][x];
            y=st[i][y];
        }
    return st[0][x];
}

int query(int nod)
{
    st0=0;
    getNodes(1, 1, n, l[nod], r[nod]);

    int mx=0, sm=0, lmc=inf, rmc=0;

    for(int i=1; i<=st0; ++i)
    {
        sm+=sum[stk[i]];
        if(mx<aint[stk[i]])
        {
            mx=aint[stk[i]];
            lmc=inf;
            rmc=0;
        }

        if(aint[stk[i]]==mx)
        {
            lmc=min(lmc, lm[stk[i]]);
            rmc=max(rmc, rm[stk[i]]);
        }
    }

    int x=p[lmc], y=p[rmc];
    int z=lca(x, y);

    return sm-1-lvl[z]+lvl[nod];
}

int main()
{
    freopen("neapuiu.in", "r", stdin);
    freopen("neapuiu.out", "w", stdout);

    scanf("%d%d", &n, &m);

    for(int i=1; i<n; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        v[a].push_back(b);
        v[b].push_back(a);
    }

    nr=n;

    for(int i=1; i<=m; ++i)
    {
        int t=0, a=0, b=0;

        scanf("%d",  &t);
        if(t==0)
        {
            scanf("%d%d", &a, &b);
            v[a].push_back(b);
            v[b].push_back(a);
            ++nr;
        }
        else
            scanf("%d", &a);

        op[i]=make_tuple(t, a, b);
    }

    df(1);
    build(1, 1, nr);
    n=nr;

    for(int i=1; i<=m; ++i)
    {
        int t=get<0>(op[i]);
        if(t==0)
            update(1, 1, n, l[get<2>(op[i])], 1);
        if(t==1)
            update(1, 1, n, l[get<1>(op[i])], 0);
        if(t==2)
            printf("%d\n", query(get<1>(op[i])));
    }

    return 0;
}
