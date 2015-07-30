// Marius Nicoli
#include <stdio.h>

#define DIM 100010
#define INF (1LL<<40)

struct nod {
    long long h;
    long long p;
};

struct nod1 {
    long long a;
    long long P;
    long long h;
    long long w;
    long long H;
};

using namespace std;

long long v[DIM];
nod s[DIM];
nod1 sol[DIM];

long long n, i, k, m, q, p, u, mid, x, rest, T;

int main() {
	
	freopen("atlas.in", "r", stdin);
	freopen("atlas.out", "w", stdout);
	
    scanf("%lld", &T);
    
    for(;T--;) {
		
		m = 0;
		
        scanf("%lld", &n);
        for (i=1;i<=n;i++)
			scanf("%lld", &v[i]);
        v[n+1] = INF-1;

        k = 1;
        s[1].p = 0;
        s[1].h = INF;

        for (i=1;i<=n+1;i++) {
            //s[k+1].h = s[k].h;
            if (v[i] < s[k].h) {
                k++;
                s[k].h = v[i];
                s[k].p = i;
                continue;
            }
            while (k>0 && v[i] >= s[k].h) {
                k--;

                if (v[i] >= s[k].h && (i-s[k].p-1) * (s[k].h - s[k+1].h) !=0) {
                    m++;
                    sol[m].a = sol[m-1].a + (i-s[k].p-1) * (s[k].h - s[k+1].h);
                    sol[m].P = i-1;
                    sol[m].w = (i-s[k].p-1);
                    sol[m].h = (s[k].h - s[k+1].h);
                    sol[m].H = s[k+1].h+1;
                }
            }
            if  ((i-s[k].p-1) * (v[i] - s[k+1].h) != 0) {
                m++;
                sol[m].a = sol[m-1].a + (i-s[k].p-1) * (v[i] - s[k+1].h);
                sol[m].P = i-1;
                sol[m].w = (i-s[k].p-1);
                sol[m].h = (v[i] - s[k+1].h);
                sol[m].H = s[k+1].h+1;
            }
            k++;
            s[k].h = v[i];
            s[k].p = i;
        }

    //    for (i=1;i<=m;i++)
    //        fdbg<<sol[i].a<<" "<<sol[i].P<<" "<<sol[i].H<<" "<<sol[i].w<<" "<<sol[i].h<<"\n";

        scanf("%lld", &q);
        for (;q--;) {
            scanf("%lld", &x);
            p = 1;
            u = m;
            while (p <= u) {
                mid = (p+u)/2;
                if (sol[mid].a < x)
                    p = mid+1;
                else
                    u = mid-1;

            }
            //fdbg<<x<<" "<<sol[p].a<<"\n";
            rest = x - sol[p-1].a;

            //fout<<sol[p].P<<" "<<sol[p].H-1 + (rest*1.0)/sol[p].w<<"\n";
            long long numarator = (sol[p].H-1) * sol[p].w + rest;
            long long numitor = sol[p].w;

            long long r, x = numarator, y = numitor;
            while (y) {
                r = x % y;
                x = y;
                y = r;
            }

            //fout<<sol[p].P<<" "<<numarator/x<<"/"<<numitor/x<<"\n";
            printf("%lld %lld/%lld\n", sol[p].P, numarator / x, numitor / x);

        }

    }
    return 0;
}
