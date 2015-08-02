#include <fstream>
#include <algorithm>

using namespace std;

ifstream f("biperm.in");
ofstream g("biperm.out");

const int MAX_N = 10005;

int n, A[5][MAX_N], SOL[5][MAX_N];
int swaps[MAX_N], nrswaps;
int rez, minim = MAX_N;
bool used[MAX_N];

void read() {
    f >> n;
    for (int i = 1; i <= 2; i++)
        for (int j = 1; j <= n; j++)
            f >> A[i][j];
}

int check(int mutari) {
    int ok = 1;
    for (int i = 1; i <= n; i++)
        used[i] = 0;

    for (int i = 1; i <= n; i++)
        if (used[A[1][i]])
            ok = 0;
        else
            used[A[1][i]] = 1;

    if (ok) {
        if (mutari < minim)
            minim = mutari;
    }

    return ok;
}

void solve_bk() {
    const int LIM = (1 << n) - 1;

    for (int i = 0; i <= LIM; i++) {
        nrswaps = 0;
        for (int j = 0; (1 << j) <= i; j++) {
            if (i & (1 << j))
                swaps[++nrswaps] = j + 1;
        }

        for (int i = 1; i <= nrswaps; i++)
            swap(A[1][swaps[i]], A[2][swaps[i]]);
        if (check(nrswaps) == 1) {
            rez++;
            if (rez == 1) {
                for (int i = 1; i <= 2; i++)
                    for (int j = 1; j <= n; j++)
                        SOL[i][j] = A[i][j];
            }
        }

        for (int i = 1; i <= nrswaps; i++)
            swap(A[1][swaps[i]], A[2][swaps[i]]);
    }

    g << rez << " " << minim << '\n';
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= n; j++)
            g << SOL[i][j] << " ";
        g << '\n';
    }
}

void solve() {
    int cnt = 0;

    for (int i = 1; i <= n; i++)
        if (!used[A[1][i]])
            used[A[1][i]] = 1;
        else
            cnt++;
    minim = cnt;

    g << minim << " " << minim << '\n';
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= n; j++)
            g << j << " ";
        g << '\n';
    }
}


int main() {
    read();

    if (n <= 20)
        solve_bk();
    else
        solve();

    f.close();
    g.close();

    return 0;
}
