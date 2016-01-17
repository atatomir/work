#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back

int dp[17][17];

int main()
{
    ofstream fout("input.in");

    srand(time(NULL));

    fout << 250 << '\n';
    for (int test = 1; test <= 250; test++) {
        fout << "16\n";
        for (int i = 1; i <= 16; i++) {
            for (int j = 1; j <= 16; j++) {
                if (i < j) {
                    dp[i][j] = rand() % 2;
                    dp[j][i] = dp[i][j] ^ 1;
                    fout << dp[i][j] << ' ';
                } else {
                    fout << dp[i][j] << ' ';
                }
            }
            fout << '\n';
        }
    }




    fout.close();

    return 0;
}
