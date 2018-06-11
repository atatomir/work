#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int sigma = 26;

int i, act, j;
string s, ans;
bool used[sigma];

int main()
{
    //freopen("test.in","r",stdin);

    cin >> s;
    if (s.size() != 26) {
        for (auto e : s) used[e - 'a'] = true;
        for (i = 0; used[i]; i++);
        s += (char)('a' + i);
        ans = s;
    } else {
        ans = s;

        for (i = 0; i < s.size(); i++) {
            act = s[i] - 'a';
            used[act] = true;
            for (j = act; j < sigma; j++)
                if (!used[j])
                    break;

            if (j < sigma) {
                ans = s;

                ans[i] = (char)('a' + j);
                while (ans.size() - 1 > i) ans.pop_back();
            }
        }
    }

    if (ans.size() == sigma) {
        cout << -1;
        return 0;
    }

    cout << ans;


    return 0;
}
