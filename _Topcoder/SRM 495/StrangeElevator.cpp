#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define mod 1000000007

map<pair<int, int>, int> F, G;
vector<int> divs;
int i;

int g(int h, int n);

// in serie
int f(int h, int n) {
    pair<int, int> aux = mp(h, n);
    int ans = 0;

    if (F.count(aux) == 0) {
        if (h % n != 0) {
            F[aux] = 0;
        } else {

            for (auto e : divs) {
                if (h % e == 0) {
                    ans += g(h / e, n);
                    if (ans >= mod) ans -= mod;
                }
            }

            F[aux] = ans;
        }
    }

    return F[aux];
}

// in paralel
int g(int h, int n) {
    pair<int, int> aux = mp(h, n);
    int ans = 0;

    if (G.count(aux) == 0) {
        if (h % n != 0) {
            G[aux] = 0;
        } else {

            for (auto e : divs) {
                if (n % e == 0) {
                    //! provin din paralel
                    //ans += g(h / e, n / e);
                    //if (ans >= mod) ans -= mod;

                    //! provin din serie
                    ans += f(h / e, n / e);
                    if (ans >= mod) ans -= mod;
                }
            }

            G[aux] = ans;
        }
    }



    return G[aux];
}

class StrangeElevator {
public:
    int theCount( int H, int N )  {
        for (i = 1; i * i <= H; i++) {
            if (H % i == 0) {
                if (i != 1) divs.pb(i);
                if (H / i != 1) divs.pb(H / i);
            }
        }

        sort(divs.begin(), divs.end());
        divs.resize(unique(divs.begin(), divs.end()) - divs.begin());

        G[mp(1, 1)] = 1;
        F[mp(1, 1)] = 1;

        if (H == 1 && N == 1) return 1;
        int ans = g(H, N) + f(H, N);
        return ans % mod;
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
			int H                     = 58;
			int N                     = 2;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int H                     = 1;
			int N                     = 1;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int H                     = 9;
			int N                     = 3;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int H                     = 120;
			int N                     = 12;
			int expected__            = 30;

			std::clock_t start__      = std::clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int H                     = 58585858;
			int N                     = 495;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int H                     = ;
			int N                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int H                     = ;
			int N                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = StrangeElevator().theCount(H, N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int H                     = ;
			int N                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = StrangeElevator().theCount(H, N);
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
