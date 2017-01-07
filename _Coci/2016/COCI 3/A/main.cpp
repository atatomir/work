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

#define maxN 5024

int n, i, j, dim, cnt;
char s[maxN];

bool is_sign(char c) {
    return c == '.' || c == '?' || c == '!';
}

bool lowercase(char c) {
    return 'a' <= c && c <= 'z';
}

bool uppercase(char c) {
    return 'A' <= c && c <= 'Z';
}

bool digit(char c) {
    return '0' <= c && c <= '9';
}

bool good(char c) {
    return lowercase(c) || uppercase(c) || digit(c);
}

bool is_word(string s) {
    if (lowercase(s[0])) return false;

    for (int i = 1; i < s.size(); i++)
        if (!lowercase(s[i]))
            return false;

    return true;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d\n", &n);
    gets(s + 1);
    for (i = 1; n > 0; i++) {
        if (is_sign(s[i])) {
            printf("%d\n", cnt);
            cnt = 0;
            n--;
            continue;
        }

        if (s[i] == ' ') continue;

        string act = "";
        for (j = i; good(s[j]); j++) act += s[j];

        if (is_word(act)) cnt++;

        i = j - 1;
    }

    return 0;
}
