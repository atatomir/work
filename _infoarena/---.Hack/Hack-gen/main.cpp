#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

//! demo code

#define PII pair<int, int>
#define VI vector<int>

const int INFINIT = 1000000;
const int dx[5] = {0, 0, 1, -1};
const int dy[5] = {1, -1, 0, 0};

int getDistance(vector<string> &A, PII start) {
    int n = A.size(), m = A[0].size();
    int COUNTER = 0;

    start.first--, start.second--; // reindexam de la 0.

    queue<PII> Q;
    vector<VI> d(n, vector<int> (m, INFINIT));
    d[start.first][start.second] = 0;
    Q.push(start);

    while(!Q.empty()) {
        PII node = Q.front();
        Q.pop();

        COUNTER++;

        for(int dir = 0; dir < 4; ++dir) {
            int newX = node.first + dx[dir];
            int newY = node.second + dy[dir];
            if(newX < 0 || newX >= n || newY < 0 || newY >= m)
                continue;
            int cost = 0;
            if(A[node.first][node.second] != A[newX][newY])
                cost = 1;

            if(d[node.first][node.second] + cost < d[newX][newY]) {
                d[newX][newY] = d[node.first][node.second] + cost;
                Q.push({newX, newY});
            }
        }
    }

    return COUNTER;
}

//!-----

int n, m, i, j;
vector<string> ans;
string a, b;


int try_it() {
    n = 50;

    a.resize(n);
    b.resize(n);
    for (i = 0; i < n; i++) {
        a[i] = i % 2 + '0';
        b[i] = '0';
    }

    ans.resize(n, a);

    for (i = 0; i < n; i++)
        ans[i] = a;

    for (j = 1; j < n; j += 2) {
        if ( (j / 2) % 2 == 0 )
            ans[n - 1][j] = '0';
        else
            ans[0][j] = '0';
    }


    /*for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            ans[i][j] = rand() % 2 + '0';
    */

    return getDistance(ans, make_pair(1, 1));
}

int main()
{
    freopen("ans.out", "w", stdout);

    bool good = false;
    srand(time(NULL));

    int best = 0;
    int how = 2;
    while (!good && --how) {
        int v = try_it();

        best = max(best, v);
        if (how % 1000 == 0) {
            cerr << "#" << how << ' ';
            cerr << best << '\n';
        }
        if (v >= 18000) break;
    }

    cerr << getDistance(ans, make_pair(1, 1));
    for (i = 0; i < n; i++)
        printf("%s\n", ans[i].c_str());

    return 0;
}
