#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

int a, b, i;
vector<string> v;

void generate_it() {
    v.clear();
    v.pb("a");

    while (v.size() < b) {
        int ini = v.size();

        for (char ch = 'a'; ch <= 'z'; ch++) {
            for (i = 0; i < ini; i++)
                v.pb( v[i] + ch );

            if (v.size() >= b) break;
        }
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d %d", &a, &b);

    generate_it();
    for (i = 0; i < b; i++)
        printf("%s ", v[i].c_str());

    return 0;
}
