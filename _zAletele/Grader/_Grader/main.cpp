#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define mp make_pair
#define pb push_back

int i, j, n;
//!------- Limits ---------
    int tests = 1000;
    int maxVal = 1000;
    int dim= 1000;
//!------------------------

void genTest() {
    FILE *fout = fopen("input.in", "w");

    fprintf(fout, "%d\n", dim);
    for (i = 1; i <= dim; i++)
        fprintf(fout, "%d ", rand() % maxVal - (maxVal / 2) );

    fclose(fout);
}

bool check() {
    int a, b;

    system("./brute");
    freopen("output.out", "r", stdin);
    scanf("%d", &a);

    system("./solution");
    freopen("output.out", "r", stdin);
    scanf("%d", &b);



    if (a == b)
        cerr << "#" << tests << " Passed\n";
    else
        cerr << "Error : " << a << " != " << b << '\n';

    return a == b;
}

int main()
{
    srand(time(NULL));

    while (tests-- > 0) {
        genTest();

        if (!check())
            return 0;
    }

    return 0;
}
