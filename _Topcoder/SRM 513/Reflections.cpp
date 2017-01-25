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

#define maxN 25

int i, limit, n, conf;
vector<ll> mirr;
vector<ll> vals[maxN];

ll mem_cnt[1 << 21];
ll mem[1 << 21];

ll abss(ll x) {
    if (x < 0) return -x;
    return x;
}

ll get_best(ll bts, ll need) {
    ll ans = (1LL << 50);

    auto it = lower_bound(vals[bts].begin(), vals[bts].end(), need);
    if (it != vals[bts].end())
        ans = min(ans, abss(*it - need));

    if (it != vals[bts].begin()) {
        it--;
        ans = min(ans, abss(*it - need));
    }

    return ans;
}

ll solve(vector<int> int_mirr, ll dest) {
    ll aux, bit, cnt;
    ll bts, need;
    ll ans = (1LL << 60);

    mirr = {};
    for (auto e : int_mirr)
        mirr.pb(e);

    n = mirr.size();
    limit = 1 << n;
    for (i = 0; i <= n; i++)
        vals[i].clear();

    for (conf = 0; conf < limit; conf++) {
        aux = cnt = 0;
        for (bit = 0; bit < n; bit++)
            if (conf & (1 << bit))
                cnt++, aux += 2LL * mirr[bit];
        vals[cnt].pb(aux);

        mem_cnt[conf] = cnt;
        mem[conf] = aux;
    }

    for (i = 0; i <= n; i++)
        sort(vals[i].begin(), vals[i].end());

    for (conf = 0; conf < limit; conf++) {
        bts = mem_cnt[conf];
        need = -(dest - mem[conf]);


        if (bts > 0)
            ans = min(ans, bts + bts - 1 + get_best(bts - 1, need));
        ans = min(ans, bts + bts + get_best(bts, need));
    }

    return ans;
}

class Reflections {
public:
    long long minimumMoves( vector <int> mirrorX, vector <int> mirrorY, vector <int> mirrorZ, vector <int> finalPosition )  {
        return solve(mirrorX, finalPosition[0]) +
               solve(mirrorY, finalPosition[1]) +
               solve(mirrorZ, finalPosition[2]);
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
			int mirrorX[]             = {2};
			int mirrorY[]             = {};
			int mirrorZ[]             = {};
			int finalPosition[]       = {3, 0, 1};
			long long expected__      = 3;

			std::clock_t start__      = std::clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int mirrorX[]             = {-5, 1, 4, 2, 3, 6, -6};
			int mirrorY[]             = {};
			int mirrorZ[]             = {};
			int finalPosition[]       = {9, 0, 0};
			long long expected__      = 2;

			std::clock_t start__      = std::clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int mirrorX[]             = {5, 8};
			int mirrorY[]             = {};
			int mirrorZ[]             = {};
			int finalPosition[]       = {4, 0, 0};
			long long expected__      = 4;

			std::clock_t start__      = std::clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int mirrorX[]             = {5};
			int mirrorY[]             = {5};
			int mirrorZ[]             = {1, 2, 3};
			int finalPosition[]       = {10, 12, -1};
			long long expected__      = 5;

			std::clock_t start__      = std::clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int mirrorX[]             = {8, -3, 21};
			int mirrorY[]             = {4, 5};
			int mirrorZ[]             = {-7, -2, -1, 7, 14};
			int finalPosition[]       = {40, -4, 31};
			long long expected__      = 10;

			std::clock_t start__      = std::clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int mirrorX[]             = ;
			int mirrorY[]             = ;
			int mirrorZ[]             = ;
			int finalPosition[]       = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int mirrorX[]             = ;
			int mirrorY[]             = ;
			int mirrorZ[]             = ;
			int finalPosition[]       = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int mirrorX[]             = ;
			int mirrorY[]             = ;
			int mirrorZ[]             = ;
			int finalPosition[]       = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = Reflections().minimumMoves(vector <int>(mirrorX, mirrorX + (sizeof mirrorX / sizeof mirrorX[0])), vector <int>(mirrorY, mirrorY + (sizeof mirrorY / sizeof mirrorY[0])), vector <int>(mirrorZ, mirrorZ + (sizeof mirrorZ / sizeof mirrorZ[0])), vector <int>(finalPosition, finalPosition + (sizeof finalPosition / sizeof finalPosition[0])));
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
