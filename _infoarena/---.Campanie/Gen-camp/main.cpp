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


int main()
{
    freopen("campanie.in","w",stdout);

    printf("18\n");
    for (int step = 1; step <= 18; step++) {
        printf("0 0 100 100\n");

        printf("1000\n");
        for (int i = 1; i < 1000; i++)
            printf("10 ");
        printf("\n");

        for (int i = 1; i <= 1000; i++) {
            printf("1000 ");
            for (int j = 1; j <= 1000; j++)
                printf("%d ", j * 10);
            printf("\n");
        }
    }


    return 0;
}
