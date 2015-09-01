#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 30011

int n,m,A,i,j;
int line[maxN];
int column[maxN];
long long ans_area,ans_count;

int cc[2];
int aux_l[maxN];
int aux_c[maxN];


void Check(long long val_,int count_) {
    if (ans_area == val_) {
        ans_count += 1LL*count_;
    } else
    if (ans_area <  val_) {
        ans_count = count_;
        ans_area = val_;
    }
}



void Try(int dim_n,int dim_m) {
    int i ;
    cc[0] = cc[1] = 1;
    aux_l[1] = aux_c[1] = 0;

    for (i = 1; i <= dim_n; i++) aux_l[1] += line[i];
    for (i = dim_n+1; i <= n; i++) {
        aux_l[ cc[0] + 1 ] = aux_l[ cc[0] ];
        cc[0]++;

        aux_l[ cc[0] ] += line[i];
        aux_l[ cc[0] ] -= line[i-dim_n];
    }

    for (i = 1; i <= dim_m; i++) aux_c[1] += column[i];
    for (i = dim_m+1; i <= m; i++) {
        aux_c[ cc[1] + 1 ] = aux_c[ cc[1] ];
        cc[1]++;

        aux_c[ cc[1] ] += column[i];
        aux_c[ cc[1] ] -= column[i-dim_m];
    }

    //! ------------------------------------------
    int a_max = 0;
    int a_max_c = 0;

    for (i = 1; i <= cc[0]; i++) {
        if (aux_l[i] == a_max) {
            a_max_c++;
        } else
        if (aux_l[i] >  a_max) {
            a_max_c = 1;
            a_max = aux_l[i];
        }
    }

    int a_min = maxN;
    int a_min_c = 0;

    for (i = 1; i <= cc[0]; i++) {
        if (aux_l[i] == a_min) {
            a_min_c++;
        } else
        if (aux_l[i] <  a_min) {
            a_min_c = 1;
            a_min = aux_l[i];
        }
    }

    //if (a_min == a_max) a_min_c = 0;

    //! ---------------------------------------

    for (i = 1; i <= cc[1]; i++) {
        //! maxim - N*M + 2*a1*a2 - a1*M - a2*N
        int a2 = aux_c[i];
        int a1;
        long long act;

        if (2*a2 == dim_m) { //! calcule..
            a1 = a_min;
            act = 1LL * dim_n * dim_m + 2LL * a1 * a2 - 1LL * a1 * dim_m - 1LL * a2 * dim_n;
            Check(act,cc[0]);

        }
        if (2*a2 < dim_m) {
            a1 = a_min;
            act = 1LL * dim_n * dim_m + 2LL * a1 * a2 - 1LL * a1 * dim_m - 1LL * a2 * dim_n;
            Check(act,a_min_c);
        }
        if (2*a2 > dim_m) {
            a1 = a_max;
            act = 1LL * dim_n * dim_m + 2LL * a1 * a2 - 1LL * a1 * dim_m - 1LL * a2 * dim_n;
            Check(act,a_max_c);
        }

    }
}

int main()
{
    freopen("matrice.in","r",stdin);
    freopen("matrice.out","w",stdout);

    scanf("%d%d%d",&n,&m,&A);
    for (i = 1; i <= n; i++) {
        scanf("%d",&line[i]);
        line[i] = !line[i];
    }
    for (i = 1; i <= m; i++) {
        scanf("%d",&column[i]);
        column[i] = !column[i];
    }

    for (i = 1; i <= n; i++) {
        if (A % i != 0) continue;

        int dim_n = i;
        int dim_m = A/dim_n;

        if (dim_m > m) continue;

        Try(dim_n,dim_m);
    }

    printf("%lld %lld",ans_area,ans_count);

    return 0;
}
