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

#define maxN 555

int n, i, j, k;
pair<ll, ll> P[maxN];
ll xmin, xmax, ymin, ymax, px1, px2, py1, py2, pos1, pos2;
bool cbd[maxN];

vector< pair<ll, ll> > on_border, inside;
vector< pair<int, int> > interv;

bool dp[maxN][maxN];

bool is_on_border(pair<ll, ll> act) {
    if (act.first == xmin) return true;
    if (act.first == xmax) return true;
    if (act.second == ymin) return true;
    if (act.second == ymax) return true;
    return false;
}

class PointErasing {
public:
    vector <int> getOutcomes( vector <int> y )  {
        n = y.size();
        for (i = 1; i <= n; i++) P[i] = mp(i, 1 + y[i - 1]);

        xmin = 1;
        xmax = n;
        ymin = 1LL << 60;
        ymax = 0;

        for (auto e : y) {
            ymin = min(ymin, 1LL + e);
            ymax = max(ymax, 1LL + e);
        }

        memset(cbd, 0, sizeof(cbd));
        for (i = 1; i <= n; i++)
            if (is_on_border(P[i]))
                on_border.pb(P[i]);

        memset(cbd, 0, sizeof(cbd));
        for (auto p1 : on_border) {
            for (auto p2 : on_border) {
                px1 = min(p1.first, p2.first);
                px2 = max(p1.first, p2.first);
                py1 = min(p1.second, p2.second);
                py2 = max(p1.second, p2.second);

                /*cerr << p1.first << ' ' << p1.second << '\n';
                cerr << p2.first << ' ' << p2.second << '\n';
                cerr << px1 << ' ' << px2 << ' ' << py1 << ' ' << py2 << '\n';*/

                for (i = 1; i <= n; i++)
                    if (px1 < P[i].first && P[i].first < px2)
                        if (py1 < P[i].second && P[i].second < py2)
                            cbd[i] = true;
            }
        }

        for (i = 1; i <= n; i++)
            if (!is_on_border(P[i]))
                if (cbd[i] == false)
                    inside.pb(P[i]);

        for (i = 1; i <= n; i++) {
            for (j = i + 1; j <= n; j++) {
                px1 = i;
                px2 = j;
                py1 = min(P[i].second, P[j].second);
                py2 = max(P[i].second, P[j].second);



                pos1 = 0;
                while (true) {

                    for (; pos1 < inside.size(); pos1++)
                        if (px1 < inside[pos1].first && inside[pos1].first < px2)
                            if (py1 < inside[pos1].second && inside[pos1].second < py2)
                                break;

                    if (pos1 == inside.size()) break;


                    for (pos2 = pos1; pos2 < inside.size(); pos2++)
                        if (px1 >= inside[pos2].first || inside[pos2].first >= px2 ||
                            py1 >= inside[pos2].second || inside[pos2].second >= py2)
                                break;

                    pos2--;
                    interv.pb(mp(pos1, pos2));
                    pos1 = pos2 + 1;

                    //! there is no need to use this while..
                    break;
                }


            }
        }

        /*sort(interv.begin(), interv.end());
        interv.resize(unique(interv.begin(), interv.end()) - interv.begin());
        for (auto e : interv) cerr << e.first << ' ' << e.second << '\n';
        cerr << on_border.size() << '\n';

        for (auto e : inside)
            cerr << e.first << ' ' << e.second << '\n';*/

        memset(dp, 0, sizeof(dp));

        for (i = 0; i < inside.size(); i++) {
            if (i != 0) {
                for (j = 0; j <= i + 1; j++)
                    dp[i][j + 1] = dp[i - 1][j];
            } else {
                dp[i][1] = true;
            }

            for (j = 0; j <= i + 1; j++) {
                for (auto e : interv) {
                    if (e.second != i) continue;

                    if (e.first == 0)
                        dp[i][0] = true;
                    else
                        dp[i][j] |= dp[e.first - 1][j];
                }
            }
        }

        vector<int> ans = {};
        if (inside.size()) {
            for (i = 0; i <= inside.size(); i++)
                if (dp[inside.size() - 1][i] == true)
                    ans.pb(on_border.size() + i);
        } else {
            ans = {on_border.size()};
        }

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
			int y[]                   = { 1, 2, 1, 1, 0, 4, 3 };
			int expected__[]          = {4, 6 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int y[]                   = { 0, 0, 4, 4, 8, 8, 4, 4 };
			int expected__[]          = {6 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int y[]                   = { 522 };
			int expected__[]          = {1 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int y[]                   = { 19, 19, 19, 19, 19, 19 };
			int expected__[]          = {6 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int y[]                   = { 0, 1, 2, 3, 4 };
			int expected__[]          = {2 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			int y[]                   = { 7, 8, 8, 7, 6, 7, 9, 3, 5, 0 };
			int expected__[]          = {3, 4, 5 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 6: {
			int y[]                   = { 3, 2, 3, 3, 4, 3, 4, 3, 3, 1, 5, 3 };
			int expected__[]          = {4, 5, 6, 7, 9 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 7: {
			int y[]                   = { 5, 5, 4, 4, 5, 8, 5, 5, 5, 5, 5, 9, 2, 0, 9, 4, 5, 5, 3, 4, 4, 4, 4, 7, 4 };
			int expected__[]          = {6, 7, 8, 10, 11, 12, 13, 15, 16, 17 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			int y[]                   = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 9: {
			int y[]                   = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 10: {
			int y[]                   = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = PointErasing().getOutcomes(vector <int>(y, y + (sizeof y / sizeof y[0])));
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
