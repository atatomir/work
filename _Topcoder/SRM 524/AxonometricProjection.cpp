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

#define mod 1000000009
#define maxN 57

int n, m, i;
int le[maxN], up[maxN];
ll ans;

ll fact[maxN], inv_fact[maxN];
ll dp[maxN][maxN];

class AxonometricProjection {
public:
    ll poww(ll a, ll b) {
        ll ans = 1;
        a %= mod;

        while (b > 0) {
            if (b & 1) ans = (ans * a) % mod;
            b >>= 1;
            a = (a * a) % mod;
        }

        return ans;
    }

    ll comb(ll n, ll k) {
        ll aux = (fact[n] * inv_fact[k]) % mod;
        aux = (aux * inv_fact[n - k]) % mod;
        return aux;
    }

    void pre() {
        int i;
        const int def = 50;

        fact[0] = 1;
        for (i = 1; i <= def; i++) fact[i] = (fact[i - 1] * i) % mod;

        inv_fact[def] = poww(fact[def], mod - 2);
        for (i = def - 1; i > 0; i--) inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
        inv_fact[0] = 1;
    }

    void solve(int ini1, int ini2) {
        int cnt1, cnt2, p1, p2, mini, i, j, k, rem_right, rem_down;
        ll aux, aux2;
        ll local;

        if (ini1 > n && ini2 > m)
            return;

        if (ini1 > n || ini2 > m) {
            ans = 0;
            return;
        }

        mini = min(le[ini1], up[ini2]);
        p1 = ini1; p2 = ini2;
        while (p1 <= n && le[p1] == mini) p1++;
        while (p2 <= m && up[p2] == mini) p2++;

        cnt1 = p1 - ini1;
        cnt2 = p2 - ini2;

        rem_right = m - p2 + 1;
        rem_down = n - p1 + 1;

        if (mini == 0) {
            solve(p1, p2);
            return;
        }

        for (i = 0; i <= cnt1; i++)
            for (j = 0; j <= cnt2; j++)
                dp[i][j] = 0;

        dp[0][0] = 1;
        for (i = 0; i < cnt1; i++) {
            for (j = 0; j <= cnt2; j++) {
                for (k = 0; j + k <= cnt2; k++) {
                    aux = (dp[i][j] * comb(cnt2 - j, k)) % mod;
                    aux = (aux * poww(mini, cnt2 - j - k)) % mod;
                    aux2 = (poww(mini + 1, rem_right) * poww(mini + 1, j)) % mod;
                    if (k == 0)
                        aux2 += mod - ((poww(mini, j) * poww(mini, rem_right)) % mod);

                    aux = (aux * aux2) % mod;


                    dp[i + 1][j + k] = (dp[i + 1][j + k] + aux) % mod;
                }
            }
        }

        //cerr << dp[2][1];

        local = 0;
        for (i = 0; i <= cnt2; i++) {
            aux = dp[cnt1][i];

            aux = (aux * poww(poww(mini + 1, rem_down), i)) % mod;
            aux = (aux * poww(mod + poww(mini + 1, rem_down) - poww(mini, rem_down), cnt2 - i)) % mod;
            local = (local + aux) % mod;
        }

        ans = (ans * local) % mod;

        solve(p1, p2);
    }

    int howManyWays( vector <int> heightsOfLeftView, vector <int> heightsOfFrontView )  {
        n = heightsOfFrontView.size();
        m = heightsOfLeftView.size();

        pre();

        for (i = 0; i < n; i++)
            le[i + 1] = heightsOfFrontView[i];

        for (i = 0; i < m; i++)
            up[i + 1] = heightsOfLeftView[i];

        sort(le + 1, le + n + 1);
        sort(up + 1, up + m + 1);

        ans = 1;
        solve(1, 1);

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
			int heightsOfLeftView[]   = {1,1};
			int heightsOfFrontView[]  = {1,1};
			int expected__            = 7;

			std::clock_t start__      = std::clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int heightsOfLeftView[]   = {50,50,50,50,524};
			int heightsOfFrontView[]  = {524,524};
			int expected__            = 104060401;

			std::clock_t start__      = std::clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int heightsOfLeftView[]   = {1,2,3,4,5,6,7,8,9,10};
			int heightsOfFrontView[]  = {1,2,3,4,5,6,7,8,9,10,11};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int heightsOfLeftView[]   = {5,2,4,1};
			int heightsOfFrontView[]  = {5,2,4,0,1};
			int expected__            = 429287;

			std::clock_t start__      = std::clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int heightsOfLeftView[]   = {5,2,4,52,24,524};
			int heightsOfFrontView[]  = {0,4,20,24,500,504,520,524};
			int expected__            = 97065655;

			std::clock_t start__      = std::clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int heightsOfLeftView[]   = {3};
			int heightsOfFrontView[]  = {3};
			int expected__            =  1;

			std::clock_t start__      = std::clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			int heightsOfLeftView[]   = ;
			int heightsOfFrontView[]  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int heightsOfLeftView[]   = ;
			int heightsOfFrontView[]  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = AxonometricProjection().howManyWays(vector <int>(heightsOfLeftView, heightsOfLeftView + (sizeof heightsOfLeftView / sizeof heightsOfLeftView[0])), vector <int>(heightsOfFrontView, heightsOfFrontView + (sizeof heightsOfFrontView / sizeof heightsOfFrontView[0])));
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
