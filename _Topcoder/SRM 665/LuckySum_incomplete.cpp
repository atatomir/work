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

int n,i;
string Note,tmp;
long long Answer;

class LuckySum {
public:
    long long ToLong(string &S){
        long long def = 1,ans=0;
        for(int i=n-1;i>=0;i--){
            ans += def*(S[i]-'0');
            def *= 10LL;
        }
        return ans;
    }

    bool isFrom(char ch,char a,char b,char c,char d){
        return a==ch || b==ch || c==ch || d==ch;
    }

    bool check(int step){
        if(step==0){
            if(n==1 && tmp[0]!='8') return false;
        }

        if(step<=0) return true;

        if ( isFrom(tmp[step-1],'9','2','5','@') )
            if ( !isFrom(tmp[step],'1','4','2','5') ) return false;

        if ( step==n-1 && isFrom(tmp[step],'9','2','5','@') ) return false;


        return true;
    }

    void Back(int step){
        if(!check(step-1)) return;

        if (step==n){
            long long act = ToLong(tmp);
            Answer = min(Answer,act);
            return;
        }

        if(Note[step]!='?') {
            tmp[step]=Note[step];
            Back(step+1);
            return;
        }

        tmp[step] = '1'; Back(step+1);
        tmp[step] = '4'; Back(step+1);
        tmp[step] = '8'; Back(step+1);
        tmp[step] = '2'; Back(step+1);
        tmp[step] = '5'; Back(step+1);
        tmp[step] = '9'; Back(step+1);
    }

    long long construct( string note )  {
        Note = note; n = Note.size(); tmp = Note;
        Answer = 1LL<<60;

        Back(0);

        if(Answer == (1LL<<60)) Answer = -1;
        return Answer;
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
			string note               = "4?8";
			long long expected__      = 448;

			std::clock_t start__      = std::clock();
			long long received__      = LuckySum().construct(note);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string note               = "?1";
			long long expected__      = 11;

			std::clock_t start__      = std::clock();
			long long received__      = LuckySum().construct(note);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string note               = "?";
			long long expected__      = 8;

			std::clock_t start__      = std::clock();
			long long received__      = LuckySum().construct(note);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string note               = "2??";
			long long expected__      = -1;

			std::clock_t start__      = std::clock();
			long long received__      = LuckySum().construct(note);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string note               = "??????????????";
			long long expected__      = 11888888888888LL;

			std::clock_t start__      = std::clock();
			long long received__      = LuckySum().construct(note);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string note               = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = LuckySum().construct(note);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string note               = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = LuckySum().construct(note);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string note               = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = LuckySum().construct(note);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
  if (argc == 1) {
    for (int test = 0; test < 1; ++test) {
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
