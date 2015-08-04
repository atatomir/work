#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#define foreach( vect ) for( auto it = vect.begin() ; it!=vect.end(); it++ )
#define fordef(ind,bg,en) for(ind = bg;ind<=en;ind++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 1000011
double dp[maxN];

class TheDiceGame {
public:
    double expectedThrows( int candies )  {
        int i,j;
        double def = 1.00/6.00;

        dp[0] = 0.00;
        fordef(i,1,candies) {
            dp[i]=1.00;
            for(j=i-1;j>=0 && i-j<=6;j--) dp[i] += def*dp[j];
        }

        /*fordef(i,candies,candies+5){
            dp[i] = 1.00;
            for(j=candies-1;j>=0 && i-j<=6;j--) dp[i] += dp[j]*def;
        }*/

        double ans = 0.00;
        fordef(i,candies,candies+5) ans += def*dp[i];

        //fordef(i,1,candies+5) cerr << i << ' ' << setprecision(5) << dp[i] << '\n';

        return dp[candies];
    }
};

// BEGIN CUT HERE
#include <algorithm>
#include <cmath>
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

	static const double MAX_DOUBLE_ERROR = 1e-9;
	static bool topcoder_fequ(double expected, double result) {
		if (std::isnan(expected)) {
			return std::isnan(result);
		} else if (std::isinf(expected)) {
			if (expected > 0) {
				return result > 0 && std::isinf(result);
			} else {
				return result < 0 && std::isinf(result);
			}
		} else if (std::isnan(result) || std::isinf(result)) {
			return false;
		} else if (std::fabs(result - expected) < MAX_DOUBLE_ERROR) {
			return true;
		} else {
			double mmin = std::min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			double mmax = std::max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			return result > mmin && result < mmax;
		}
	}
	double moj_relative_error(double expected, double result) {
		if (std::isnan(expected) || std::isinf(expected) || std::isnan(result) || std::isinf(result) || expected == 0) {
			return 0;
		}
		return std::fabs(result-expected) / std::fabs(expected);
	}

	int verify_case(int casenum, const double &expected, const double &received, std::clock_t elapsed) {
		std::cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received);
			if (rerr > 0) {
				std::sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int candies               = 1;
			double expected__         = 1.0;

			std::clock_t start__      = std::clock();
			double received__         = TheDiceGame().expectedThrows(candies);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int candies               = 2;
			double expected__         = 1.1666666666666667;

			std::clock_t start__      = std::clock();
			double received__         = TheDiceGame().expectedThrows(candies);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int candies               = 7;
			double expected__         = 2.5216263717421126;

			std::clock_t start__      = std::clock();
			double received__         = TheDiceGame().expectedThrows(candies);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int candies               = 47;
			double expected__         = 13.90476189046144;

			std::clock_t start__      = std::clock();
			double received__         = TheDiceGame().expectedThrows(candies);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int candies               = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = TheDiceGame().expectedThrows(candies);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int candies               = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = TheDiceGame().expectedThrows(candies);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int candies               = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = TheDiceGame().expectedThrows(candies);
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
