/**
 * Problema: Sipet O( N )
 * Stud. Popescu Silviu Emil
 *    Automatica si Calculatoare
 *    Universitatea Politehnica Bucuresti
 */

#include <stdio.h>
#include <assert.h>
#define NMax 10000010

const char IN[] = "sipet.in", OUT[] = "sipet.out";

struct pereche {
    int a, b;
};

int Tes, N, L, p[4];
int A, B, C, R;
pereche v[NMax];
bool bb[NMax];

bool isPrime( int x ) {

    for ( int d = 2; d * d <= x; ++ d )
        if ( x % d == 0 )
            return false;
    return true;

}

int sqr( int x ) {
    return x * x;
}

int main() {

    freopen(IN, "r", stdin);
    freopen(OUT, "w", stdout);

    scanf("%d", &Tes);

    while ( Tes -- ) {

        scanf("%d%d", &N, &p[1]);

        assert(isPrime(p[1]));
        for ( int i = 2; i <= 3; ++ i )
            for ( p[i] = p[i - 1] + 1; !isPrime(p[i]); ++ p[i] );

       // fprintf(stderr, "%d %d %d\n", p[1], p[2], p[3]);
        for ( int a = 0; a * p[1] <= N; ++ a )
            for ( int b = 0; a * p[1] + b * p[2] <= N && b < p[1]; ++ b ) {
                int pos = a * p[1] + b * p[2];
                v[pos].a = a;
                v[pos].b = b;
                bb[pos] = true;
            }

        bool found = false; R = -1;
        for ( int r = 0; r <= p[1] && R == -1; ++ r )
            for ( int c = 0; r + c * p[3] <= N && c <= p[1]; ++ c ) {
                int pos = c * p[3] + r;
                if ( bb[N - pos] && (R == -1 || R != -1 && A + B + C < v[N - pos].a + v[N - pos].b + c )) {
                    found = true;
                    A = v[N - pos].a;
                    B = v[N - pos].b;
                    C = c;
                    R = r;
                }
            }

        for ( int a = 0; a * p[1] <= N; ++ a )
            for ( int b = 0; a * p[1] + b * p[2] <= N && b < p[1]; ++ b ) {
                int pos = a * p[1] + b * p[2];
                bb[pos] = false;
            }

        printf("%d %d %d %d %d\n", A + B + C, A, B, C, R);

    }

    return 0;
}
