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

int n, m, i, x, y;
SAT work;

int main()
{
    freopen("2sat.in","r",stdin);
    freopen("2sat.out","w",stdout);

    scanf("%d%d", &n, &m);
    work.init(n);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        work.add_relation(x, y);
    }

    if (work.solve() == false) {
        printf("-1");
        return 0;
    }

    for (i = 1; i <= n; i++) printf("%d ", work.state[i]);


    return 0;
}
