#include <fstream>
#include <vector>

#define DIM 2010
#define INF DIM*1000

using namespace std;

vector < pair<int, int> >L[DIM];
int D[DIM], V[DIM], P[DIM], H[DIM], S[DIM], T[DIM], F[DIM];


int n, m, dH, x, y, k, aux, i, c, inHeap;

ifstream fin("dbz.in");
ofstream fout("dbz.out");

void stergeRad() {
    H[1] = H[dH--];
    P[H[1]] = 1;

    int p = 1, c = 2;
    while (c <= dH) {
        if (c + 1 <= dH && D[ H[c+1] ] < D[ H[c] ])
            c++;

        if (D[ H[p] ] > D[ H[c] ]) {
            aux = H[p];
            H[p] = H[c];
            H[c] = aux;
            P[ H[p] ] = p;
            P[ H[c] ] = c;
            p = c;
            c = (p<<1);
        } else
            break;
    }
}

void urca(int poz) {
    int c = poz, p = c/2;
    while (p != 0 && D[ H[c] ] < D[ H[p] ]) {
        aux = H[c];
        H[c] = H[p];
        H[p] = aux;
        P[H[p]] = p;
        P[H[c]] = c;
        c = p;
        p = (c>>1);
    }
}

void citire() {
    fin>>n>>m;
    for (i=1;i<=m;i++) {
        fin>>x>>y>>c;
        L[x].push_back(make_pair(y,c));
        L[y].push_back(make_pair(x,c));
    }

}

void dijkstra(int start) {

    S[start] = INF;

    int i;
    for (i=1;i<=n;i++) {
        D[i] = INF;
        T[i] = 0;
        F[i] = 0;
    }
    D[start] = 0;

    H[1] = start;
    P[start] = 1;
    dH = 1;
    while (dH) {
        k = H[1];
        stergeRad();

        V[k] = 1;

        for (i=0;i<L[k].size(); i++) {

            if (V[ L[k][i].first ] == 1 && F[k] != F[ L[k][i].first ] && k!=start && L[k][i].first != T[k]) {
                S[start] = min(S[start], D[k] + D[ L[k][i].first ] + L[k][i].second);

            }

            x = L[k][i].first;
            if (D[x] > D[k] + L[k][i].second) {
                inHeap = (D[x] != INF);
                D[x] = D[k] + L[k][i].second;
                T[x] = k;
                if (k == start) {
                    F[x] = x;
                } else
                    F[x] = F[ k ];

                if (inHeap)
                    urca( P[x] );
                else {
                    dH ++;
                    H[dH] = x;
                    P[x] = dH;
                    urca(dH);
                }
            }
        }

    }

/*
    for (i=2;i<=n;i++)
        if (D[i] == INF)
            fout<<"0 ";
        else
            fout<<D[i]<<" ";
*/

}

int main() {
    citire();

    for (i=1;i<=n;i++) {
        dijkstra(i);
        if (S[i] == INF)
            fout<<"-1 ";
        else
            fout<<S[i]<<" ";
    }


    return 0;
}
