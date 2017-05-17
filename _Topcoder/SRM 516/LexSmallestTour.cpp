#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 51

int n, i, j;
char adj[maxN][maxN];
vector<int> ord;
char last;

bool us[maxN];
bool any;
int cnt;

int n1, act_gr;
char c1;
int gr[maxN];

int edges;

void dfs(int node) {
    us[node] = true;
    gr[node] = act_gr;

    for (int i = 1; i <= n; i++)
        if (adj[node][i] != '.' && !us[i])
            dfs(i), any = true;
}

bool check(int from, int to, char act) {
    int i, j;
    int total;
    char best_col;
    int best_cnt;

    for (i = 1; i <= n; i++) {
        best_col = 'A';
        best_cnt = 0;
        total = 0;

        if (i == 1 && to == 1) {
            adj[1][n1] = c1;
            adj[1][from] = act;
        }

        for (j = 1; j <= n; j++) {
            if (adj[i][j] == '.') continue;
            total++;

            if (best_cnt == 0) best_col = adj[i][j];
            if (best_col == adj[i][j]) best_cnt++;
            else                       best_cnt--;
        }

        best_cnt = 0;
        for (j = 1; j <= n; j++)
            if (adj[i][j] == best_col)
                best_cnt++;

        if (i == 1 && to == 1) {
            adj[1][n1] = '.';
            adj[1][from] = '.';
        }


        if (i != 1 && i != to) {
            if (total % 2 == 1) { /*cerr << "Error1";*/ return false;}

            if (best_cnt * 2 > total) return false;
            continue;
        }

        if (1 != to) {
            if (total % 2 == 0) {/*cerr << "Error2";*/ return false;}

            if (i == 1) {
                if (best_cnt > (total + 1) / 2) return false;
            } else {
                if (best_cnt > (total + 1) / 2) return false;
                if (best_cnt == (total + 1) / 2 && best_col == act) return false;
            }
        } else {
            if (total % 2 == 1) {/*cerr << "Error3";*/ return false;}

            if (best_cnt - (total - best_cnt) > 2) return false;
            if (best_cnt - (total - best_cnt) == 2 && c1 != best_col) return false;
        }
    }

    memset(us, 0, sizeof(us));
    cnt = 0;

    act_gr++;
    any = false;
    dfs(to);
    if (any) cnt++;
    bool ret = any;

    for (i = 1; i <= n; i++) {
        if (us[i]) continue;
        act_gr++;
        any = false;
        dfs(i);
        if (any) {
            cnt++;
            //cerr << "found " << i << '\n';
        }
    }

    //cerr << "!" << gr[32] << "\n";

    if (cnt > 1) return false;
    if (cnt == 1 && ret == false) return false;
    if (gr[1] != gr[to]) return false;

    return true;
}

void doit(int node) {
    int i;
    char act_edge;

    ord.pb(node);
    //cerr << node << '\n';

    //for (i = 1; i <= n; i++) cerr << adj[node][i];
    //cerr << '\n';

    for (i = 1; i <= n; i++) {
        if (adj[node][i] == '.') continue;
        if (adj[node][i] == last) continue;

        act_edge = adj[node][i];
        adj[node][i] = adj[i][node] = '.';

        if (!check(node, i, act_edge)) {
            adj[node][i] = adj[i][node] = act_edge;
        } else {

            if (n1 == 0) {
                n1 = i;
                c1 = act_edge;
            }

            last = act_edge;
            //cerr << (--edges) << '\n';

            //cerr << "go " << node << ' ' << i << '\n';
            doit(i);
            return;
        }
    }

    return;
}

bool final_check() {
    int i, j;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (adj[i][j] != '.')
                return false;

    return true;
}

