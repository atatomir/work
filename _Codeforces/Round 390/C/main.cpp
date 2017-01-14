#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111

int t, ti, i, j, n, m;
string names[maxN];
map< string, int > ids;
string l[maxN];

bool maybe[maxN][maxN];
string work;
int pos;

string ans[maxN];
int his_id[maxN];


bool is_ok(char c) {
    if ('0' <= c && c <= '9') return true;
    if ('A' <= c && c <= 'Z') return true;
    if ('a' <= c && c <= 'z') return true;
    return false;
}

bool get_word(string &s) {
    for (; pos < work.size() && !is_ok(work[pos]); pos++);

    s.clear();
    for (; pos < work.size() && is_ok(work[pos]); pos++)
        s.pb(work[pos]);

    if (s.empty()) return false;
    return true;
}

void parse(int ln) {
    string aux;
    int id, i;

    work = l[ln];
    pos = 0;
    if (work[0] != '?') {
        get_word(aux);
        id = ids[aux];

        ans[ln] = names[id];
        for (i = 1; i <= n; i++)
            if (i != id)
                maybe[ln][i] = false;

        his_id[ln] = id;
    }

    while (get_word(aux)) {
        id = ids[aux];
        maybe[ln][id] = false;
    }
}

void no_sol() {
    printf("Impossible\n");
}

void solve() {
    int i, j, cnt;
    int last;

    for (int step = 1; step <= 4 * m + 3; step++) {
        for (i = 1; i <= m; i++) {

            if (ans[i].empty()) {
                cnt = 0;
                for (j = 1; j <= m; j++)
                    if (maybe[i][j])
                        cnt++, last = j;

                if (cnt == 0) {
                    no_sol();
                    return;
                }

                if (cnt == 1) {
                    ans[i] = names[last];
                    his_id[i] = last;
                }
            }

            if (ans[i].empty() == false) {
                maybe[i - 1][ his_id[i] ] = false;
                maybe[i + 1][ his_id[i] ] = false;
            }
        }
    }


    for (i = 1; i <= m; i++) {
        if (ans[i].empty()) {
            no_sol();
            return;
        }

        if (maybe[i][ his_id[i] ] == false) {
            no_sol();
            return;
        }
    }

    for (i = 1; i <= m; i++) {
        cout << ans[i] << ":";

        for (j = 0; l[i][j] != ':'; j++);

        for (j++; j < l[i].size(); j++) cout << l[i][j];

        cout << '\n';
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> t;
    for (ti = 1; ti <= t; ti++) {
        ids.clear();

        cin >> n;
        for (i = 1; i <= n; i++) {
            cin >> names[i];
            ids[names[i]] = i;
        }

        cin >> m;

        for (i = 1; i <= m; i++) {
            ans[i] = "";
            for (j = 1; j <= m; j++)
                maybe[i][j] = true;
        }


        getline(cin, l[0]);

        for (int ln = 1; ln <= m; ln++) {
            getline(cin, l[ln]);

            parse(ln);
        }

        solve();
    }



    return 0;
}
