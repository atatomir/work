    #include <cstdlib>
    #include <algorithm>
    #include <cstdio>
    #define MAX_DIGITS 66000
    using namespace std;
    void gradeSchool(int *a, int *b, int *ret, int d) {
        int i, j;
        for(i = 0; i < 2 * d; i++) ret[i] = 0;
        for(i = 0; i < d; i++)
            for(j = 0; j < d; j++) ret[i + j] += a[i] * b[j];
    }

    void karatsuba(int *a, int *b, int *ret, int d) {
        int i;
        int *ar = &a[0], *al = &a[d/2], *br = &b[0];
        int *bl = &b[d/2], *asum = &ret[d * 5], *bsum = &ret[d * 5 + d/2];
        int *x1 = &ret[d * 0], *x2 = &ret[d * 1], *x3 = &ret[d * 2];
        if(d <= 2) {
            gradeSchool(a, b, ret, d);
            return;
        }
        for(i = 0; i < d / 2; i++) {
            asum[i] = al[i] + ar[i];
            bsum[i] = bl[i] + br[i];
        }

        karatsuba(ar, br, x1, d/2);
        karatsuba(al, bl, x2, d/2);
        karatsuba(asum, bsum, x3, d/2);
        for(i = 0; i < d; i++) x3[i] = x3[i] - x1[i] - x2[i];
        for(i = 0; i < d; i++) ret[i + d/2] += x3[i];
    }
    int a[MAX_DIGITS], b[MAX_DIGITS],r[6 * MAX_DIGITS], d_a, d_b, d;
    int main()
    {
        int T, d, n;
        freopen("bacterii2.in","r",stdin);
        freopen("bacterii2.ok","w",stdout);
        scanf("%d\n",&T);
        while(T--){
            d_a = d_b = 0;
            for(int j=0;j < MAX_DIGITS; ++j)
                a[j] = b[j] = r[j] = 0;
            scanf("%d\n",&n);
            for(int j=1;j<=n; ++j)
            {
                int x;
                scanf("%d ",&x);
                d_a = max(x,d_a);
                a[x]++;
            }
            scanf("%d\n",&n);
            for(int j=1;j<=n; ++j)
            {
                int x;
                scanf("%d ",&x);
                d_b = max(x,d_b);
                b[x]++;
            }
            ++d_a,++d_b;
            int i = (d_a > d_b) ? d_a : d_b;
            for(d = 1; d < i; d *= 2);
            karatsuba(a, b, r, d);
            for(int j=0;j < 2*d; ++j)
                if(r[j] > 0)
                    printf("%d %d\n",j,r[j]);
            printf("\n");
        }
        return 0;
    }
