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

#define maxN 5555
#define maxS 111
#define mod 10007

int n, m, s, i, j;
ll dpR[maxN][maxS];
ll dpD[maxN][maxS];
ll fact[maxN], inv_fact[maxN];

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

ll comb(ll n, ll k) {
    ll ans = fact[n] * inv_fact[n - k] * inv_fact[k];
    return ans % mod;
}

ll solve() {
    int i, j, k, t1, t2;
    ll ans, aux;

    dpR[0][0] = 1;
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= s; j++) {
            if (dpR[i][j] == 0) continue;
            dpR[i][j] %= mod;

            for (k = 0; k + j <= s; k++)
                dpR[i + 1][j + k] += dpR[i][j] * (k + 1),
                dpR[i + 1][j + k] %= mod;
        }
    }

    dpD[0][0] = 1;
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= s; j++) {
            if (dpD[i][j] == 0) continue;
            dpD[i][j] %= mod;

            for (k = 1; k + j <= s; k++)
                dpD[i + 1][j + k] += dpD[i][j] * k,
                dpD[i + 1][j + k] %= mod;
        }
    }

    fact[0] = 1;
    for (i = 1; i < maxN; i++) fact[i] = (fact[i - 1] * i) % mod;

    inv_fact[maxN - 1] = poww(fact[maxN - 1], mod - 2);
    for (i = maxN - 2; i > 0; i--) inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
    inv_fact[0] = 1;

    ans = 0;
    for (i = 1; i < n; i++) {
        int down = i - 1;
        int right = m - 1;
        int steps = down + right;
        int bonus = n - i;
        int other = n * m - 2 * steps - bonus - 1;

        for (t1 = 0; t1 <= s; t1++) {
            if (dpD[down][t1] == 0) continue;
            for (t2 = 0; t1 + t2 <= s; t2++) {
                if (dpR[right][t2] == 0) continue;

                aux = dpD[down][t1] * dpR[right][t2] * comb(steps - 1, down);
                aux %= mod;
                aux *= poww(s + 1, other);
                aux %= mod;
                aux *= comb(s - t1 - t2 + bonus - 1, bonus - 1);

                ans = (ans + aux) % mod;
            }
        }
    }

    for (i = 1; i < m; i++) {
        int down = n - 1;
        int right = i - 1;
        int steps = down + right;
        int bonus = m - i;
        int other = n * m - 2 * steps - bonus - 1;

        for (t1 = 0; t1 <= s; t1++) {
            if (dpD[down][t1] == 0) continue;
            for (t2 = 0; t1 + t2 <= s; t2++) {
                if (dpR[right][t2] == 0) continue;

                aux = dpD[down][t1] * dpR[right][t2] * comb(steps - 1, right);
                aux %= mod;
                aux *= poww(s + 1, other);
                aux %= mod;
                aux *= comb(s - t1 - t2 + bonus - 1, bonus - 1);

                ans = (ans + aux) % mod;
            }
        }
    }

    if (n == 1 || m == 1) {
        int dst = max(n, m) - 1;
        ans = comb(s + dst - 1, dst - 1);
    }

    if (n * m == 1) {
        if (s == 0)
            return 1;
        else
            return 0;
    }

    return ans;
}

class FoxAndGreed {
public:
    int count( int H, int W, int S )  {
        n = H;
        m = W;
        s = S;

        return solve();
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
			int H                     = 2;
			int W                     = 2;
			int S                     = 1;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int H                     = 2;
			int W                     = 2;
			int S                     = 2;
			int expected__            = 9;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int H                     = 2;
			int W                     = 2;
			int S                     = 0;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int H                     = 47;
			int W                     = 58;
			int S                     = 100;
			int expected__            = 1301;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int H                     = 1234;
			int W                     = 2345;
			int S                     = 97;
			int expected__            = 8894;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int H                     = 2500;
			int W                     = 1;
			int S                     = 100;
			int expected__            = 7254;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int H                     = ;
			int W                     = ;
			int S                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGreed().count(H, W, S);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int H                     = ;
			int W                     = ;
			int S                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FoxAndGreed().count(H, W, S);
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
