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

#define sigma 26
#define maxN 2000011

#define ends atatomir
#define mod 51123987LL

struct node {
    node* son[sigma];
    int len;
    node* fail;
    int cnt;

    node(int _len) {
        memset(son, 0, sizeof(son));
        len = _len;
        if (len > 0) cnt = 1;
        fail = NULL;
    }
};

char work[maxN];
node *nul_even, *nul_odd;
node *suff;

int n, i;
ll ends[maxN];
ll begins[maxN];

ll ans, total;

void clear_path(node* act) {
    for (int i = 0; i < sigma; i++)
        if (act->son[i] != NULL)
            clear_path(act->son[i]);
    delete act;
}

void init() {
    nul_odd = new node(-1); nul_odd->fail = nul_odd;
    nul_even = new node(0); nul_even->fail = nul_odd;
    suff = nul_odd;
}

int add_letter(int pos) {
    int go = work[pos] - 'a';

    //! get the act suffix
    while (work[pos] != work[pos - suff->len - 1]) suff = suff->fail;
    if (suff->son[go] != NULL) {
        suff = suff->son[go];
        return suff->cnt;
    }

    //! create new node
    suff->son[go] = new node(suff->len + 2);
    node* aux = suff->fail;
    suff = suff->son[go];

    //! if it has no fail edge..
    if (suff->len == 1) {
        suff->fail = nul_even;
        return suff->cnt;
    }

    //! get the fail edge
    while (work[pos] != work[pos - aux->len - 1]) aux = aux->fail;
    aux = aux->son[go];

    suff->fail = aux;
    suff->cnt += aux->cnt;

    return suff->cnt;
}



int main()
{
    //freopen("palisection.in","r",stdin);

    scanf("%d\n%s", &n, work + 1);

    //! compute ends
    init();
    for (i = 1; i <= n; i++) ends[i] = add_letter(i), total += ends[i];

    //! compute begins
    clear_path(nul_even);
    clear_path(nul_odd);
    reverse(work + 1, work + n + 1);
    init();
    for (i = 1; i <= n; i++) begins[n - i + 1] = add_letter(i);

    //! compute ans
    for (i = 2; i <= n; i++) ends[i] = (ends[i] + ends[i - 1]) % mod;
    if (total % 2 == 0)
        ans = (((total / 2) % mod) * (total - 1)) % mod;
    else
        ans = ((((total - 1) / 2) % mod) * total) % mod;

    for (i = 2; i <= n; i++)
        ans = (ans + mod - (begins[i] * ends[i - 1]) % mod) % mod;

    printf("%lld", ans);


    return 0;
}
