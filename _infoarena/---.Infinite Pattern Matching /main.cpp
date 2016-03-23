#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 60
#define maxData 777

class big_number {
    public:
        int dim;
        int data[maxData];

        void init() {
            dim = 0;
            memset(data, 0, sizeof(data));
        }

        void get_from(char *from, int l, int r) {
            init();
            for (int i = r; i >= l; i--)
                data[++dim] = (from[i] == '0' ? 0 : 1);
        }

        void get_from_sp(char *from, int l, int r) {
            for (int i = r; i >= l; i--)
                data[++dim] = (from[i] == '0' ? 0 : 1);
        }

        void incr() {
            data[1]++;

            for (int i = 1; data[i] > 1; i++) {
                data[i + 1]++;
                data[i] = 0;
                dim = max(dim, i);
            }

            if (data[dim + 1] != 0) dim++;
        }

        void decr() {
            data[1]--;

            for (int i = 1; data[i] < 0; i++) {
                data[i] += 2;
                data[i + 1]--;
            }

            while (dim > 0 && data[dim] == 0)
                dim--;
        }

        bool isEqual(char *from, int l, int r, int nr_l, int nr_r) {
            int pos = dim - nr_r + 1;

            if (nr_r - nr_l + 1 != r - l + 1)
                return false;

            for (int i = r; i >= l; i--) {
                if (from[i] - '0' != data[pos])
                    return false;
                pos++;
            }

            return true;
        }

        void operator=(const big_number& who) {
            dim = who.dim;
            memcpy(data, who.data, sizeof(data));
        }

        bool operator<(const big_number& who) {
            if (dim < who.dim)
                return true;
            if (dim > who.dim)
                return false;

            for (int i = dim; i > 0; i--) {
                if (data[i] < who.data[i])
                    return true;
                if (data[i] > who.data[i])
                    return false;
            }

            return false;
        }

        void operator*=(int x) {
            for (int i = 1; i <= dim; i++)
                data[i] *= x;

            for (int i = 1; i <= dim; i++) {
                data[i + 1] += data[i] >> 1;
                data[i] &= 1;
                if (data[dim + 1] != 0) dim++;
            }
        }

        void set_pow(int x) {
            init();
            dim = x;
            data[x] = 1;
        }

        void operator-=(const big_number& who) {
            for (int i = 1; i <= who.dim; i++)
                data[i] -= who.data[i];

            for (int i = 1; i <= dim; i++) {
                if (data[i] < 0) {
                    data[i] += 2;
                    data[i + 1]--;
                }
            }

            while (dim > 0 && data[dim] == 0)
                dim--;
        }

        void print() {
            for (int i = dim; i > 0; i--)
                printf("%d", data[i]);
        }

        //!---------------------------------

        void base_pow() {
            for (int i = 1; i <= dim; i++)
                data[i] *= 2;

            for (int i = 1; i <= dim; i++) {
                data[i + 1] += data[i] / 10;
                data[i] %= 10;
                if (data[dim + 1] != 0) dim++;
            }
        }

        void base_add(const big_number& who) {
            dim = max(dim, who.dim);
            for (int i = 1; i <= dim; i++)
                data[i] += who.data[i];

            for (int i = 1; i <= dim; i++) {
                if (data[i] >= 10) {
                    data[i + 1] += data[i] / 10;
                    data[i] %= 10;
                }
            }
            if (data[dim + 1] > 0) dim++;
        }
};

int n, i;
char B[maxN];

big_number ans;
big_number aux;
int ans_rem;

big_number how;
big_number ans_dec;

void test_more() {
    int i, j, l;

    for (i = 1; i <= n; i++) {
        if (B[i] == '0') continue;

        for (j = 2 * i - 1; j <= n; j++) {
            //! the main number is set
            l = j - i + 1;
            aux.get_from(B, i, j);

            bool bad = false;

            aux.decr();
            if (aux.dim == 1 && aux.data[1] == 0) bad = true;
            bad |= !aux.isEqual(B, 1, i - 1, aux.dim - i + 2, aux.dim);
            aux.incr();

            int k;
            for (k = j + 1; k <= n; k += aux.dim) {
                aux.incr();
                bad |= !aux.isEqual(B, k, min(k + aux.dim - 1, n), 1, min(aux.dim, n - k + 1));
            }

            if (bad == false) {
                if (ans < aux) continue;
                ans = aux;
                ans_rem = k - n - 1;
            }
        }
    }
}

bool isGood(int bef, big_number& l, big_number& r) {
    if (l.dim < bef)
        return false;
    if (r.dim < n - bef)
        return false;

    for (int i = bef; i > 0; i--)
        if (l.data[bef - i + 1] != B[bef])
            return false;
    for (int i = n; i > bef; i--)
        if (r.data[ r.dim - (n - bef) + (n - i + 1) ] != B[i])
            return false;

    return true;
}

void improve(int bef) {
    big_number l, r;

    r = aux;
    l = r;
    l.decr();

    while (l.data[bef] == l.data[bef + 1]) {
        for (int i = bef; i <= l.dim; i++)
            l.data[i] = l.data[i + 1];
        l.dim--;

        r = l;
        r.incr();

        if (!isGood(bef, l, r)) break;
        aux = r;
    }
}

void test_again() {
    int i;

    for (i = 2; i <= n; i++) {
        if (B[i] == '0') continue;

        aux.get_from(B, 1, i - 1);
        aux.get_from_sp(B, i, n);
        aux.incr();

        improve(i - 1);

        if (aux < ans) {
            ans = aux;
            ans_rem = ans.dim - (n - i + 1);
        }
    }
}

int main()
{
    freopen("infinitepatternmatching.in","r",stdin);
    freopen("infinitepatternmatching.out","w",stdout);

    scanf("%s",B + 1);
    n = strlen(B + 1);

    B[0] = '1';
    if (B[1] == '0')
        ans.get_from(B, 0, n);
    else
        ans.get_from(B, 1, n);

    test_again();
    test_more();


    how.init();
    aux.init();

    how = ans;
    how.incr();
    how *= ans.dim;

    for (i = 1; i < ans.dim; i++) {
        aux.set_pow(i + 1);
        how -= aux;
    }

    while (ans_rem > 0) {
        how.decr();
        ans_rem--;
    }

    how.decr();

    ans_dec.init();
    aux.init();
    aux.data[1] = 1;
    aux.dim = 1;

    for (i = 1; i <= how.dim; i++) {
        if (how.data[i] == 1)
            ans_dec.base_add(aux);
        aux.base_pow();
    }

    ans_dec.print();

    return 0;
}
