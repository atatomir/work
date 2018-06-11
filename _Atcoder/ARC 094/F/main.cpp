#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int mod = 998244353;

string s, saux;
map<string, bool> M;
int cnt;
queue<string> Q;

int ss, dd, i;
int dp[2][3][3][2]; //! pos, last, sum, done

char dif(char a, char b) {
    if (a == b) return '!';
    if ('a' != a && 'a' != b) return 'a';
    if ('b' != a && 'b' != b) return 'b';
    return 'c';
}

void brute() {
    string act, aux;

    Q.push(s);
    M[s] = true;
    cnt = 1;

    while (!Q.empty()) {
        act = Q.front(); Q.pop();

        for (i = 1; i < act.size(); i++) {
            aux = act;
            if (aux[i - 1] != aux[i]) {
                aux[i - 1] = aux[i] = dif(aux[i - 1], aux[i]);
                if (!M[aux]) {
                    M[aux] = true;
                    cnt++;
                    Q.push(aux);
                }
            }
        }


    }

    cout << cnt;
}

void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

/*bool check(string act) {
    int sum = 0;

    for (auto e : act) sum += e - 'a';
    sum %= 3;
    if (sum != 1) return false;

    if (act == s) return true;
    for (int i = 1; i < 4; i++)
        if (act[i - 1] == act[i])
            return true;

    return false;
}*/

int main()
{
    freopen("test.in","r",stdin);

    cin >> s;
    if (s.size() <= 3) {
        brute();
        return 0;
    }

    /*int many = 0;
    for (int cc = 0; cc < 3 * 3 * 3 * 3; cc++) {
        int aux = cc;
        saux = "";

        while (saux.size() != 4) {
            saux.pb('a' + (aux % 3));
            aux /= 3;
        }

        if (check(saux)) cerr << saux << ' ' << ++many << '\n';
    }*/

    ss = 0; dd = 1;
    dp[ss][0][0][0] = 1;
    dp[ss][1][1][0] = 1;
    dp[ss][2][2][0] = 1;

    for (i = 2; i <= s.size(); i++) {
        memset(dp[dd], 0, sizeof(dp[dd]));

        for (int last = 0; last < 3; last++) {
            for (int sum = 0; sum < 3; sum++) {
                for (int done = 0; done < 2; done++) {

                    for (int nxt = 0; nxt < 3; nxt++) {
                        int new_sum = (sum + nxt) % 3;
                        int new_done = (last == nxt ? 1 : done);

                        add(dp[dd][nxt][new_sum][new_done], dp[ss][last][sum][done]);
                    }

                }
            }
        }

        swap(ss, dd);
    }

    int need = 0;
    for (auto e : s) need += e - 'a';

    need %= 3;
    add(cnt, dp[ss][0][need][1]);
    add(cnt, dp[ss][1][need][1]);
    add(cnt, dp[ss][2][need][1]);

    for (i = 1; i < s.size(); i++)
        if (s[i - 1] == s[i])
            break;

    if (i == s.size()) add(cnt, 1);

    for (i = 1; i < s.size(); i++)
        if (s[i - 1] != s[i])
            break;

    if (i == s.size()) cnt = 1;

    cout << cnt;



    return 0;
}
