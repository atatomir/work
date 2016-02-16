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
#define ll long long

#define maxN 1024

int n, i, pos;
char s[maxN];
map<string, int> Quantity;
int full_time;

string aux;

bool is_letter(char c) {
    return 'a' <= c && c <= 'z';
}

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

void jump_blank() {
    while (pos <= n && s[pos] == ' ') pos++;
}

int get_number() {
    jump_blank();

    int ans = 0;
    while (is_digit(s[pos])) {
        ans = ans * 10 + s[pos] - '0';
        pos++;
    }

    return ans;
}

string get_name() {
    string ans;
    ans.clear();
    jump_blank();

    while (is_letter(s[pos])) {
        ans.pb(s[pos]);
        pos++;
    }

    return ans;
}

int main()
{
    freopen("reteta2.in","r",stdin);
    freopen("reteta2.out","w",stdout);

    gets(s + 1);
    n = strlen(s + 1);

    pos = 1;
    jump_blank();
    while (pos <= n) {
        jump_blank();
        if (s[pos] == '(') {
            pos++;
            continue;
        }

        if (s[pos] == ')') {
            pos++;
            full_time += get_number();
            continue;
        }

        aux = get_name();

        //cerr << aux << '\n';

        Quantity[aux] += get_number();

        jump_blank();
    }

    printf("%d\n", full_time);
    for (auto e : Quantity)
        printf("%s %d\n", &e.first[0], e.second);


    return 0;
}