class LexSmallestTour {
public:
    vector <int> determineTour( vector <string> roads, vector <int> queries )  {
        n = roads.size();
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                adj[i + 1][j + 1] = roads[i][j], edges += (roads[i][j] != '.');

        vector<int> ans = {};

        //edges /= 2;
        //cerr << edges << '\n';

        last = '?';
        doit(1);
        for (auto e : queries) ans.pb(ord[e] - 1);

        if (!final_check())
            return {};

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
			string roads[]            = {".AB"
,"A.C"
,"BC."};
			int queries[]             = {0, 1, 2, 3};
			int expected__[]          = {0, 1, 2, 0 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string roads[]            = {".A..C"
,"A.ABB"
,".A.C."
,".BC.."
,"CB..."};
			int queries[]             = {0, 1, 2, 3, 4, 5, 6};
			int expected__[]          = {0, 1, 3, 2, 1, 4, 0 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string roads[]            = {".aa"
,"a.A"
,"aA."};
			int queries[]             = {3, 2, 1};
			int expected__[]          = {0, 2, 1 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string roads[]            = {"..A.A"
,"...A."
,"A...A"
,".A..."
,"A.A.."};
			int queries[]             = {1, 2};
			int expected__[]          = { };

			std::clock_t start__      = std::clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

      case 4: {
			string roads[]            = {".zmyYMV", "z.etalY", "me.CLUI", "ytC.MsL", "YaLM.wo", "MlUsw.i", "VYILoi."};
			int queries[]             = {0, 1, 21, 20, 17, 11, 10, 13, 2, 9, 19, 8, 12, 15, 3, 5, 16, 6, 7, 4, 14, 18};
			int expected__[]          = {0, 1, 0, 6, 6, 2, 6, 4, 2, 1, 5, 5, 3, 5, 0, 1, 3, 4, 0, 3, 2, 4};

			std::clock_t start__      = std::clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
      case 5: {
			string roads[]            = {"........B.....BABAA...B...AAB......AB..", ".....BA....A.BB..B...A.A.ABAA.A.B...B.B", "...BAAABB.B..ABA......A.BBAAB...B....A.", "..B......B.ABBBBAA....A..BAA.B...AA.B.A", "..A..B..A.A.BA...A...BBBA.BA.A.....B.B.", ".BA.B..AA..B.BAAAB.A.AABA...B.BABB..B..", ".AA.....AB.AB.ABB...BA.BB.ABB...BA..A.A", "..B..A.........BAA.B.A..ABBB.B.A...BA.A", "B.B.AAA...A.BABAAB..B..AAA.BB.B.BA..B..", "...B..B....BA.A.A.BBAB...AAB.AA.B.BA...", "..B.A...A...BBABAA.AABA.ABB.ABB.AB....B", ".A.A.BA..B..A..B.A......A.BB.........B.", "...BB.B.BABA.AABBABA.BA.AA..AAA..B.B..B", ".BABAB..A.B.A..A.......A.BBAABBBA...BA.", "BBBB.AA.BAA.A....B.....ABBAABABA.......", "A.AB.ABBA.BBBA..BAAA..B.B.ABBA..A...A.B", "B..A.ABAAAA.B..B.A....A.BBBB.B.A.......", "AB.AAB.AB.AAA.BAA.B.BBB..ABBA..B...AB..", "A........B..B..A.B.A.....A....B........", ".....A.B.BA.A..A..A.......BBBAB....B..A", "......B.BAA......B....B....BABA.A...A..", ".A..BAAA.BB.B....B.........ABAA.A.BB...", "B.AABA....A.A..BAB..B..ABBABABBB...A.A.", ".A..BBB.A....AA.......A...ABBA.B......B", "..B.AABAA.AAA.BBB.....B..BBAA..BA..BAB.", ".ABB...BAAB.ABB.BAA...B.B..AABAAAB.BABA", "ABAAB.AB.ABB.BAABB.B..AAB..B......A.A..", "AAAAA.BBBB.B.AABBB.BBABBAAB.AA.A.B.A.BA", "BAB..BB.B.A.AABB.A.BABABAA.A.B.......A.", "...BA..B.AB.ABAAB..ABABA.B.AB.AB.A....B", ".A...B..BAB.ABB...BBAAB..A...A.A...B.A.", ".....A.A.....BA.AB....BBBA.A.BA.BB.AAB.", ".BB..BB.BBA..A.A....AA..AA.....B..BA...", "...A.BA.A.B.B............B.B.A.B...AA..", "...A.....B...........B....A.....B..A...", "A...B..B.A..B....A.B.BA.BB.A..BAAAA.B..", "BB.B.BAAB....B.A.B..A...AAA....A.A.B..B", "..A.B......B.A........A.BB.BA.AB......A", ".B.A..AA..B.B..B...A...B.A.A.B......BA."};
			int queries[]             = {0, 1, 352, 351, 260, 304, 28, 25, 239, 272, 98, 77, 305, 274, 57, 225, 348, 21, 113, 3, 269, 90, 340, 96, 211, 179, 162, 140, 104, 299, 131, 216, 262, 296, 254, 283, 73, 286, 64, 129, 137, 249, 182, 255, 142, 150, 290, 20, 6, 192};
			int expected__[]          = {0, 8, 0, 35, 28, 29, 6, 5, 16, 24, 8, 32, 28, 23, 6, 27, 37, 9, 28, 5, 38, 10, 22, 5, 11, 24, 15, 3, 13, 10, 15, 6, 12, 35, 24, 27, 22, 31, 2, 36, 30, 36, 12, 25, 12, 13, 25, 6, 11, 20};

			std::clock_t start__      = std::clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
/*      case 6: {
			string roads[]            = ;
			int queries[]             = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = LexSmallestTour().determineTour(vector <string>(roads, roads + (sizeof roads / sizeof roads[0])), vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
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
