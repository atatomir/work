#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >
#define steps 41
#define eps 0.0001

#define maxN 50011

int n,i;
double L;
double a[maxN],b[maxN],k[maxN],q[maxN],v[maxN];
int ind[maxN];
vector<double> ans;

double coef,cons;

bool cmp(int a,int b){
    return v[a] < v[b];
}

bool Equal(double a,double b){
    a = a-b; if(a<0) a = -a;
    return (a<=eps);
}

double BinarySearch(double l,double r){
    double mid;
    int lim = steps;

    while(lim--){
        mid = (l+r)/2.00;
        double vv = coef*mid+cons;

        if(L < vv) r = mid;
        else       l = mid;
    }
    return (l+r)/2.00;
}

double revBinarySearch(double l,double r){
    double mid;
    int lim = steps;

    while(lim--){
        mid = (l+r)/2.00;
        double vv = coef*mid+cons;

        if(L > vv) r = mid;
        else       l = mid;
    }
    return (l+r)/2.00;
}

int main()
{
    freopen("xmoto.in","r",stdin);
    freopen("xmoto.out","w",stdout);

    scanf("%d %lf",&n,&L);
    fordef(i,1,n) scanf("%lf%lf%lf%lf%lf",&a[i],&b[i],&k[i],&q[i],&v[i]);

    fordef(i,1,n) ind[i]=i;
    sort(ind+1,ind+n+1,cmp);
    ind[n+1] = n+1;
    v[n+1] = 10000.00;

    fordef(i,1,n){
        coef += a[i];
        cons += k[i];
    }

    fordef(i,0,n){
        double val;
        if(coef > 0){
        /**/  val = BinarySearch(v[ind[i]]+eps,v[ind[i+1]]);
        if(Equal(val*coef+cons,L)) ans.pb(val);
        } else {
        /**/  val = revBinarySearch(v[ind[i]]+eps,v[ind[i+1]]);
        if(Equal(val*coef+cons,L)) ans.pb(val);
        }

        coef -= a[ind[i+1]];   cons -= k[ind[i+1]];
        coef += b[ind[i+1]];   cons += q[ind[i+1]];
    }

    printf("%d\n",ans.size());
    foreach(ans) printf("%.6lf\n",*it);

    return 0;
}
