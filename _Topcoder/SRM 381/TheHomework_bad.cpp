#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define foreach( vect ) for( auto it = vect.begin() ; it!=vect.end(); it++ )
#define fordef(ind,bg,en) for(ind = bg;ind<=en;ind++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxVal 1024

int cntA[maxVal],cntB[maxVal];
int tmp;

class TheHomework {
public:
    void check(int n,int m,int a,int b,int ans){
        while(b < 0) { a += -b; b = 0; }

        int step = n/2; if(step==0) return;
        ans += (b+step-1)/step;
        a -= b; b = 0;

        while(a>0){
            ans++;
            step = n/2;
            n -= step; a -= step;
        }

        tmp = min(tmp,ans);
    }

    int transform( vector <int> first, vector <int> second )  {
        int n,m,i,j,a,b,ans;
        n = first.size(); m = second.size();
        ans = 0;

        fordef(i,0,1000) cntA[i]=cntB[i]=0;
        foreach(first) cntA[*it]++;
        foreach(second) cntB[*it]++;

        a=b=0;
        fordef(i,0,1000){
            int def = min(cntA[i],cntB[i]);
            a += cntA[i]-def;
            b += cntB[i]-def;
        }

        if(a==b && a==0) return 0;

        while(n<m){
            ans++;
            b -= n;
            n <<= 1;
        }



        tmp = 1000;
        check(m,m,a,b+(n-m),0);
        check(n,m,a,b,0);
        check(2*n,m,a,b-n,1);

        return ans+tmp;
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
			int first[]               = {1,2,3};
			int second[]              = {2,3,4};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TheHomework().transform(vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(second, second + (sizeof second / sizeof second[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int first[]               = {0};
			int second[]              = {1};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TheHomework().transform(vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(second, second + (sizeof second / sizeof second[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int first[]               = {5,2,7,999,7};
			int second[]              = {7,7,2,999,5};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = TheHomework().transform(vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(second, second + (sizeof second / sizeof second[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int first[]               = {12,13};
			int second[]              = {1,1,1,1,1,1,1,1,1};
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = TheHomework().transform(vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(second, second + (sizeof second / sizeof second[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int first[]               = ;
			int second[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TheHomework().transform(vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(second, second + (sizeof second / sizeof second[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int first[]               = ;
			int second[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TheHomework().transform(vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(second, second + (sizeof second / sizeof second[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int first[]               = ;
			int second[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TheHomework().transform(vector <int>(first, first + (sizeof first / sizeof first[0])), vector <int>(second, second + (sizeof second / sizeof second[0])));
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
