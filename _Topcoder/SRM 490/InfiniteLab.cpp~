#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 23
#define dup 50
#define sz ((2 * dup + 4) * maxN)
#define sm_inf 1000000
#define inf (1LL << 60)

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};

int n, m, N, M, i, j;
char maze[sz][maxN];
pair<int, int> T[sz];

int ln;
vector< vector<int> > dist[maxN];
queue< pair<int, int> > Q;

vector<ll> fast[maxN];



void bfs(int x, int y, vector< vector<int> > &data) {
    data = vector< vector<int> >(N + 3, vector<int>(M + 3, sm_inf));

    while (!Q.empty()) Q.pop();

    if (maze[x][y] == '#') return;

    data[x][y] = 0;
    Q.push(mp(x, y));
    while (!Q.empty()) {
        x = Q.front().first;
        y = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++) {
            int xx = x + defX[i];
            int yy = y + defY[i];

            if (maze[xx][yy] != '#' && data[xx][yy] > data[x][y] + 1) {
                data[xx][yy] = data[x][y] + 1;
                Q.push(mp(xx, yy));
            }
        }

        if (maze[x][y] == 'T') {
            int tp;

            if (T[x].first == y)
                tp = T[x].second;
            else
                tp = T[x].first;

            if (maze[x][tp] != '#' && data[x][tp] > data[x][y] + 1) {
                data[x][tp] = data[x][y] + 1;
                Q.push(mp(x, tp));
            }
        }
    }
}

ll get_dec(ll ln) {
    ll ans = 0;
    ll l = dup * n + 1;
    ll r = dup * (n + 1);

    if (ln < l) {
        ll dif = l - ln;

        ln += (dif / n) * n;
        ans += (dif / n) * n;
    }

    if (ln > r) {
        ll dif = ln - r;

        ln -= (dif / n) * n;
        ans -= (dif / n) * n;
    }

    while (ln < l) {
        ln += n;
        ans += n;
    }

    while (ln > r) {
        ln -= n;
        ans -= n;
    }


    return ans;
}

vector< vector<ll> > mult(vector< vector<ll> > &a, vector< vector<ll> > &b) {
    vector< vector<ll> > ans = a;
    int i, j, k;

    for (i = 1; i <= M; i++) {
        for (j = 1; j <= M; j++) {
            ans[i][j] = inf;

            for (k = 1; k <= m; k++) {
                if (a[i][k] >= inf || b[k][j] >= inf) continue;
                ans[i][j] = min(ans[i][j], a[i][k] + b[k][j]);
            }
        }
    }

    return ans;
}

vector< vector<ll> > poww(ll how) {
    vector< vector<ll> > ans, aux;
    int i;

    how--;
    ans.resize(M + 3);
    for (i = 1; i <= M; i++)
        ans[i] = fast[i];

    aux = ans;

    while (how > 0) {
        if (how & 1) ans = mult(ans, aux);
        how >>= 1;
        aux = mult(aux, aux);
    }

    return ans;
}

