#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

int how_many;

void print_move(int id) {
    if (id == 0)
        printf("//HOLD \n");
    if (id == 1)
        printf("//UP \n");
    if (id == 2)
        printf("//RIGHT \n");
    if (id == 3)
        printf("//DOWN \n");
    if (id == 4)
        printf("//LEFT \n");

    printf("LDA %d\nSTA [0]\nHLT\nHLT\n\n", id);
}

void print_move_HLT(int id) {
    if (id == 0)
        printf("//HOLD \n");
    if (id == 1)
        printf("//UP \n");
    if (id == 2)
        printf("//RIGHT \n");
    if (id == 3)
        printf("//DOWN \n");
    if (id == 4)
        printf("//LEFT \n");

    printf("HLT\nHLT\nHLT\nHLT\n\n");
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("06_beOnYourToes.tech","w",stdout);
    cerr << "no , (how, id)\n";

    printf("LDA [3000]\nADDA 4\nSTA [3000]\nJGE [3000]\n\n");

    int comm, how, id, i;
    scanf("%d", &comm);
    for(; comm > 0; comm--) {
        scanf("%d%d", &how, &id);
        how_many += how;
        print_move(id);
        for (int i = 2; i <= how; i++)
            print_move_HLT(id);
    }

    cerr << "\n" << how_many;

    return 0;
}
