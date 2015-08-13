#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

#define foreach( vect ) for( auto it = vect.begin() ; it!=vect.end(); it++ )
#define fordef(ind,bg,en) for(ind = bg;ind<=en;ind++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 111
#define maxLog 9

int n,i,j,logg;
vector<int> list[maxN];
vector<int> how[maxN];
int dad[maxLog][maxN],lvl[maxN];
int diff[maxN];
bool us[maxN];
vector<int> ans;

class LuckyCycle {
public:
    void dfs(int node){
        us[node] = true;
        for(int i=0;i<list[node].size();i++){
            int newNode = list[node][i];
            if(us[newNode]) continue;

            dad[0][newNode] = node;
            diff[newNode] = diff[node] + (how[node][i]==4?1:-1);
            lvl[newNode] = lvl[node]+1;
            dfs(newNode);
        }
    }

    int goUp(int A,int how){
        for(int actLog=logg;actLog>=0;actLog--){
            if( (how&(1<<actLog))!=0 ) A = dad[actLog][A];
        }
        return A;
    }

    int getLca(int A,int B){
        if(lvl[A] < lvl[B]) swap(A,B);

        A = goUp(A, lvl[A]-lvl[B] );
        if(A==B) return A;

        for(int actLog = logg;actLog>=0;actLog--){
            int _A = dad[actLog][A];
            int _B = dad[actLog][B];

            if(_A!=_B) {
                A = _A; B = _B;
            }
        }
        return dad[0][A];
    }

    vector <int> getEdge( vector <int> edge1, vector <int> edge2, vector <int> weight )  {
        ans = {};

        n = edge1.size()+1;
        for(i=0;i<edge1.size();i++) {
            int n1 = edge1[i];
            int n2 = edge2[i];
            list[n1].pb(n2); how[n1].pb( weight[i] );
            list[n2].pb(n1); how[n2].pb( weight[i] );
        }

        memset(dad,0,sizeof(dad));
        dfs(1);

        logg = 7;
        for (int actLog=1;actLog<=logg;actLog++) {
            for(i=1;i<=n;i++) {
                dad[actLog][i] = dad[actLog-1][ dad[actLog-1][i] ];
            }
        }

        for(i=1;i<n;i++){
            for(j=i+1;j<=n;j++){
                if(dad[0][i]==j || dad[0][j]==i) continue;

                int lca = getLca(i,j);
                //!----------
                int sum = diff[i]+diff[j]-diff[lca]-diff[lca];
                cerr << i << ' ' << j << ' ' << lca << '\n';
                if(sum==-1){
                    ans = {i,j,4};
                    return ans;
                }
                if(sum==1){
                    ans = {i,j,7};
                    return ans;
                }
            }
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
			int edge1[]               = {1};
			int edge2[]               = {2};
			int weight[]              = {4};
			int expected__[]          = { };

			std::clock_t start__      = std::clock();
			vector <int> received__   = LuckyCycle().getEdge(vector <int>(edge1, edge1 + (sizeof edge1 / sizeof edge1[0])), vector <int>(edge2, edge2 + (sizeof edge2 / sizeof edge2[0])), vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int edge1[]               = {1, 3, 2, 4};
			int edge2[]               = {2, 2, 4, 5};
			int weight[]              = {4, 7, 4, 7};
			int expected__[]          = {1, 5, 7 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = LuckyCycle().getEdge(vector <int>(edge1, edge1 + (sizeof edge1 / sizeof edge1[0])), vector <int>(edge2, edge2 + (sizeof edge2 / sizeof edge2[0])), vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int edge1[]               = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
			int edge2[]               = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
			int weight[]              = {4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7};
			int expected__[]          = {1, 12, 7 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = LuckyCycle().getEdge(vector <int>(edge1, edge1 + (sizeof edge1 / sizeof edge1[0])), vector <int>(edge2, edge2 + (sizeof edge2 / sizeof edge2[0])), vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int edge1[]               = {1, 2, 3, 5, 6};
			int edge2[]               = {2, 3, 4, 3, 5};
			int weight[]              = {4, 7, 7, 7, 7};
			int expected__[]          = {1, 4, 4 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = LuckyCycle().getEdge(vector <int>(edge1, edge1 + (sizeof edge1 / sizeof edge1[0])), vector <int>(edge2, edge2 + (sizeof edge2 / sizeof edge2[0])), vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

      case 4: {
			int edge1[]               = {1,1,3};
			int edge2[]               = {2,3,4};
			int weight[]              = {4,7,7};
			int expected__[]          = {2,4,4};

			std::clock_t start__      = std::clock();
			vector <int> received__   = LuckyCycle().getEdge(vector <int>(edge1, edge1 + (sizeof edge1 / sizeof edge1[0])), vector <int>(edge2, edge2 + (sizeof edge2 / sizeof edge2[0])), vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
      case 5: {
			int edge1[]               = {1,2,2};
			int edge2[]               = {2,4,3};
			int weight[]              = {4,4,7};
			int expected__[]          = {};

			std::clock_t start__      = std::clock();
			vector <int> received__   = LuckyCycle().getEdge(vector <int>(edge1, edge1 + (sizeof edge1 / sizeof edge1[0])), vector <int>(edge2, edge2 + (sizeof edge2 / sizeof edge2[0])), vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
/*      case 6: {
			int edge1[]               = ;
			int edge2[]               = ;
			int weight[]              = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = LuckyCycle().getEdge(vector <int>(edge1, edge1 + (sizeof edge1 / sizeof edge1[0])), vector <int>(edge2, edge2 + (sizeof edge2 / sizeof edge2[0])), vector <int>(weight, weight + (sizeof weight / sizeof weight[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
  if (argc == 1) {
    for (int test = 5; test < 10; ++test) {
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
