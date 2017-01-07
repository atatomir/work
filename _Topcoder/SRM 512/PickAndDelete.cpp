#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <sstream>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 211
#define mod 1000000007

string data;
int n, i, j, k;
int nr[maxN];
int comb[maxN][maxN];
int dp[maxN][maxN];

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

class PickAndDelete {
public:
    int count( vector <string> S )  {
        data = "";
        for (auto e : S) data += e;
        istringstream fin(data);

        n = 0;
        while (!fin.eof())
            fin >> nr[++n];

        for (i = 0; i <= n; i++) {
            comb[i][0] = 1;
            for (j = 1; j <= i; j++)
                comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
        }

        nr[0] = 0;
        sort(nr + 1, nr + n + 1);

        int aux;

        dp[0][0] = 1;
        for (i = 1; i <= n; i++) {
            for (j = i; j <= n; j++) {
                dp[i][j] = 0;

                for (k = 0; k <= j; k++) {
                    if (dp[i - 1][j - k] == 0) continue;

                    aux = (1LL * dp[i - 1][j - k] * comb[j][k]) % mod;
                    aux = (1LL * aux * poww(nr[i] - nr[i - 1], k)) % mod;

                    dp[i][j] = (dp[i][j] + aux) % mod;
                }
            }
        }

        return dp[n][n];
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
			string S[]                = {"1 2"};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S[]                = {"2 2 2 2 2 2 2 2 2"};
			int expected__            = 512;

			std::clock_t start__      = std::clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S[]                = {"5", " 1 ", "2"};
			int expected__            = 34;

			std::clock_t start__      = std::clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S[]                = {"3 ", "14159 265", "3589 7", " 932"};
			int expected__            = 353127147;

			std::clock_t start__      = std::clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string S[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string S[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string S[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
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
