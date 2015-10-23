#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024
#define pos j
#define ha aux[j]

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);
            reFill();
        }

        Buffer& operator>>(int &dest) {
            while (!isDigit(data[pos])) {
                if (++pos == dim) reFill();
            }
            dest = 0;
            while(isDigit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        void reFill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
        bool isDigit(char c) {
            return ('0' <= c) && (c <= '9');
        }
};
Buffer fin("cladiri.in", 1 << 20);

int n, m, dx, dy, i, j;
int matrix[maxN][maxN];
int aux_matrix[maxN][maxN];

int aux[maxN];
int how[maxN];

pair<int, int> S[maxN]; //! pos, h
int dim;

int l_up[maxN];
int l_down[maxN];
int c_left[maxN];
int c_right[maxN];
int ans;

void compute(int *dest) {
    memset(aux, 0, sizeof(aux));
    memset(how, 0, sizeof(how));

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++)
            aux[j] = (matrix[i][j] == 1 ? 0 : 1 + aux[j]);

        dim = 1;
        S[dim] = (mp(0, -1));
        for (j = 1; j <= m; j++) {
            //!---------------
            while (S[dim].second >= ha) dim--;
            how[j] = pos - S[dim].first;
            S[++dim] = (mp(pos, ha));
            //!---------------
        }

        dim = 1;
        S[dim] = (mp(m + 1, -1));
        for (j = m; j > 0; j--) {
            //!---------------
            while (S[dim].second >= ha) dim--;
            how[j] += -pos + S[dim].first;
            S[++dim] = (mp(pos, ha));
            //!---------------
        }

        dest[i] = dest[i - 1];
        for (j = 1; j <= m; j++)
            dest[i] = max(dest[i], (how[j] - 1) * aux[j]);
    }
}

void swap_up_down() {
    for (i = n / 2; i > 0; i--)
        for (j = 1; j <= m; j++)
            swap(matrix[i][j], matrix[n - i + 1][j]);
}

void swap_diagonal() {
    memcpy(aux_matrix, matrix, sizeof(matrix));

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            matrix[j][i] = aux_matrix[i][j];

    /*for (i = 1; i <= n; i++)
        for (j = i + 1; j <= m; j++)
            swap(matrix[j][i], matrix[i][j]);*/

    swap(n, m);
}

void swap_vect(int *v, int dim) {
    int a = 1;
    int b = dim;

    while (a < b) {
        swap(v[a], v[b]);
        a++; b--;
    }
}

int main()
{
    //freopen("cladiri.in","r",stdin);
    freopen("cladiri.out","w",stdout);

    fin >> n >> m >> dy >> dx;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            fin >> matrix[i][j];

    //! up - horizontal
    compute(l_up);

    //! down - horizontal
    swap_up_down();
    compute(l_down);
    swap_up_down();

    //! left - vertical
    swap_diagonal();
    compute(c_left);

    //! right - vertical
    swap_up_down();
    compute(c_right);
    swap_up_down();
    swap_diagonal();

    swap_vect(l_down, n);
    swap_vect(c_right, m);

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            matrix[i][j] = matrix[i][j] + matrix[i - 1][j] + matrix[i][j - 1] - matrix[i - 1][j - 1];

    for (i = dx; i <= n; i++) {
        for (j = dy; j <= m; j++) {
            int how_good = matrix[i][j] - matrix[i - dx][j] - matrix[i][j - dy] + matrix[i - dx][j - dy];
            if (how_good == 0) {
                int aux_val = max(max(l_up[i - dx], l_down[i + 1]), max(c_left[j - dy], c_right[j + 1]));

                ans = max(ans, aux_val);
            }
        }
    }

    printf("%d", ans);

    //for (i = 1; i <= m; i++) cerr << c_right[i] << '\n';


    return 0;
}
