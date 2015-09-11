#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define fordef(ind,bg,en) for(ind = bg;ind<=en;ind++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

class PointDistance {
public:
    long long getDistance(int x1, int y1, int x2, int y2) {
        return 1LL * (x1 - x2) * (x1 - x2) + 1LL * (y1 - y2) * (y1 - y2);
    }

    vector <int> findPoint( int x1, int y1, int x2, int y2 )  {
        for (int x3 = -100; x3 <= 100; x3++) {
            for (int y3 = -100; y3 <= 100; y3++) {
                if (x3 == x1 && y3 == y1) continue;
                if (x3 == x2 && y3 == y2) continue;

                long long d1 = getDistance(x1, y1, x3, y3);
                long long d2 = getDistance(x2, y2, x3, y3);

                if (d1 > d2) {
                    return {x3, y3};
                }
            }
        }
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

	template<typename T> std::ostream& operator<<(std::ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, std::clock_t elapsed) {
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
			int x1                    = -1;
			int y1                    = 0;
			int x2                    = 1;
			int y2                    = 0;
			int expected__[]          = {8, 48 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointDistance().findPoint(x1, y1, x2, y2);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int x1                    = 1;
			int y1                    = 1;
			int x2                    = -1;
			int y2                    = -1;
			int expected__[]          = {25, -63 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointDistance().findPoint(x1, y1, x2, y2);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int x1                    = 0;
			int y1                    = 1;
			int x2                    = 2;
			int y2                    = 3;
			int expected__[]          = {41, 65 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointDistance().findPoint(x1, y1, x2, y2);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int x1                    = 5;
			int y1                    = -4;
			int x2                    = -2;
			int y2                    = 5;
			int expected__[]          = {68, 70 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointDistance().findPoint(x1, y1, x2, y2);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int x1                    = -50;
			int y1                    = -50;
			int x2                    = 50;
			int y2                    = -50;
			int expected__[]          = {67, 4 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointDistance().findPoint(x1, y1, x2, y2);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			int x1                    = -50;
			int y1                    = 50;
			int x2                    = -49;
			int y2                    = 49;
			int expected__[]          = {73, -25 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointDistance().findPoint(x1, y1, x2, y2);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

      case 6: {
			int x1                    = +50;
			int y1                    = +50;
			int x2                    = -50;
			int y2                    = -50;
			int expected__[]          = {};

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointDistance().findPoint(x1, y1, x2, y2);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
/*      case 7: {
			int x1                    = ;
			int y1                    = ;
			int x2                    = ;
			int y2                    = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointDistance().findPoint(x1, y1, x2, y2);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 8: {
			int x1                    = ;
			int y1                    = ;
			int x2                    = ;
			int y2                    = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointDistance().findPoint(x1, y1, x2, y2);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
