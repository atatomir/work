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

#define maxN 55
int n,i,j,lim,targ;
int Power[maxN];
ll mask[maxN];

int wh;
vector<int> notSel,Sel;
ll actMask,sum,ans;


class MagicMolecule {
public:
    bool allGood(){
        if(Sel.size()<targ) return false;

        ll mm = actMask;
        foreach(Sel){
            mm &= mask[*it];
            if(mm!=actMask) return false;
        }

        if(sum==2 && n==4) cerr << actMask << '\n';
        return true;
    }

    int maxMagicPower( vector <int> magicPower, vector <string> magicBond )  {
        n = magicPower.size();
        fordef(i,0,n-1) Power[i+1] = magicPower[i];
        fordef(i,0,n-1){
            mask[i+1]=0;
            fordef(j,0,n-1){
                if( magicBond[i][j]=='Y'  || i==j)
                    mask[i+1] |= 1LL<<(j+1);
            }
        }

        //! bulaneala
        targ = (n*2+2)/3;
        srand(time(NULL)); ans=-1; lim = 12000000; actMask = 0;
        notSel.clear(); Sel.clear();
        fordef(i,1,n) notSel.pb(i);

        while(lim--){
            wh = rand()%2;
            if(Sel.size()<targ) wh = 1; //! add
            if(notSel.size()==0) wh = 0; //! remove

            if(wh==1){
                wh = rand()%notSel.size();
                int val = notSel[wh];
                notSel[wh] = notSel[ notSel.size()-1 ]; notSel.pop_back();
                Sel.push_back(val);

                actMask |= 1LL<<val;
                sum += Power[val];

                //cerr << "add " << val << ' ' << sum << '\n';
            } else {
                wh = rand()%Sel.size();
                int val = Sel[wh];
                Sel[wh] = Sel[ Sel.size()-1 ]; Sel.pop_back();
                notSel.push_back(val);

                actMask ^= 1LL<<val;
                sum -= Power[val];

                //cerr << "rm " << val << ' ' << sum << '\n';
            }

            if(allGood()) ans = max(ans,sum);
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
			int magicPower[]          = {1,2,3};
			string magicBond[]        = {"NYY","YNN","YNN"};
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int magicPower[]          = {1,1,1,1};
			string magicBond[]        = {"NNYY","NNYY","YYNN","YYNN"};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int magicPower[]          = {86,15,100,93,53,50};
			string magicBond[]        = {"NYYYYN","YNNNNY","YNNYYN","YNYNYN","YNYYNY","NYNNYN"};
			int expected__            = 332;

			std::clock_t start__      = std::clock();
			int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int magicPower[]          = {3969,9430,7242,8549,8190,8368,3704,9740,1691};
			string magicBond[]        = {"NYYYYYYYY","YNYYYYYYY","YYNYYYYYY","YYYNYYYYY","YYYYNYYYY","YYYYYNYYY","YYYYYYNNY","YYYYYYNNY","YYYYYYYYN"};
			int expected__            = 57179;

			std::clock_t start__      = std::clock();
			int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int magicPower[]          = ;
			string magicBond[]        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int magicPower[]          = ;
			string magicBond[]        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int magicPower[]          = ;
			string magicBond[]        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MagicMolecule().maxMagicPower(vector <int>(magicPower, magicPower + (sizeof magicPower / sizeof magicPower[0])), vector <string>(magicBond, magicBond + (sizeof magicBond / sizeof magicBond[0])));
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
