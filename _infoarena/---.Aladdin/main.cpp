#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1024

class SAT {
    public:
        vector<int> state;
        bool all_good;

        void init(int _n) {
            n = _n; dim = 2 * n + 3;
            list = vector< vector<int> >(dim, vector<int>(0, 0));
            state = vector<int>(dim, -1);
            all_good = false;
        }

        void add_relation(int a, int b) {
            // use -a/-b if you want to use non a
            if (a < 0) a = inv(-a);
            if (b < 0) b = inv(-b);

            list[inv(a)].pb(b);
            list[inv(b)].pb(a);
        }

        bool solve() {
            int i;

            us = vector<bool>(dim, false);
            rev = vector< vector<int> >(dim, vector<int>(0, 0));
            comp.clear();
            while (!S.empty()) S.pop();

            //! build reversed list
            for (i = 1; i <= 2 * n; i++)
                for (int to : list[i])
                    rev[to].pb(i);

            //! step one in strong connected
            for (i = 1; i <= 2 * n; i++)
                if (us[i] == false)
                    dfs(i);

            //! step two in strong connected
            while (!S.empty()) {
                int node = S.top(); S.pop();
                if (us[node] == false) continue;

                aux.clear();
                dfs_rev(node);
                comp.pb(aux);
            }

            //! start solving
            for (i = 0; i < comp.size(); i++) {
                aux = comp[i];

                int need = get_color();
                if (need == -2) {
                    all_good = false;
                    return false;
                }

                if(set_color(need) == false) {
                    all_good = false;
                    return false;
                }
            }

            return true;
        }

    private:
        int n, dim, i;
        vector< vector<int> > list;

        vector<bool> us;
        vector< vector<int> > rev;
        vector< vector<int> > comp;
        vector<int> aux;
        stack<int> S;



        int inv(int a) {
            if (a <= n) return a + n;
            return a - n;
        }

        void dfs(int node) {
            us[node] = true;
            for (int to : list[node])
                if (!us[to])
                    dfs(to);

            S.push(node);
        }

        void dfs_rev(int node) {
            us[node] = false;
            aux.pb(node);

            for (int to : rev[node])
                if (us[to])
                    dfs_rev(to);
        }

        int get_color() {
            int i;

            int act = -1;
            for (int node : aux) {
                if (state[node] == -1) continue;
                if (act != -1 && act != state[node]) return -2; //! error
                act = state[node];
            }

            if (act == -1) act = 0;
            return act;
        }

        bool set_color(int col) {
            for (int node : aux) {
                if (state[node] != -1) {
                    if (state[node] != col) return false;
                    continue;
                }

                state[node] = col;
                state[inv(node)] = (col == 0 ? 1 : 0);
            }

            if (col == 0) return true;

            //! force other nodes
            for (int node : aux) {
                for (int to : list[node]) {
                    if (state[to] == 0) return false;
                    state[to] = 1;

                    if (state[inv(to)] == 1) return false;
                    state[inv(to)] = 0;
                }
            }

            return true;
        }
};

int n, m, i, j;
int mat[maxN][maxN], rez[maxN][maxN];
int sol[maxN][maxN];
SAT work;

int main()
{
    freopen("aladdin.in","r",stdin);
    freopen("aladdin.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i < n; i++) {
        for (j = 1; j < m; j++) {
            scanf("%d", &mat[i][j]); rez[i][j] = mat[i][j];
            if (i % 2 != j % 2) mat[i][j] = -mat[i][j];
            mat[i][j] += mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1];
        }
    }

    if (n == 1 || m == 1) {
        for (i = 0; i < n; i++, printf("\n"))
            for (j = 0; j < m; j++)
                printf("%d ", sol[i][j]);
        return 0;
    }

    for (sol[0][0] = 0; sol[0][0] < 2; sol[0][0]++) {
        work.init(n + m - 2);

        for (i = 1; i < n; i++) {
            for (j = 1; j < m; j++) {
                int cst = (i % 2 == j % 2 ? mat[i][j] - sol[0][0] : -mat[i][j] + sol[0][0]);
                int sg1 = (j % 2 == 0 ? +1 : -1);
                int sg2 = (i % 2 == 0 ? +1 : -1);

                for (int b1 = 0; b1 < 2; b1++) {
                    for (int b2 = 0; b2 < 2; b2++) {
                        int act = cst + sg1 * b1 + sg2 * b2;

                        if (act < 0 || act > 1)
                            work.add_relation( (i) * (b1 ? -1 : 1) , (n - 1 + j) * (b2 ? -1 : 1) );
                    }
                }
            }
        }

        if (work.solve() == true) {
            //! and nothing else matters...

            for (i = 1; i < n; i++) sol[i][0] = work.state[i];
            for (j = 1; j < m; j++) sol[0][j] = work.state[n - 1 + j];

            for (i = 1; i < n; i++)
                for (j = 1; j < m; j++)
                    sol[i][j] = rez[i][j] - sol[i - 1][j] - sol[i][j - 1] - sol[i - 1][j - 1];

            for (i = 0; i < n; i++, printf("\n"))
                for (j = 0; j < m; j++)
                    printf("%d ", sol[i][j]);

            return 0;
        }
    }

    printf("-1");
    cerr << "You are not lucky..";

    return 0;
}
