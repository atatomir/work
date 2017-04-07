#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 5011

const int defX[4] = {-1, 1, 0, 0};
const int defY[4] = {0, 0, -1, 1};

int n, m, i, j, c1, c01, c02, S, D, flow;
char cell[55][55];
int id[55][55];

vector<int> list[maxN];
char C[maxN][maxN], F[maxN][maxN];
int prov[maxN];
queue<int> Q;


void add_edge(int x, int y) {
    C[x][y] = 1;
    list[x].pb(y);
    list[y].pb(x);
}

bool bellman() {
    int i;

    memset(prov, 0, sizeof(prov));
    prov[S] = S;
    Q.push(S);

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();
        if (node == D) continue;

        for (auto to : list[node]) {
            if (C[node][to] > F[node][to] && prov[to] == 0) {
                prov[to] = node;
                Q.push(to);
            }
        }
    }

    if (prov[D] == 0) return false;

    for (auto to : list[D]) {
        if (C[to][D] > F[to][D] && prov[to] != 0) {
            prov[D] = to;

            int aux = 1;
            for (int node = D; node != S; node = prov[node])
                aux = min(aux, C[prov[node]][node] - F[prov[node]][node]);

            for (int node = D; node != S; node = prov[node]) {
                F[prov[node]][node] += aux;
                F[node][prov[node]] -= aux;
            }

            flow += aux;
        }
    }


    return true;
}

class TheTilesDivOne {
public:
    int find( vector <string> board )  {
        n = board.size();
        m = board[0].size();

        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                cell[i][j] = board[i - 1][j - 1];

        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                if ( (i + j) % 2 == 0 )
                    id[i][j] = ++c1;

        for (i = 1; i <= n; i += 2)
            for (j = 1; j <= m; j++)
                if ( (i + j) % 2 == 1 )
                    id[i][j] = ++c01;

        for (i = 2; i <= n; i += 2)
            for (j = 1; j <= m; j++)
                if ( (i + j) % 2 == 1 )
                    id[i][j] = ++c02;

        S = c01 + c02 + 2 * c1 + 1;
        D = S + 1;

        for (i = 1; i <= n; i += 2) {
            for (j = 1; j <= m; j++) {
                if ( (i + j) % 2 == 1 ) {
                    if (cell[i][j] == 'X') continue;
                    add_edge(S, id[i][j]);

                    for (int dd = 0; dd < 4; dd++) {
                        int x = i + defX[dd];
                        int y = j + defY[dd];
                        if (id[x][y] == 0) continue;
                        add_edge(id[i][j], c01 + id[x][y]);
                    }
                }
            }
        }

        for (i = 2; i <= n; i += 2) {
            for (j = 1; j <= m; j++) {
                if ( (i + j) % 2 == 1 ) {
                    if (cell[i][j] == 'X') continue;
                    add_edge(c01 + 2 * c1 + id[i][j], D);

                    for (int dd = 0; dd < 4; dd++) {
                        int x = i + defX[dd];
                        int y = j + defY[dd];
                        if (id[x][y] == 0) continue;
                        add_edge(c01 + c1 + id[x][y], c01 + 2 * c1 + id[i][j]);
                    }
                }
            }
        }



        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                if ( (i + j) % 2 == 0 )
                    if (cell[i][j] != 'X')
                        add_edge(c01 + id[i][j], c01 + c1 + id[i][j]);

        flow = 0;
        while (bellman());

        //cerr << C[60][136];

        return flow;
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
			string board[]            = {"X.X",
 "...",
 "X.X"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"...",
 "...",
 "..."};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"......X.X.XXX.X.XX."};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"X.....XXX.XX..XXXXXXXXX...X.XX.XX....X",
 ".XXXX..X..XXXXXXXX....XX.X.X.X.....XXX",
 "....XX....X.XX..X.X...XX.X..XXXXXXX..X",
 "XX.XXXXX.X.X..X..XX.XXX..XX...XXX.X..."};
			int expected__            = 13;

			std::clock_t start__      = std::clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
			string board[]            = {"..", ".X", "X.", ".."};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 5: {
			string board[]            = {"X.X", "...", "X.X"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TheTilesDivOne().find(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
