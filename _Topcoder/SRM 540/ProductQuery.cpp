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

#define maxN 111
#define mod 1000000007

int n, i;
vector< pair<int, int> > base[maxN], rest[maxN];
int inv[33];

ll dp[maxN][maxN];

int simp(ll d) {
    int pos, i, j, cnt;
    vector< pair<int, int> > aux;
    bool any;

    for (pos = n; pos > 0; pos--) {
        if (rest[pos].empty()) continue;
        aux = rest[pos];
        rest[pos].clear();

        sort(aux.begin(), aux.end());
        cnt = 1;

        for (i = 1; i < aux.size(); i++) {
            if (aux[i - 1].first == aux[i].first) {
                if (aux[i - 1] != aux[i])
                    return -1;
            } else {
                aux[cnt++] = aux[i];
            }
        }
        aux.resize(cnt);

        any = false;
        for (i = 0; i < cnt; i++) {
            if (aux[i].second == 0) {
                if (any) return -1;
            } else {
                any = true;
            }
        }

        if (aux[0].second == 0) {
            for (i = 0; i + 1 < cnt; i++)
                if (aux[i + 1].second != 0)
                    break;

            if (i == cnt - 1) {
                rest[pos] = {aux[i]};
                continue;
            } else {
                rest[aux[i + 1].first - 1].pb(aux[i]);
            }

            for (j = i + 1; j < cnt; j++)
                aux[j - i - 1] = aux[j];
            aux.resize(aux.size() - i - 1);
        }

        if (aux.empty()) continue;
        rest[pos] = {aux.back()};

        for (i = 0; i + 1 < aux.size(); i++) {
            rest[aux[i + 1].first - 1].pb(mp(aux[i].first, (aux[i].second * inv[aux[i + 1].second]) % d));
        }
    }

    return 0;
}

ll solve(ll d) {
    int i, j, k, pos;

    inv[0] = 0;
    for (i = 1; i < d; i++) {
        inv[i] = 1;
        for (j = 1; j <= d - 2; j++) inv[i] = (inv[i] * i) % d;
    }

    for (i = 1; i <= n; i++) {
        rest[i].clear();
        for (auto e : base[i])
            rest[i].pb(mp(e.first, e.second % d));
    }

    if (simp(d) == -1) return 0;

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            dp[i][j] %= mod;

            if (rest[i + 1].empty()) {
                dp[i + 1][j] += (dp[i][j] * (d - 1)) % mod;
                dp[i + 1][i + 1] += dp[i][j];
            } else {
                if (rest[i + 1][0].second == 0) {
                    //! must be zero
                    pos = rest[i + 1][0].first;
                    if (j < pos) {
                        dp[i + 1][i + 1] += dp[i][j];
                    } else {
                        dp[i + 1][j] += (dp[i][j] * (d - 1)) % mod;
                        dp[i + 1][i + 1] += dp[i][j];
                    }
                } else {
                    //! must be non-zero
                    pos = rest[i + 1][0].first;
                    if (j < pos) {
                        dp[i + 1][j] += dp[i][j];
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (i = 0; i <= n; i++)
        ans += dp[n][i] % mod;
    ans %= mod;

    //cerr << "For " << d << " - " << ans << '\n';

    return ans;
}

class ProductQuery {
public:
    int theInput( int N, vector <int> Qfrom, vector <int> Qto, vector <int> output )  {
        n = N;
        for (i = 0; i < Qfrom.size(); i++)
            base[Qto[i] + 1].pb(mp(Qfrom[i] + 1, output[i]));

        ll ans = solve(2) * solve(5);
        ans %= mod;

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
			int N                     = 3;
			int Qfrom[]               = {0};
			int Qto[]                 = {0};
			int output[]              = {5};
			int expected__            = 100;

			std::clock_t start__      = std::clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 5;
			int Qfrom[]               = {0, 2, 0};
			int Qto[]                 = {1, 4, 4};
			int output[]              = {3, 4, 6};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 3;
			int Qfrom[]               = {0, 1};
			int Qto[]                 = {1, 2};
			int output[]              = {5, 8};
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 8;
			int Qfrom[]               = {2, 0, 3, 6};
			int Qto[]                 = {3, 7, 4, 6};
			int output[]              = {2, 0, 6, 7};
			int expected__            = 118080;

			std::clock_t start__      = std::clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 20;
			int Qfrom[]               = {9, 6, 2, 3, 1, 3, 12, 3, 4, 6, 10, 18, 10, 11, 15, 5};
			int Qto[]                 = {12, 12, 4, 13, 7, 14, 17, 10, 5, 13, 11, 19, 17, 14, 17, 8};
			int output[]              = {7, 5, 7, 5, 0, 5, 8, 5, 3, 5, 3, 9, 4, 1, 6, 5};
			int expected__            = 276398080;

			std::clock_t start__      = std::clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 58;
			int Qfrom[]               = {5, 5};
			int Qto[]                 = {8, 8};
			int output[]              = {1, 2};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int N                     = ;
			int Qfrom[]               = ;
			int Qto[]                 = ;
			int output[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int Qfrom[]               = ;
			int Qto[]                 = ;
			int output[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int Qfrom[]               = ;
			int Qto[]                 = ;
			int output[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
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
