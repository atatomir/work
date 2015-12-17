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
vector< pair<int, int> > moves;

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

    printf("LDA %d\nSTA [0]\nHLT\n\n", id);
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

    printf("HLT\nHLT\nHLT\n\n");
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("04_gottaCircleAround.tech","w",stdout);
    cerr << "no , (how, id)\n";

    int comm, how, id, i;
    scanf("%d", &comm);
    for(; comm > 0; comm--) {
        scanf("%d%d", &how, &id);
        how_many += how;
        moves.pb(mp(how, id));
    }

    printf("LDA [10000]\nSUBA 4\nJGE [10000]\n\n");
    printf("LDA %d\nSTA [10000]\n", how_many * 4 + 4 - 3 - 1);
    print_move(moves[0].second);

    for (i = moves.size() - 1; i >= 0; i--) {
        for (int j = 1; j < moves[i].first; j++) {
            if (i != moves.size() - 1) {
                printf("STA [10000]\n");
                print_move_HLT(moves[i].second);
            } else {
                print_move_HLT(moves[i].second);
                printf("HLT\n\n");
            }
        }

        if (moves[i].first > 0 && i != 0) {
            printf("STA [10000]\n");
            print_move(moves[i].second);
        }
    }


    return 0;
}
