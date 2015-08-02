#include <fstream>
#include <string>
#include <set>

using namespace std;

ifstream f("subsecvente.in");
ofstream g("subsecvente.out");

const int MAX_N = 7;

int n, rez;
string s[MAX_N], p, q;
set <string> S[MAX_N];

void read() {
    f >> n;
    for (int i = 1; i <= n; i++)
        f >> s[i];
}

/*int check(int ind, int lungime) {
    q.clear();
    for (int j = 0; j <= s[ind].size() - lungime; j++) {
        for (int k = 1; k <= lungime; k++)
            q.push_back(s[ind][j + k - 1]);
        if (p == q)
            return 1;
        q.clear();
    }
    return 0;
}

void solve() {
    p.clear();
    for (int i = 1; i <= s[1].size() && i <= 60; i++) // lungimea unei subsecvente
        for (int j = 0; j <= s[1].size() - i; j++) {         // de unde incepe subsecventa
            for (int k = 1; k <= i; k++)
                p.push_back(s[1][j + k - 1]);

            int ok = 1;
            for (int x = 2; x <= n && ok; x++)
                ok = ok & check(x, i);

            if (ok) {
                rez = max(rez, i);
                j = s[1].size();
            }

            p.clear();
        }
}*/

void solve() {
    for (int ind = 1; ind <= n; ind++)
        for (int i = 1; i <= s[ind].size() && i <= 60; i++)
            for (int j = 0; j <= s[ind].size() - i; j++) {
                for (int k = 1; k <= i; k++)
                    p.push_back(s[ind][j + k - 1]);
                S[ind].insert(p);
                p.clear();
            }

    for (int i = 1; i <= s[1].size() && i <= 60; i++)
        for (int j = 0; j <= s[1].size() - i; j++) {
            for (int k = 1; k <= i; k++)
                p.push_back(s[1][j + k - 1]);

            int ok = 1;
            for (int ind = 2; ind <= n && ok; ind++) {
                if ( !(S[ind].find(p) != S[ind].end()) )
                    ok = 0;
            }

            if (ok) {
                rez = max(rez, i);
                j = s[1].size();
            }

            p.clear();
        }

}

int main() {
    read();
    solve();

    g << rez << '\n';

    f.close();
    g.close();

    return 0;
}
