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

#define inf 1000000000000000000LL

const ll bucket = 100000;
ll aux[2 * bucket + 11];
ll delta, mod;

ll get_val(ll x) {
    x += delta;
    if (x >= mod) x -= mod;
    return x;
}

ll bs(ll *data, ll _delta, ll _mod, ll limit) {
    delta = _delta;
    mod = _mod;

    if (get_val(data[0]) > limit) return 0;
    ll ans = 0;

    for (ll step = 1 << 19; step > 0; step >>= 1)
        if (ans + step < bucket)
            if (get_val(data[ans + step]) <= limit)
                ans += step;

    return ans + 1;
}

ll prod(ll A, ll B, ll mod) {
    if (A < B) swap(A, B);
    if (B == 0) return 0;

    if (inf / A >= B) return (A * B) % mod;
    return (2LL * prod(A / 2LL, B, mod) + (A % 2) * B) % mod;
}

ll solve(ll k, ll mod, ll cnt, ll limit) {
    ll i, delta, pp;
    ll ans = 0;

    delta = 0;
    for (i = 0; i < bucket; i++) {
        aux[i] = delta;
        delta += k;
        if (delta >= mod) delta -= mod;
    }

    sort(aux, aux + bucket);
    for (i = 0; i < bucket; i++) aux[i + bucket] = aux[i];

    for (i = 0; bucket * (i + 1) <= cnt + 1; i++) {
        delta = ((bucket * i) % mod);
        delta = prod(delta, k, mod);

        pp = lower_bound(aux, aux + bucket, mod - delta) - aux;
        ans += bs(aux + pp, delta, mod, limit);
    }


    for (pp = bucket * i; pp <= cnt; pp++) {
        delta = prod(pp % mod, k, mod);

        if (delta <= limit)
            ans++;
    }

    return ans;
}

ll count_them(ll k, ll mod, ll cnt, ll lower, ll upper) {
    ll to_upper = solve(k, mod, cnt, upper);
    ll to_lower = (lower == 0 ? 0 : solve(k, mod, cnt, lower - 1));

    ll ans = to_upper - to_lower;
    return ans;
}

class ModuleSequence {
public:
    long long countElements( long long K, long long N, long long A, long long B, long long lower, long long upper )  {
        K %= N;

        ll to_B = count_them(K, N, B, lower, upper);
        ll to_A = (A == 0 ? 0 : count_them(K, N, A - 1, lower, upper));

        ll ans = to_B - to_A;
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

	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) {
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
			long long K               = 2;
			long long N               = 7;
			long long A               = 1;
			long long B               = 5;
			long long lower           = 2;
			long long upper           = 5;
			long long expected__      = 3;

			std::clock_t start__      = std::clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long K               = 9;
			long long N               = 1;
			long long A               = 0;
			long long B               = 7;
			long long lower           = 0;
			long long upper           = 0;
			long long expected__      = 8;

			std::clock_t start__      = std::clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long K               = 20;
			long long N               = 12;
			long long A               = 21;
			long long B               = 30;
			long long lower           = 1;
			long long upper           = 11;
			long long expected__      = 6;

			std::clock_t start__      = std::clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long K               = 30;
			long long N               = 89;
			long long A               = 112;
			long long B               = 200;
			long long lower           = 80;
			long long upper           = 88;
			long long expected__      = 9;

			std::clock_t start__      = std::clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long K               = 890;
			long long N               = 1000;
			long long A               = 1000;
			long long B               = 10000;
			long long lower           = 456;
			long long upper           = 980;
			long long expected__      = 4770;

			std::clock_t start__      = std::clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			long long K               = 3873832291;
			long long N               = 9243734047;
			long long A               = 844008683;
			long long B               = 8305999347;
			long long lower           = 65051;
			long long upper           = 3945850064;
			long long expected__      = 3185229126;

			std::clock_t start__      = std::clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			long long K               = ;
			long long N               = ;
			long long A               = ;
			long long B               = ;
			long long lower           = ;
			long long upper           = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long K               = ;
			long long N               = ;
			long long A               = ;
			long long B               = ;
			long long lower           = ;
			long long upper           = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = ModuleSequence().countElements(K, N, A, B, lower, upper);
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
