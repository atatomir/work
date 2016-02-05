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


int main()
{
    freopen("zuzu.out","w",stdout);

    srand(time(NULL));

    printf("40 15\n");
    for (int i = 1; i <= 40; i++) {
        printf("%d %d %d %d %d %d %d\n", rand() % 1000,
                                         rand() % 1000,
                                         rand() % 1000,
                                         rand() % 1000,
                                         rand() % 1000,
                                         rand() % 1000,
                                         rand() % 6 + 1);
    }


    return 0;
}
