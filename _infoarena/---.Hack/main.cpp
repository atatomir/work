#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int i, j, n = 50;
vector<string> ans;
string a;

void generate_it() {
    a.resize(n);
    for (i = 0; i < n; i++)
        a[i] = i % 2 + '0';

    ans = vector<string>(n, a);

    for (j = 1; j < n; j += 2) {
        if (j % 4 == 1)
            ans[n - 1][j] = '0';
        else
            ans[0][j] = '0';
    }
}

int main()
{
    ofstream fout("hack.out");

    generate_it();

    fout << "50 50 1 1" << '\n';
    for (i = 0; i < n; i++)
        fout << ans[i] << '\n';

    return 0;
}
