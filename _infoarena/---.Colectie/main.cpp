#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 35

const int pow_ten[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
const int each_less[9] = {0, 1, 20, 300, 4000, 50000, 600000, 7000000, 80000000};

vector<int> count_cif(int nr) {
    vector<int> ans = vector<int>(10, 0);
    int fr = 0;
    int i, j;
    int dig[9];

    nr++;

    //! get first digit
    while (nr >= 10 * pow_ten[fr]) fr++;
    for (i = 0; i <= fr; i++) dig[i] = (nr / pow_ten[i]) % 10;

    //! add nr with < fr digits
    for (i = fr - 1; i >= 0; i--) {
        for (j = 0; j < 10; j++)
            ans[j] += each_less[i] * 9 + pow_ten[i];
        ans[0] -= pow_ten[i];
    }

    for (i = fr; i >= 0; i--) {
        int cnt = dig[i] ;
        int mv = 0;

        if (i == fr) cnt--, mv = 1;

        for (j = 0; j < 10; j++)
            ans[j] += each_less[i] * cnt;
        for (j = mv; j < cnt + mv; j++)
            ans[j] += pow_ten[i];

        for (j = fr; j > i; j--)
            ans[ dig[j] ] += pow_ten[i] * cnt;
    }

    return ans;
}




int n, k, i, j, lim, cnt, ans;
vector<int> data[maxN];
vector<int> need;
vector<int> cmp;
vector<int> aux;

map< vector<int>, pair<int, int> > M;

int st1, st2;
vector<int> sol;


bool ver(int nr) {
    //! check if function count_fir counts correct
    cmp = vector<int>(10, 0);

    for (int i = 1; i <= nr; i++) {
        int aux = i;

        while (aux) {
            cmp[aux % 10]++;
            aux /= 10;
        }
    }

    for (int i = 0; i < 10; i++)
        if (cmp[i] != need[i])
            return false;

    return true;
}

void add_vect(int id) {
    static int i;
    for (i = 0; i < 10; i++)
        aux[i] += data[id][i];
}

void del_vect(int id) {
    static int i;
    for (i = 0; i < 10; i++)
        aux[i] -= data[id][i];
}



int main()
{
    freopen("colectie.in","r",stdin);
    freopen("colectie.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) {
        data[i].resize(10);
        for (j = 0; j < 10; j++)
            scanf("%d", &data[i][j]);
    }

    ans = n + 1;
    need = count_cif(k);
    //if (!ver(k)) cerr << "Error";

    //! for first half
    lim = 1 << (n / 2);
    k = n / 2;
    for (int state = 0; state < lim; state++) {
        aux = vector<int>(10, 0);
        cnt = 0;

        for (i = 0; i < k; i++)
            if (state & (1 << i))
                add_vect(i + 1), cnt++;

        auto res = M[aux];
        if (res.first == 0 || res.first > cnt)
            M[aux] = mp(cnt, state);
    }

    //! for second half
    i = 1; j = n;
    while (i < j) swap(data[i++], data[j--]);

    lim = 1 << ( (n + 1) / 2 );
    k = (n + 1) / 2;
    for (int state = 0; state < lim; state++) {
        aux = need;
        cnt = 0;

        for (i = 0; i < k; i++)
            if (state & (1 << i))
                del_vect(i + 1), cnt++;

        auto res = M[aux];
        if (res.first != 0 && res.first + cnt < ans) {
            ans = res.first + cnt;
            st1 = res.second;
            st2 = state;
        }
    }

    //! conclude
    for (i = 1; st2; i++, st2 >>= 1)
        if (st2 & 1)
            sol.pb(n - i + 1);

    for (i = 1; st1; i++, st1 >>= 1)
        if (st1 & 1)
            sol.pb(i);

    sort(sol.begin(), sol.end());


    if (ans == n + 1) {
        printf("0");
        return 0;
    }

    printf("1\n%d\n", ans);
    for (int e : sol)
        printf("%d ", e);


    return 0;
}
