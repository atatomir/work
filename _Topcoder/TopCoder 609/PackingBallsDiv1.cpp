#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define author @atatomir
using namespace std;

#define mp make_pair
#define pb push_back
#define foreach( vect ) for( typeof(vect) it = vect,begin() ; it!=vect.end(); it++ )
#define fordef(ind,bg,en) for(ind = bg;ind<=en;ind++)

#define maxN 100011
#define X x
#define k K

int x[maxN],i,vaj;
int v[maxN],ans;

class PackingBallsDiv1 {
public:
    int minPacks( int K, int A, int B, int C, int D )  {
        X[0] = A;
        for(i = 1;i<=k-1;i++) X[i] = (1LL*X[i-1] * B + 1LL*C) % D + 1;

        for(i=0;i<k;i++) {
            vaj += x[i]/k; v[i] = x[i]%k;
            if(v[i]==0) {v[i]=k; vaj--;}
        }

        sort(v,v+k); ans = k;

        for(i=0;i<k;i++){
            int now = (k-i-1) + v[i];
            ans = min(now,ans);
        }

        ans += vaj;
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
			int K                     = 3;
			int A                     = 4;
			int B                     = 2;
			int C                     = 5;
			int D                     = 6;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = PackingBallsDiv1().minPacks(K, A, B, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int K                     = 1;
			int A                     = 58;
			int B                     = 23;
			int C                     = 39;
			int D                     = 93;
			int expected__            = 58;

			std::clock_t start__      = std::clock();
			int received__            = PackingBallsDiv1().minPacks(K, A, B, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int K                     = 23;
			int A                     = 10988;
			int B                     = 5573;
			int C                     = 4384;
			int D                     = 100007;
			int expected__            = 47743;

			std::clock_t start__      = std::clock();
			int received__            = PackingBallsDiv1().minPacks(K, A, B, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int K                     = 100000;
			int A                     = 123456789;
			int B                     = 234567890;
			int C                     = 345678901;
			int D                     = 1000000000;
			int expected__            = 331988732;

			std::clock_t start__      = std::clock();
			int received__            = PackingBallsDiv1().minPacks(K, A, B, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int K                     = ;
			int A                     = ;
			int B                     = ;
			int C                     = ;
			int D                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PackingBallsDiv1().minPacks(K, A, B, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int K                     = ;
			int A                     = ;
			int B                     = ;
			int C                     = ;
			int D                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PackingBallsDiv1().minPacks(K, A, B, C, D);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int K                     = ;
			int A                     = ;
			int B                     = ;
			int C                     = ;
			int D                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PackingBallsDiv1().minPacks(K, A, B, C, D);
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