class InfiniteLab {
public:
    long long getDistance( vector <string> map, long long r1, int c1, long long r2, int c2 )  {
        n = map.size();
        m = map[0].size();

        N = n * (2 * dup + 1); M = m;

        for (i = 0; i < N; i++)
            for (j = 0; j < M; j++)
                maze[i + 1][j + 1] = map[i % n][j];

        for (i = 0; i <= N; i++)
            maze[i][0] = maze[i][M + 1] = '#';
        for (i = 0; i <= M; i++)
            maze[0][i] = maze[N + 1][i] = '#';

        for (i = 1; i <= N; i++) {
            for (j = 1; j <= M; j++) {
                if (maze[i][j] != 'T') continue;

                if (T[i].first == 0)
                    T[i].first = j;
                else
                    T[i].second = j;
            }
        }

        ln = dup * n + 1;
        for (i = 1; i <= m; i++) {
            bfs(ln, i, dist[i]);

            fast[i] = vector<ll>(M + 3, 0);
            for (j = 1; j <= M; j++) {
                if (dist[i][ln - n][j] >= sm_inf)
                    fast[i][j] = (inf);
                else
                    fast[i][j] = dist[i][ln - n][j];
            }
        }

        //! now do the easy work

        r1++; c1++;
        r2++; c2++;

        if (r1 < r2) {
            swap(r1, r2);
            swap(c1, c2);
        }

        ll need = get_dec(r1);
        r1 += need;
        r2 += need;

        if (r2 > 0) {
            bfs(r1, c1, dist[0]);

            if (dist[0][r2][c2] >= sm_inf)
                return -1;
            return dist[0][r2][c2];
        }

        ll how = (ln - r2) / n;
        ll ln2 = ln - how * n;
        ll new_ln = ln - (ln2 - r2);

        auto aux = poww(how);
        ll ans = inf;


        for (i = 1; i <= M; i++) {
            for (j = 1; j <= M; j++) {
                if (dist[i][r1][c1] >= sm_inf) continue;
                if (dist[j][new_ln][c2] >= sm_inf) continue;
                if (aux[i][j] >= inf) continue;

                ans = min(ans, dist[i][r1][c1] + aux[i][j] + dist[j][new_ln][c2]);
            }
        }

        if (ans >= inf)
            return -1;
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
			string map[]              = {"#...##",
 ".##...",
 "..#.##",
 "#.#.##"};
			long long r1              = 1;
			int c1                    = 0;
			long long r2              = 5;
			int c2                    = 3;
			long long expected__      = 7;

			std::clock_t start__      = std::clock();
			long long received__      = InfiniteLab().getDistance(vector <string>(map, map + (sizeof map / sizeof map[0])), r1, c1, r2, c2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string map[]              = {"##.#.",
 ".#T#T",
 "...#.",
 "##.#."};
			long long r1              = 7;
			int c1                    = 4;
			long long r2              = 1;
			int c2                    = 0;
			long long expected__      = 9;

			std::clock_t start__      = std::clock();
			long long received__      = InfiniteLab().getDistance(vector <string>(map, map + (sizeof map / sizeof map[0])), r1, c1, r2, c2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string map[]              = {"..######.#",
 ".###T###.T",
 "..T#.##T##",
 ".######..#"};
			long long r1              = 1;
			int c1                    = 0;
			long long r2              = 6;
			int c2                    = 4;
			long long expected__      = 11;

			std::clock_t start__      = std::clock();
			long long received__      = InfiniteLab().getDistance(vector <string>(map, map + (sizeof map / sizeof map[0])), r1, c1, r2, c2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string map[]              = {"..#..",
 ".#.#.",
 "....."};
			long long r1              = -29;
			int c1                    = 2;
			long long r2              = 19;
			int c2                    = 2;
			long long expected__      = 54;

			std::clock_t start__      = std::clock();
			long long received__      = InfiniteLab().getDistance(vector <string>(map, map + (sizeof map / sizeof map[0])), r1, c1, r2, c2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string map[]              = {".#.#.",
 "..#..",
 ".....",
 ".....",
 "..#.."};
			long long r1              = -999;
			int c1                    = 3;
			long long r2              = 100;
			int c2                    = 2;
			long long expected__      = -1;

			std::clock_t start__      = std::clock();
			long long received__      = InfiniteLab().getDistance(vector <string>(map, map + (sizeof map / sizeof map[0])), r1, c1, r2, c2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string map[]              = ;
			long long r1              = ;
			int c1                    = ;
			long long r2              = ;
			int c2                    = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = InfiniteLab().getDistance(vector <string>(map, map + (sizeof map / sizeof map[0])), r1, c1, r2, c2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string map[]              = ;
			long long r1              = ;
			int c1                    = ;
			long long r2              = ;
			int c2                    = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = InfiniteLab().getDistance(vector <string>(map, map + (sizeof map / sizeof map[0])), r1, c1, r2, c2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string map[]              = ;
			long long r1              = ;
			int c1                    = ;
			long long r2              = ;
			int c2                    = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = InfiniteLab().getDistance(vector <string>(map, map + (sizeof map / sizeof map[0])), r1, c1, r2, c2);
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
