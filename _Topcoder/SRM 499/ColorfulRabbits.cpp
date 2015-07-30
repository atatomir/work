#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

#define foreach( vect ) for( auto it = vect.begin() ; it!=vect.end(); it++ )
#define fordef(ind,bg,en) for(ind = bg;ind<=en;ind++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 1000011

int cnt[maxN],i;
int def=1000000;

class ColorfulRabbits {
public:
    int getMinimum( vector <int> replies )  {
        memset(cnt,0,sizeof(cnt));
        foreach(replies) cnt[*it]++;

        int ans = 0;
        fordef(i,0,def)
            ans += (i+1)*((cnt[i]+i)/(i+1));
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
			int replies[]             = { 1, 1, 2, 2 } ;
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulRabbits().getMinimum(vector <int>(replies, replies + (sizeof replies / sizeof replies[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int replies[]             = { 0 } ;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulRabbits().getMinimum(vector <int>(replies, replies + (sizeof replies / sizeof replies[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int replies[]             = { 2, 2, 44, 2, 2, 2, 444, 2, 2 } ;
			int expected__            = 499;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulRabbits().getMinimum(vector <int>(replies, replies + (sizeof replies / sizeof replies[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 3: {
			int replies[]             = {1000};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulRabbits().getMinimum(vector <int>(replies, replies + (sizeof replies / sizeof replies[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 4: {
			int replies[]             = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulRabbits().getMinimum(vector <int>(replies, replies + (sizeof replies / sizeof replies[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int replies[]             = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ColorfulRabbits().getMinimum(vector <int>(replies, replies + (sizeof replies / sizeof replies[0])));
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
