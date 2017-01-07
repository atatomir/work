#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
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
            all_good = true;
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


int n, i;
vector<int> x, y, xx, yy;
SAT work;

int abss(int x) {
    if (x < 0) return -x;
    return x;
}

bool intersect(ll x1, ll y1, ll x2, ll y2, ll dim) {
    x1 *= 2; x2 *= 2, y1 *= 2, y2 *= 2;

    if (x1 > x2) swap(x1, x2), swap(y1, y2);
    if (x1 + dim <= x2 - dim) return false;

    if (y1 > y2) swap(x1, x2), swap(y1, y2);
    if (y1 + dim <= y2 - dim) return false;

    return true;
}

bool check(int dim) {
    int i, j;

    work.init(2 * n);
    for (i = 1; i <= n; i++) {
        work.add_relation(i, n + i);
        work.add_relation(-i, -n - i);
    }

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (intersect(x[i - 1], y[i - 1], x[j - 1], y[j - 1], dim))
                work.add_relation(-i, - j);
            if (intersect(x[i - 1], y[i - 1], xx[j - 1], yy[j - 1], dim))
                work.add_relation(-i, -n - j);
            if (intersect(xx[i - 1], yy[i - 1], x[j - 1], y[j - 1], dim))
                work.add_relation(-n - i, -j);
            if (intersect(xx[i - 1], yy[i - 1], xx[j - 1], yy[j - 1], dim))
                work.add_relation(-n - i, -n - j);
        }
    }

    return work.solve();
}

class ColorfulDecoration {
public:
    int getMaximum( vector <int> xa, vector <int> ya, vector <int> xb, vector <int> yb )  {
        x = xa;
        y = ya;
        xx = xb;
        yy = yb;
        n = x.size();


        int ans = 0;
        for (int step = 1 << 30; step > 0; step >>= 1)
            if (check(ans + step) == true)
                ans += step;


        return ans;
    }

};

// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
			}
			return;
		}

		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}

		if (total == 0) {
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}

	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) {
		std::cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;

		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl;
			std::cerr << "    Received: " << received << std::endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int xa[]                  = { 10, 0, 7 };
			int ya[]                  = { 0, 19, 6 };
			int xb[]                  = { 20, 10, 25 };
			int yb[]                  = { 20, 35, 25 };
			int expected__            = 19;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulDecoration().getMaximum(vector <int>(xa, xa + (sizeof xa / sizeof xa[0])), vector <int>(ya, ya + (sizeof ya / sizeof ya[0])), vector <int>(xb, xb + (sizeof xb / sizeof xb[0])), vector <int>(yb, yb + (sizeof yb / sizeof yb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int xa[]                  = { 464, 20 };
			int ya[]                  = { 464, 10 };
			int xb[]                  = { 464, 3 };
			int yb[]                  = { 464, 16 };
			int expected__            = 461;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulDecoration().getMaximum(vector <int>(xa, xa + (sizeof xa / sizeof xa[0])), vector <int>(ya, ya + (sizeof ya / sizeof ya[0])), vector <int>(xb, xb + (sizeof xb / sizeof xb[0])), vector <int>(yb, yb + (sizeof yb / sizeof yb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int xa[]                  = { 0, 0, 1, 1 };
			int ya[]                  = { 0, 0, 1, 1 };
			int xb[]                  = { 1, 1, 0, 0 };
			int yb[]                  = { 1, 1, 0, 0 };
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulDecoration().getMaximum(vector <int>(xa, xa + (sizeof xa / sizeof xa[0])), vector <int>(ya, ya + (sizeof ya / sizeof ya[0])), vector <int>(xb, xb + (sizeof xb / sizeof xb[0])), vector <int>(yb, yb + (sizeof yb / sizeof yb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int xa[]                  = { 0, 3, 0, 5, 6 };
			int ya[]                  = { 1, 6, 0, 8, 5 };
			int xb[]                  = { 6, 1, 7, 4, 7 };
			int yb[]                  = { 5, 9, 2, 8, 9 };
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulDecoration().getMaximum(vector <int>(xa, xa + (sizeof xa / sizeof xa[0])), vector <int>(ya, ya + (sizeof ya / sizeof ya[0])), vector <int>(xb, xb + (sizeof xb / sizeof xb[0])), vector <int>(yb, yb + (sizeof yb / sizeof yb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int xa[]                  = { 1000000000, 0 };
			int ya[]                  = { 0, 1000000000 };
			int xb[]                  = { 0, 1000000000 };
			int yb[]                  = { 0, 1000000000 };
			int expected__            = 1000000000;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulDecoration().getMaximum(vector <int>(xa, xa + (sizeof xa / sizeof xa[0])), vector <int>(ya, ya + (sizeof ya / sizeof ya[0])), vector <int>(xb, xb + (sizeof xb / sizeof xb[0])), vector <int>(yb, yb + (sizeof yb / sizeof yb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int xa[]                  = ;
			int ya[]                  = ;
			int xb[]                  = ;
			int yb[]                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulDecoration().getMaximum(vector <int>(xa, xa + (sizeof xa / sizeof xa[0])), vector <int>(ya, ya + (sizeof ya / sizeof ya[0])), vector <int>(xb, xb + (sizeof xb / sizeof xb[0])), vector <int>(yb, yb + (sizeof yb / sizeof yb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int xa[]                  = ;
			int ya[]                  = ;
			int xb[]                  = ;
			int yb[]                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulDecoration().getMaximum(vector <int>(xa, xa + (sizeof xa / sizeof xa[0])), vector <int>(ya, ya + (sizeof ya / sizeof ya[0])), vector <int>(xb, xb + (sizeof xb / sizeof xb[0])), vector <int>(yb, yb + (sizeof yb / sizeof yb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int xa[]                  = ;
			int ya[]                  = ;
			int xb[]                  = ;
			int yb[]                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulDecoration().getMaximum(vector <int>(xa, xa + (sizeof xa / sizeof xa[0])), vector <int>(ya, ya + (sizeof ya / sizeof ya[0])), vector <int>(xb, xb + (sizeof xb / sizeof xb[0])), vector <int>(yb, yb + (sizeof yb / sizeof yb[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
  if (argc == 1) {
    for (int test = 0; test < 10; ++test) {
      string command = string(argv[0]) + " ";
      command.push_back('0' + test);
      if (system(command.c_str()))
        cerr << "TEST FAILED!" << endl;
    }
  } else {
    moj_harness::run_test(atoi(argv[1]));
  }
  return 0;
}
// END CUT HERE
