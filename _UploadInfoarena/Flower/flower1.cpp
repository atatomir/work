#include <cstdio>
#include <algorithm>
 
using namespace std;
 
#define maxn 200010
#define inf (1LL*1000000000*1000000000)
 
int n, m, s, tip;
long long st[4*maxn], sl[4*maxn], mn[4*maxn];
int valid[4*maxn];
struct Panta
{
    int pStart, pEnd;
    long long vStart, slope;
    Panta *left, *right;
};
Panta *id[4*maxn];
 
Panta* findId(int nod, int left, int right, int poz)
{
    if(left==right)
        return id[nod];
 
    if(id[nod]!=NULL)
        return id[nod];
 
    int med=(left+right)/2;
 
    if(poz<=med)
        return findId(nod*2, left, med, poz);
    else
        return findId(nod*2+1, med+1, right, poz);
}
 
void updateId(int nod, int left, int right, int uleft, int uright, Panta *val)
{
    if(uleft<=left && right<=uright)
    {
        id[nod]=val;
        return;
    }
 
    if(id[nod]!=NULL)
    {
        id[nod*2]=id[nod*2+1]=id[nod];
        id[nod]=NULL;
    }
 
    int med=(left+right)/2;
 
    if(uleft<=med)
        updateId(nod*2, left, med, uleft, uright, val);
    if(med<uright)
        updateId(nod*2+1, med+1, right, uleft, uright, val);
}
 
void push(int nod, int left, int right, long long vstart, long long slope)
{
    valid[nod]=1;
    st[nod]=vstart;
    sl[nod]=slope;
    mn[nod]=min(vstart, vstart + slope * (right-left));
}
 
void updateValue(int nod, int left, int right, int uleft, int uright, long long vstart, long long slope)
{
    if(uleft<=left && right<=uright)
    {
        push(nod, left, right, vstart + (left-uleft) * slope, slope);
        return;
    }
 
    int med=(left+right)/2;
 
    if(valid[nod])
    {
        push(nod*2, left, med, st[nod], sl[nod]);
        push(nod*2+1, med+1, right, st[nod] + sl[nod] * (med+1-left), sl[nod]);
        valid[nod]=0;
    }
 
    if(uleft<=med)
        updateValue(nod*2, left, med, uleft, uright, vstart, slope);
    if(med<uright)
        updateValue(nod*2+1, med+1, right, uleft, uright, vstart, slope);
 
    mn[nod]=min(mn[nod*2], mn[nod*2+1]);
}
 
void setSlope(Panta *p, Panta *left, Panta *right, int pstart, int pend, long long vstart, long long slope)
{
    p->left = left;
    if(left!=NULL)
        left->right = p;
 
    p->right = right;
    if(right!=NULL)
        right->left = p;
 
    p->pStart = pstart;
    p->pEnd = pend;
    p->vStart = vstart;
    p->slope = slope;
 
    updateId(1, 1, n, pstart, pend, p);
    updateValue(1, 1, n, pstart, pend, p->vStart, p->slope);
}
 
int bsleft(Panta *p, int poz, long long varf, long long panta)
{
    int left = p->pStart, right = p->pEnd, sol=p->pEnd + 1;
 
    while(left<=right)
    {
        int med=(left+right)/2;
        if(varf - panta * (poz - med) >= p->vStart + p->slope * (med - p->pStart))
        {
            sol = med;
            right = med-1;
        }
        else
            left = med+1;
    }
 
    return sol;
}
 
int bsright(Panta *p, int poz, long long varf, long long panta)
{
    int left = p->pStart, right = p->pEnd, sol=p->pStart - 1;
 
    while(left<=right)
    {
        int med=(left+right)/2;
        if(varf - panta * (med - poz) >= p->vStart + p->slope * (med - p->pStart))
        {
            sol = med;
            left = med+1;
        }
        else
            right = med-1;
    }
 
    return sol;
}
 
void addSconcs(int poz, long long varf, long long panta)
{
    Panta *who = findId(1, 1, n, poz);
    if(who == NULL)
    {
        Panta *p = new Panta();
 
        setSlope(p, NULL, NULL, 1, poz, varf - panta * (poz-1), panta);
 
        if(poz<n)
        {
            Panta *r = new Panta();
            setSlope(r, p, NULL, poz+1, n, varf - panta, -panta);
        }
        return;
    }
 
   // printf("%d %d %d\n", who->pStart, poz, who->pEnd);
 
    if(who->vStart + who->slope * (poz - who->pStart) >= varf)
        return;
 
    Panta *nWho;
 
    if(who -> pEnd == poz)
        nWho = who->right;
    else
    {
        nWho = new Panta();
        setSlope(nWho, who, who->right, poz+1, who->pEnd, who->vStart + who->slope * (poz+1 - who->pStart), who->slope);
        who->pEnd = poz;
    }
 
    //stanga
 
    Panta *cr = who;
 
    int pi = 1;
 
    while(cr!=NULL)
    {
        if(varf - panta * (poz - cr->pStart) >= cr->vStart)
            cr = cr->left;
        else
        {
            pi = bsleft(cr, poz, varf, panta);
            cr->pEnd = pi - 1;
            break;
        }
    }
 
    Panta *p = new Panta();
 
    setSlope(p, cr, nWho, pi, poz, varf - panta * (poz-pi), panta);
   // printf("!%d ", pi);
 
    //dreapta
 
    if(nWho == NULL)
        return;
 
    if(nWho->vStart >= varf - panta)
        return;
 
    cr = nWho;
    pi = n;
 
    while(cr!=NULL)
    {
        if(varf - panta * (cr->pEnd - poz) >= cr->vStart + cr->slope * (cr->pEnd - cr->pStart))
            cr = cr->right;
        else
        {
            pi = bsright(cr, poz, varf, panta);
 
            cr->vStart = cr->vStart + cr->slope * (pi + 1 - cr->pStart);
            cr->pStart = pi + 1;
 
            break;
        }
    }
 
    Panta *r = new Panta();
 
 
  //  printf("%d", pi);
 
    setSlope(r, p, cr, poz+1, pi, varf-panta, -panta);
 
 
}
 
long long query(int nod, int left, int right, int qleft, int qright)
{
    if(qleft<=left && right<=qright)
        return mn[nod];
 
    int med=(left+right)/2;
 
    if(valid[nod])
    {
        push(nod*2, left, med, st[nod], sl[nod]);
        push(nod*2+1, med+1, right, st[nod] + sl[nod] * (med+1-left), sl[nod]);
        valid[nod]=0;
    }
 
    long long rez = inf;
 
    if(qleft<=med)
        rez=min(rez, query(nod*2, left, med, qleft, qright));
 
    if(med<qright)
        rez=min(rez, query(nod*2+1, med+1, right, qleft, qright));
 
    mn[nod]=min(mn[nod*2], mn[nod*2+1]);
 
    return rez;
}
 
 
int main()
{
    freopen("flower.in", "r", stdin);
    freopen("flower.out", "w", stdout);
 
    scanf("%d%d", &n, &m);
 
    for(int pas=1; pas<=m; ++pas)
    {
        scanf("%d", &tip);
        if(tip==1)
        {
            int poz;
            long long panta, varf;
 
            scanf("%d%lld%lld", &poz, &varf, &panta);
            addSconcs(poz, varf, panta);
        }
        else
        {
            int l, r;
 
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(1, 1, n, l, r));
        }
    }
 
    return 0;
}
