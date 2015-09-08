#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 811
#define maxValue 100011

int n,m,i,j,q,pos,csort_pos;
int matrix[maxN][maxN];
int id[maxN][maxN];
pair<short,short> countSort[maxN*maxN];
char op;

int w_count;
int work[maxN * maxN];
int next_left[maxN * maxN];
int next_right[maxN * maxN];

int act_dim,act_pos,act;

int getNextLeft(int node) {
    if (next_left[node] == node) return node;
    next_left[node] = getNextLeft(next_left[node]);
    return next_left[node];
}

int getNextRight(int node) {
    if (next_right[node] == node) return node;
    next_right[node] = getNextRight(next_right[node]);
    return next_right[node];
}

int set_unavailable(int node) {
    next_left[node] = next_left[node - 1];
    next_right[node] = next_right[node + 1];
}

void removeElement(int line,int column) {
    int pos_del = id[line][column];
    act_dim--;
    matrix[line][column] = 0;

    if (pos_del < act_pos) { //! left
        act--;
        set_unavailable(pos_del);

    } else{
        if (pos_del > act_pos) { //! right
            set_unavailable(pos_del);

        } else { //! exactly there...
            act--;
            set_unavailable(pos_del);
            if (act > 0) {
                act_pos = getNextLeft(act_pos);
            } else {
                act_pos = getNextRight(act_pos);
                act++;
            }

        }
    }
}

bool my_cmp(const pair<int, int> &a, const pair<int, int> &b) {
    return matrix[a.first][a.second] < matrix[b.first][b.second];
}

int main()
{
    freopen("amedie.in","r",stdin);
    freopen("amedie.out","w",stdout);

    scanf("%d%d%d",&n,&m,&q);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d",&matrix[i][j]);
            countSort[++csort_pos] = mp(i, j) ;
        }
    }

    sort(countSort + 1, countSort + csort_pos + 1, my_cmp);

    for (i = 1; i <= csort_pos; i++) {
        work[++w_count] = matrix[countSort[i].first][countSort[i].second];
        id[countSort[i].first][countSort[i].second] = w_count;
    }

    for (i = 1; i <= w_count; i++) next_left[i] = next_right[i] = i;

    act_dim = w_count; //! dimensiune virtuala
    act_pos = (act_dim + 1) / 2; //! pozitie reala in sir
    act = act_pos; //! pozitie virtuala in sir

    scanf("\n");
    for (; q > 0; q--) {
        scanf("%c",&op);
        if (op == 'Q') {
            scanf("\n");

            int target = (act_dim + 1)/ 2;
            while (act < target) {
                act++;
                act_pos = getNextRight(act_pos + 1);
            }
            while (act > target) {
                act--;
                act_pos = getNextLeft(act_pos - 1);
            }

            printf("%d\n",work[act_pos]);
        }
        if (op == 'L') {
            scanf("%d\n",&pos);

            for (i = 1; i <= m; i++)
                if (matrix[pos][i] != 0) removeElement(pos,i);
        }
        if (op == 'C') {
            scanf("%d\n",&pos);

            for (i = 1; i <= n; i++)
                if (matrix[i][pos] != 0) removeElement(i,pos);
        }
    }

    return 0;
}
