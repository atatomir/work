#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

#define fordef(ind,bg,en) for(ind = bg;ind<=en;ind++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 33

int N, M, i, j;
int pay[maxN][maxN];
int dp[maxN][maxN][maxN]; //! pos,now,last

class ShopPositions {
public:
    int maxProfit( int n, int m, vector <int> c )  {
        for (i = 0; i < n; i++) {
            for (j = 1; j <= 3 * m; j++){
                pay[i][j] = c[i * 3 * m + j - 1];
            }
        }

        memset(dp, 0, sizeof(dp));

        for (int pos = 1; pos <= n; pos++) {
            for (int now = 0; now <= m; now++) {
                for (int last = 0; last <= m; last++) {
                    dp[pos][now][last] = 0;
                    for (int l_last = 0; l_last <= m; l_last++) {
                        if (l_last > 0 && pos == 1) break;

                        int act = dp[pos - 1][last][l_last] +
                                  pay[pos - 1][l_last + last + now] * last;
                        dp[pos][now][last] = max(dp[pos][now][last], act);
                    }
                }
            }
        }

        int ans = 0;
        for (i = 0; i <= m; i++) ans = max(ans, dp[n][0][i]);

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
			int n                     = 1;
			int m                     = 5;
			int c[]                   = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 1, 1, 1, 1, 1};
			int expected__            = 300;

			std::clock_t start__      = std::clock();
			int received__            = ShopPositions().maxProfit(n, m, vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 1;
			int m                     = 5;
			int c[]                   = {1000, 5, 4, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
			int expected__            = 1000;

			std::clock_t start__      = std::clock();
			int received__            = ShopPositions().maxProfit(n, m, vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 3;
			int m                     = 1;
			int c[]                   = { 7,6,1, 10,4,1, 7,6,3 };
			int expected__            = 14;

			std::clock_t start__      = std::clock();
			int received__            = ShopPositions().maxProfit(n, m, vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 2;
			int m                     = 2;
			int c[]                   = { 12,11,10,9,8,7, 6,5,4,3,2,1 };
			int expected__            = 24;

			std::clock_t start__      = std::clock();
			int received__            = ShopPositions().maxProfit(n, m, vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 3;
			int m                     = 3;
			int c[]                   = { 30,28,25,15,14,10,5,4,2, 50,40,30,28,17,13,8,6,3, 45,26,14,14,13,13,2,1,1 };
			int expected__            = 127;

			std::clock_t start__      = std::clock();
			int received__            = ShopPositions().maxProfit(n, m, vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int n                     = ;
			int m                     = ;
			int c[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ShopPositions().maxProfit(n, m, vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int n                     = ;
			int m                     = ;
			int c[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ShopPositions().maxProfit(n, m, vector <int>(c, c + (sizeof c / sizeof c[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			int m                     = ;
			int c[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ShopPositions().maxProfit(n, m, vector <int>(c, c + (sizeof c / sizeof c[0])));
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
