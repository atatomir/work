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

const int maxN = 6011;

int n, i, last, act;
char s[maxN];
vector<string> data;
vector<int> a, b;
int id[maxN];
string ans, aux;

string solve(int bg, int en) {
    string ans = "";
    string aux;
    int i, j, last;

    a.clear();
    b.clear();
    for (i = bg; i <= en; i++) {
        if (s[i] == 'a')
            a.pb(i), id[i] = a.size() - 1;
        else
            b.pb(i), id[i] = b.size() - 1;
    }

    if (s[bg] == 'a') {
        last = 0;
        for (i = 0; i < a.size(); i++) {
            if (a[i] <= last) continue;
            ans += "ab";
            last = b[i];
        }
    } else {
        for (i = 0; i < a.size(); i++) {
            aux.clear();
            for (j = bg; j <= en; j++)
                if (id[j] >= i)
                    aux.pb(s[j]);


            if (aux > ans) ans = aux;
        }
    }

    return ans;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d\n%s", &n, s + 1);
    for (i = 1; i <= 2 * n; i++) {
        if (s[i] == 'a')
            act++;
        else
            act--;

        if (act == 0) {
            data.pb(solve(last + 1, i));
            last = i;
        }
    }

    ans = "";
    for (i = data.size() - 1; i >= 0; i--) {
        aux = data[i] + ans;
        if (aux > ans) ans = aux;
    }

    cout << ans;

    return 0;
}
