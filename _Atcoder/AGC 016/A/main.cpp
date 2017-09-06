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

int n, i, j, ans;
string s;
char c;

bool any_dif(string aux, char c) {
    for (int i = 0; i < aux.size(); i++)
        if (aux[i] != c)
            return true;
    return false;
}

int solve(char c) {
    int ans = 0, i;
    string aux;

    aux = s;
    while (!aux.empty() && any_dif(aux, c)) {
        ans++;
        for (i = 0; i + 1 < aux.size(); i++) {
            if (aux[i] == c || aux[i + 1] == c)
                aux[i] = c;
        }
        aux.pop_back();
    }

    return ans;
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> s;
    ans = s.size() - 1;

    for (c = 'a'; c <= 'z'; c++) {
        ans = min(ans, solve(c));
    }

    cout << ans;

    return 0;
}
