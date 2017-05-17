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

#define mod 1000000007
#define act_state dp[t][vis][bl][prs][odd][tp]

vector<int> boxes;
int black, towers, cbs;

int dp[10][52][12][52][10][2];
int dp2[111][111], comb[111][111];
int how_many[111];
ll ans;

template<typename T>
void add(T& a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

bool valid(int vis, int bl, int prs, int odd) {
    static int cnt;

    vis += odd;
    if (vis > cbs) return false;

    cnt = (cbs - vis) / 2;
    cnt = min(cnt, prs);
    prs -= cnt;

    if (bl + prs > black) return false;

    return true;
}

void pre() {
    int t, h, vis, inv, bl, tp, lim_h, new_bl, new_col, prs, odd;
    int i, j, k;

    cbs = 0;
    for (auto e : boxes) cbs += e;
    lim_h = cbs + 2 * black;

    if (black >= 2 && cbs >= 1)
        dp[1][0][2][0][1][1] = 1;


    dp[0][0][0][0][0][1] = 1;
    for (t = 0; t < towers; t++) {
        for (vis = 0; vis <= cbs; vis++) {
            for (bl = 0; bl <= black; bl++) {
                for (prs = 0; prs <= 40; prs++) {
                    for (odd = 0; odd <= t; odd++) {
                        for (tp = 0; tp < 2; tp++) {

                            if (act_state == 0) continue;
                            if (!valid(vis, bl, prs, odd)) continue;

                            add(how_many[vis], act_state);

                            //cerr << t << ' ' << vis << ' ' << bl << ' ' << prs << ' ' << odd << ' ' << tp << ' ' <<  act_state << '\n';

                            //! add a colored block
                            add(dp[t][vis + 1][bl][prs][odd][0], act_state);

                            //! add a black block
                            add(dp[t][vis][bl + 1][prs][odd][1], act_state);

                            //! add a new tower
                            h = vis + 2 * bl - t;
                            if (tp == 1) continue;

                            if (!valid(vis, bl + 1, prs + ((h - 1) / 2), odd + ((h - 1) % 2))) continue;
                            add(dp[t + 1][vis][bl + 1][prs + ((h - 1) / 2)][odd + ((h - 1) % 2)][1], act_state);
                        }
                    }
                }
            }
        }
    }


    for (i = 0; i <= cbs; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j - 1];
            add(comb[i][j], comb[i - 1][j]);
        }
    }

    dp2[0][0] = 1;
    for (i = 1; i <= boxes.size(); i++) {
        for (j = 0; j <= 100; j++) {
            for (k = 0; k <= boxes[i - 1] && k <= j; k++) {
                add(dp2[i][j], (1LL * dp2[i - 1][j - k] * comb[j][k]) % mod);
            }
        }
    }

    for (i = 0; i <= cbs; i++) {
        //cerr << how_many[i] << ' ';
        ans += 1LL * how_many[i] * dp2[boxes.size()][i];
        ans %= mod;
    }
}

class SkewedPerspective {
public:
    int countThem( vector <int> cubes, int B, int w )  {
        boxes = cubes;
        black = B;
        towers = w;

        pre();

        add(ans, mod - 1);
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
			int cubes[]               = {1,1};
			int B                     = 1;
			int w                     = 2;
			int expected__            = 19;

			std::clock_t start__      = std::clock();
			int received__            = SkewedPerspective().countThem(vector <int>(cubes, cubes + (sizeof cubes / sizeof cubes[0])), B, w);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int cubes[]               = {1};
			int B                     = 3;
			int w                     = 2;
			int expected__            = 19;

			std::clock_t start__      = std::clock();
			int received__            = SkewedPerspective().countThem(vector <int>(cubes, cubes + (sizeof cubes / sizeof cubes[0])), B, w);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int cubes[]               = {};
			int B                     = 5;
			int w                     = 5;
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = SkewedPerspective().countThem(vector <int>(cubes, cubes + (sizeof cubes / sizeof cubes[0])), B, w);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int cubes[]               = {7,7,7};
			int B                     = 0;
			int w                     = 8;
			int expected__            = 301226488;

			std::clock_t start__      = std::clock();
			int received__            = SkewedPerspective().countThem(vector <int>(cubes, cubes + (sizeof cubes / sizeof cubes[0])), B, w);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
			int cubes[]               = {1};
			int B                     = 5;
			int w                     = 5;
			int expected__            = 39;

			std::clock_t start__      = std::clock();
			int received__            = SkewedPerspective().countThem(vector <int>(cubes, cubes + (sizeof cubes / sizeof cubes[0])), B, w);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 5: {
			int cubes[]               = {9};
			int B                     = 2;
			int w                     = 6;
			int expected__            = 466;

			std::clock_t start__      = std::clock();
			int received__            = SkewedPerspective().countThem(vector <int>(cubes, cubes + (sizeof cubes / sizeof cubes[0])), B, w);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 6: {
			int cubes[]               = {50};
			int B                     = 10;
			int w                     = 8;
			int expected__            = 665146241;

			std::clock_t start__      = std::clock();
			int received__            = SkewedPerspective().countThem(vector <int>(cubes, cubes + (sizeof cubes / sizeof cubes[0])), B, w);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
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
