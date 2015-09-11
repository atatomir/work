#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 22

int n, i;
int mask[maxN];
int dp[1 << maxN];

class OrderOfOperationsDiv2 {
public:
    int compute(int conf) {
        if (conf == 0) return 0;
        if (dp[conf] != 0) return dp[conf];

        int actBits = 0;
        for (int op = 0; op < n; op++)
            if ( ( conf & (1 << op) ) != 0 )
                actBits |= mask[op];

        dp[conf] = 10000;
        for (int op = 0; op < n; op++) {
            if ( ( conf & (1 << op) ) == 0 ) continue;

            int prov = conf ^ (1 << op);
            int provBits = 0;

            for (int l_op = 0; l_op < n; l_op++)
                if ( ( prov & (1 << l_op) ) != 0 )
                    provBits |= mask[l_op];

            provBits ^= actBits;
            int count_bits = 0;
            while (provBits > 0) {
                count_bits++;
                provBits &= provBits - 1;
            }

            dp[conf] = min(dp[conf], count_bits * count_bits + compute(prov));
        }

        return dp[conf];
    }

    int minTime( vector <string> s )  {
        n = s.size();
        memset(dp, 0, sizeof(dp));
        for (i = 0; i < n; i++) {
            mask[i] = 0;
            for (int bit = 0; bit < s[i].size(); bit++)
                if (s[i][bit] == '1')
                    mask[i] |= 1 << bit;
        }

        return compute( (1 << n) - 1 );
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
			string s[]                = {
 "111",
 "001",
 "010"
};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = OrderOfOperationsDiv2().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s[]                = {
 "11101",
 "00111",
 "10101",
 "00000",
 "11000"
};
			int expected__            = 9;

			std::clock_t start__      = std::clock();
			int received__            = OrderOfOperationsDiv2().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s[]                = {
  "11111111111111111111"
};
			int expected__            = 400;

			std::clock_t start__      = std::clock();
			int received__            = OrderOfOperationsDiv2().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s[]                = {
  "1000",
  "1100",
  "1110"
};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = OrderOfOperationsDiv2().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s[]                = {
  "111",
  "111",
  "110",
  "100"
};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = OrderOfOperationsDiv2().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

       case 5: {
			string s[]                = {"001","111","000"};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = OrderOfOperationsDiv2().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 6: {
			string s[]                = {"1010",
                                         "0010",
                                         "0101",
                                         "1111",};
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = OrderOfOperationsDiv2().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			string s[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = OrderOfOperationsDiv2().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])));
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
