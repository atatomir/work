#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

#define foreach( vect ) for( auto it = vect.begin() ; it!=vect.end(); it++ )
#define fordef(ind,bg,en) for(ind = bg;ind<=en;ind++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxVal 1024
#define dim 111
int cntA[maxVal],cntB[maxVal];

int dist[dim][dim],lim;
bool us[dim][dim];
queue<pa(int,int)> Q;

class TheHomework {
public:
    bool good(int n,int k){
        if(n > 100 || n<=0) return false;
        if(k > 50 || k<0)  return false;
        if(us[n][k]) return false;
        return true;
    }

    void BFS(int n,int k){
        int i,nn,kk;
        us[n][k] = true;
        dist[n][k] = 0;
        while(!Q.empty()) Q.pop();
        Q.push(mp(n,k));

        while(!Q.empty()){
            pa(int,int) act = Q.front(); Q.pop();
            //cerr << act.first << ' ' << act.second << '\n';
            n = act.first; k = act.second;

            //! op 1
            fordef(i,1,act.first){
                nn = n+i; kk = min(k+i,lim);

                if(!good(nn,kk)) continue;
                dist[nn][kk] = dist[n][k]+1;
                us[nn][kk] = true;
                Q.push(mp(nn,kk));
            }

            //! op 2
            int steps = n/2;
            fordef(i,1,steps){
                nn = n-i; kk = min(nn,k);

                if(!good(nn,kk)) continue;
                dist[nn][kk] = dist[n][k]+1;
                us[nn][kk] = true;
                Q.push(mp(nn,kk));
            }

            //! op 3
            /**/ steps = n/2;
            fordef(i,1,steps){
                nn = n; kk = min(nn,k+i);

                if(!good(nn,kk)) continue;
                dist[nn][kk] = dist[n][k]+1;
                us[nn][kk] = true;
                Q.push(mp(nn,kk));
            }
        }
    }

    int transform( vector <int> first, vector <int> second )  {
        int n,m,i,j,k;
        n = first.size(); m = second.size(); lim = m;

        fordef(i,0,1000) cntA[i]=cntB[i]=0;
        foreach(first) cntA[*it]++;
        foreach(second) cntB[*it]++;

        k=0;
        fordef(i,0,1000){
            int def = min(cntA[i],cntB[i]);
            k += def;
        }
        BFS(n,k);

        return dist[m][m];
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
