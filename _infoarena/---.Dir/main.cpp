#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 2016

int n, i, pos, cnt;
string FOLD[maxN];
vector<string> files;

char s[maxN];
vector<int> St;

string aux;

bool is_upper(char c) {
    return 'A' <= c && c <= 'Z';
}

bool is_lower(char c) {
    return 'a' <= c && c <= 'z';
}

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

bool is_good(char c) {
    return is_upper(c) || is_lower(c) || is_digit(c);
}

string get_name() {
    string ans;
    ans.clear();

    while (pos < n && is_good(s[pos]))
        ans.pb(s[pos++]);
    return ans;
}

int main()
{
    freopen("dir.in","r",stdin);
    freopen("dir.out","w",stdout);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    pos = 1;
    while (pos <= n) {
        if (s[pos] == ',') {pos++; continue;}
        if (s[pos] == ')') {
            St.pop_back();
            pos++;
            continue;
        }

        if (is_upper(s[pos])) { //! FOLDER
            FOLD[++cnt] = get_name();
            St.pb(cnt);
            pos++;
        } else { //! file
            aux.clear();
            for (auto e : St) {
                aux += FOLD[e];
                aux.pb('\\');
            }
            aux += get_name();

            files.pb(aux);
        }
    }

    sort(files.begin(), files.end());
    printf("%d\n", files.size());
    for (auto f : files)
        printf("%s\n", &f[0]);


    return 0;
}
