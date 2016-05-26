// Marius Nicoli
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("atlas.in");
ofstream fout("atlas.out");

#define DIM 100010
#define INF (1LL<<40)

struct nod {
    long long nr;
    long long p;
    long long numarator, numitor;
    long long pz;
};

nod w[DIM];
long long v[DIM];

long long n, i, c, q, j, L, h, m, aria, x, T;

int cmp1(nod a, nod b) {
    return a.nr < b.nr;
}

int cmp2(nod a, nod b) {
    return a.p < b.p;
}

int main() {

    fin>>T;
    for (;T--;) {
        c = 0;
        L = 0;
        aria = 0;
        fin>>n;
        v[0] = INF;
        for (i=1;i<=n;i++) {
            fin>>v[i];
        }
        v[n+1] = INF;

        fin>>q;
        for (i=1;i<=q;i++) {
            fin>>w[i].nr;
            w[i].p = i;
        }

        sort(w+1, w+q+1, cmp1);

        c = 1;
        for (i=1;i<=n+1;i++) {
            if (v[i] < v[i-1]) {
                continue;
            }

            if (v[i] == v[i-1]) {
                continue;
            }

            while (v[i] > v[i-1]) {
                L=0;
                j = i-1;
                while (v[i-1] == v[j]) {
                    L++;
                    j--;
                }

                j = i-L-1;
                m = min(v[i], v[j]);
                h = m - v[i-1];
                aria += L*h;

                while (w[c].nr <= aria && c <= q) {

                    x = w[c].nr - (aria - L*h);

    //                w[c].sol =  + x*1.0/L;


                    long long numarator = v[i-1] * L + x;
                    long long numitor = L;

                    long long r, xx = numarator, yy = numitor;
                    while (yy) {
                        r = xx % yy;
                        xx = yy;
                        yy = r;
                    }

                    w[c].numarator = numarator / xx;
                    w[c].numitor = numitor / xx;

                    w[c].pz = i-1;
                    c++;
                }

                for (++j;j<i;j++)
                    v[j] += h;


                if (c > q)
                    break;
            }

            //L++;

            if (c > q)
                break;

        }

        sort(w+1, w+q+1, cmp2);

        for(i=1;i<=q;i++)
            fout<<w[i].pz<<" "<<w[i].numarator<<"/"<<w[i].numitor<<"\n";

    }
    return 0;
}
