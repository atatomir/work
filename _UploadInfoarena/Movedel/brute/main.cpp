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

#define maxN 2016

int n, m, i;

int main()
{
    freopen("movedel.in","r",stdin);
    freopen("movedel.out","w",stdout);

    srand(time(NULL));
    scanf("%d%d", &n, &m);

    for (i = 1; i <= n; i++) printf("%c", 'a' + (rand () % 26)); printf("\n");
    for (i = 1; i <= n; i++) printf("%c", 'a' + (rand () % 26)); printf("\n");


    return 0;
}
