#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define inf 1000

int main()
{
    srand(time(NULL));

    freopen("test.in","w",stdout);

    printf("100000 300\n");
    for (int i = 1; i <= 100000; i++)
        printf("%d %d\n", rand() % inf, rand() % inf);


    return 0;
}
