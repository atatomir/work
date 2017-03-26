#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <functional>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 33

const int defX[4] = {-1, 1, 0, 0};
const int defY[4] = {0, 0, -1, 1};
const int mask = (1 << 21) - 1;

int n, m, i, j;
unordered_map<int, int> M;
ll ans = 0;

string chars = "ABCDEFZHIKLMNOPQRSTVX";
int id[333];
int mat[maxN][maxN];

function<void(int)> to_use;
int xoro;

class AlphabetPaths {
public:
    void dfs(int x, int y, int alrdn, int step, int deny) {
        if (step == 0) {
            to_use(alrdn);
            return;
        }

        for (int i = 0; i < 4; i++) {
            if (i == deny) continue;
            int xx = x + defX[i];
            int yy = y + defY[i];

            if (mat[xx][yy] == 0) continue;
            if (alrdn & mat[xx][yy]) continue;

            dfs(xx, yy, alrdn | mat[xx][yy], step - 1, i ^ 1);
        }
    }

    long long count( vector <string> letterMaze )  {
        n = letterMaze.size();
        m = letterMaze[0].size();

        for (i = 0; i < chars.size(); i++)
            id[chars[i]] = 1 << i;

        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                mat[i + 1][j + 1] = id[letterMaze[i][j]];

        auto add_map = [](int x)->void {
            //cerr << x << '\n';
            M[x]++;
        };

        auto add_ans = [](int x)->void {
            //cerr << x << ' ' << (mask ^ x ^ xoro) << '\n';
            ans += 1LL * M[mask ^ x ^ xoro];
        };

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                if (mat[i][j] == 0) continue;

                M.clear();

                to_use = add_map;
                dfs(i, j, mat[i][j], 10, -1);

                xoro = mat[i][j];
                to_use = add_ans;
                dfs(i, j, mat[i][j], 10, -1);
            }
        }


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

	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) {
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
			string letterMaze[]       = {"ABCDEFZHIXKLMNOPQRST",
 "...................V"};
			long long expected__      = 2;

			std::clock_t start__      = std::clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string letterMaze[]       = {".................VT.",
 "....................",
 "ABCDEFZHIXKLMNOPQRS.",
 "..................S.",
 ".................VT."};
			long long expected__      = 0;

			std::clock_t start__      = std::clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string letterMaze[]       = {"TBCDE.PQRSA",
 "FZHIXKLMNOV"};
			long long expected__      = 50;

			std::clock_t start__      = std::clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string letterMaze[]       = {"ABCDEF.",
 "V....Z.",
 "T....H.",
 "S....I.",
 "R....X.",
 "KLMNOPQ"};
			long long expected__      = 4;

			std::clock_t start__      = std::clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string letterMaze[]       = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string letterMaze[]       = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string letterMaze[]       = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = AlphabetPaths().count(vector <string>(letterMaze, letterMaze + (sizeof letterMaze / sizeof letterMaze[0])));
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
