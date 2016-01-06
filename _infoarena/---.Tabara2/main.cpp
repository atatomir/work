#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxS 50001
#define lSon (node << 1)
#define rSon (lSon | 1)

class aint {
    public:
        void init(int _n, int *_data) {
            n = _n;
            data = _data;
        }

        void update(int node, int l, int r, int pos, int val) {
            if (l == r) {
                data[node] = max(data[node],val);
                return;
            }

            int mid = (l + r) >> 1;
            if (pos <= mid)
                update(lSon, l, mid, pos, val);
            else
                update(rSon, mid + 1, r, pos, val);

            data[node] = max(data[lSon], data[rSon]);
        }

        int query(int node, int l, int r, int qL, int qR) {
            if (qL <= l && r <= qR)
                return data[node];

            int ans = 0;

            int mid = (l + r) >> 1;
            if (qL <= mid)
                ans = max(ans, query(lSon, l, mid, qL, qR));
            if (qR >  mid)
                ans = max(ans, query(rSon, mid + 1, r, qL, qR));

            return ans;
        }

    private:
        int n;
        int *data;
};

int loc, s, m, i;
char ch;
int op, a, b;

int dad[maxS];
int place[maxS];
int pay[maxS];

int aint_data[maxS << 2];
aint work;

int Find(int node) {
    if (dad[node] == node)
        return node;
    dad[node] = Find(dad[node]);
    return dad[node];
}

void Merge(int R1, int R2) {
    dad[R2] = R1;
    place[R1] = max(place[R1], place[R2]);
    pay[R1] = max(pay[R1], pay[R2]);

    if (place[R1] != 0)
        work.update(1, 1, s, place[R1], pay[R1]);
}

int main()
{
    freopen("tabara2.in","r",stdin);
    freopen("tabara2.out","w",stdout);

    scanf("%d%d%d\n", &loc, &s, &m);
    for (i = 1; i <= s; i++) {
        scanf("%d", &pay[i]);
        dad[i] = i;
    }
    work.init(s, aint_data);
    scanf("\n");

    for (i = 1; i <= m; i++) {
        scanf("%c", &ch);

        if (ch == 'U') { //! update
            scanf("%d%d%d\n", &op, &a, &b);
            if (op == 1) { //! adauga muchie a-b
                int R1 = Find(a);
                int R2 = Find(b);
                Merge(R1, R2);
            } else { //! asociaza lui b locatia a
                int R = Find(b);
                place[R] = a;
                work.update(1, 1, s, a, pay[R]);
            }
        } else { //! query
            scanf("%d%d\n", &a, &b);

            printf("%d\n", work.query(1, 1, s, a, b));
        }
    }


    return 0;
}
