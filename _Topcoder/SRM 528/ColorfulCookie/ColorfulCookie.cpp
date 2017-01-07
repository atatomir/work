#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define lim 40
#define maxN 57
#define maxFrom 44
#define inf 1000000

int n, i, j, p1, p2;
int cnt[maxN];
int dp[maxN][maxN * maxFrom];


class ColorfulCookie {
public:
    int getMaximum( vector <int> cookies, int P1, int P2 )  {
        n = cookies.size();
        for (i = 1; i <= n; i++) cnt[i] = cookies[i - 1];
        p1 = P1; p2 = P2;

        int ans = 0;
        for (int step = (1 << 12); step > 0; step >>= 1)
            if (check(ans + step))
                ans += step;

        return ans * (p1 + p2);
    }

    bool check(int how_many) {
        int i, j, k, aux;

        if (how_many >= lim * n) return false;

        for (i = 0; i <= n; i++)
            for (j = 0; j <= n * lim; j++)
                dp[i][j] = -inf;

        dp[0][0] = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j <= i * lim; j++) {
                if (dp[i][j] < 0) continue;
                if (j > how_many) continue;

                for (k = 0; k <= lim; k++) {
                    if (j + k > how_many) continue;
                    if (cnt[i + 1] < p1 * k) continue;

                    aux = min(lim, how_many - k);
                    aux = min(aux, (cnt[i + 1] - p1 * k) / p2);

                    dp[i + 1][j + k] = max(dp[i + 1][j + k], dp[i][j] + aux);
                }
            }
        }


        return dp[n][how_many] >= how_many;
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
			int cookies[]             = {100, 100};
			int P1                    = 50;
			int P2                    = 50;
			int expected__            = 200;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int cookies[]             = {50, 250, 50};
			int P1                    = 50;
			int P2                    = 100;
			int expected__            = 300;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int cookies[]             = {2000};
			int P1                    = 100;
			int P2                    = 200;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int cookies[]             = {123, 456, 789, 555};
			int P1                    = 58;
			int P2                    = 158;
			int expected__            = 1728;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
			int cookies[]             = {2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000};
			int P1                    = 2000;
			int P2                    = 2000;
			int expected__            = 48000;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 5: {
			int cookies[]             = ;
			int P1                    = ;
			int P2                    = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int cookies[]             = ;
			int P1                    = ;
			int P2                    = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulCookie().getMaximum(vector <int>(cookies, cookies + (sizeof cookies / sizeof cookies[0])), P1, P2);
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
