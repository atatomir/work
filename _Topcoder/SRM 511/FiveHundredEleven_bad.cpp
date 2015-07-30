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

class FiveHundredEleven {
public:
    bool par;
    vector<int> _cards;

    void backT(int pas,int conf,int sel){
        if(pas==_cards.size()){
            if(conf!= 511) return;
            if(sel%2==0) par = true;
            cerr << (sel);
            return;
        }

        if( (conf & _cards[pas]) != _cards[pas]) backT(pas+1,conf|_cards[pas],sel+1);
        backT(pas+1,conf,sel);
    }

    string theWinner( vector <int> cards )  {
        cards.pb(511);
        _cards = cards;

        par = false;
        backT(0,0,0);

        if(par) return "Fox Ciel" ;
        else    return "Toastman";
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

	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) {
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
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl;
			std::cerr << "    Received: \"" << received << "\"" << std::endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int cards[]               = {3, 5, 7, 9, 510};
			string expected__         = "Fox Ciel";

			std::clock_t start__      = std::clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int cards[]               = {0, 0, 0, 0};
			string expected__         = "Toastman";

			std::clock_t start__      = std::clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int cards[]               = {511};
			string expected__         = "Toastman";

			std::clock_t start__      = std::clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int cards[]               = {5, 58, 192, 256};
			string expected__         = "Fox Ciel";

			std::clock_t start__      = std::clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
			int cards[]               = {0,0,0,0,0};
			string expected__         = "Fox Ciel";

			std::clock_t start__      = std::clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 5: {
			int cards[]               = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int cards[]               = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = FiveHundredEleven().theWinner(vector <int>(cards, cards + (sizeof cards / sizeof cards[0])));
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
