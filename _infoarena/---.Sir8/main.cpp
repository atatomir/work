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

#define maxSir 60011
#define maxDim 800011

const int base = 1007;
const int moddo = 666013;

int n, cuv, k, i, cnt, cont, refresh;
char s[maxSir];
char aux[maxDim];
vector<int> hashes;
vector<int> dims;

vector< string > bucket;
vector< int > hash_bucket;

int op, poz, a, b, ind, last;
char c;

int poww[maxDim];
int sums[maxSir];

int get_hash(char *from, int l, int r) {
    int ans = 0;
    for (int i = l; i <= r; i++)
        ans = (ans * base + from[i] - 'a') % moddo;
    return ans;
}

int get_hash(string &from, int l, int r) {
    int ans = 0;
    for (int i = l; i <= r; i++)
        ans = (ans * base + from[i] - 'a') % moddo;
    return ans;
}

void bucket_to_char() {
    int i;

    n = 0;
    for (auto act : bucket)
        for (i = 0; i < act.size(); i++)
            s[++n] = act[i];

    bucket.clear();
}

void char_to_bucket() {
    int i, j, dim, limit;
    string act;

    bucket.clear();
    hash_bucket.clear();
    dim = sqrt(n);

    for (i = 1; i <= n; i += dim) {
        act.clear();
        limit = min(i + dim, n + 1);

        for (j = i; j < limit; j++)
            act.pb(s[j]);
        bucket.pb(act);
        hash_bucket.pb( get_hash(act, 0, act.size() - 1) );
    }
}

void add_to(int pos, char c) {
    for (int i = 0; i < bucket.size(); i++) {
        if (bucket[i].size() < pos) {
            pos -= bucket[i].size();
            continue;
        }

        bucket[i].insert(pos - 1, 1, c);
        hash_bucket[i] = get_hash(bucket[i], 0, bucket[i].size() - 1);

        return;
    }
    if (pos == 1) {
        bucket[ bucket.size() - 1 ].pb(c);
        return;
    }

    cerr << "Error! Out of bound...";
}

int get_bucket(int pos) {
    for (int i = 0; i < bucket.size(); i++)
        if (sums[i] >= pos)
            return i;

    cerr << "Error! Out of buckets";
}

int get_big_hash(int l, int r) {
    int i, pos, how;
    int ans = 0;

    sums[0] = bucket[0].size();
    for (i = 1; i < bucket.size(); i++)
        sums[i] = sums[i - 1] + bucket[i].size();

    int b1 = get_bucket(l);
    int b2 = get_bucket(r);
    int pos_l = l - (sums[b1] - bucket[b1].size()) - 1;
    int pos_r = r - (sums[b2] - bucket[b2].size()) - 1;

    if (pos_l < 0)
        return -1;

    if (b1 == b2)
        return get_hash(bucket[b1], pos_l, pos_r);

    //! add first part
    ans = get_hash(bucket[b1], pos_l, bucket[b1].size() - 1);
    //! add full buckets
    for (i = b1 + 1; i < b2; i++)
        ans = (1LL * ans * poww[ bucket[i].size() ] + hash_bucket[i]) % moddo;
    //! add last part
    ans = (1LL * ans * poww[ pos_r + 1 ] + get_hash(bucket[b2], 0, pos_r)) % moddo;

    return ans;
}

int main()
{
    freopen("sir8.in","r",stdin);
    freopen("sir8.out","w",stdout);

    scanf("%s\n%d\n", s + 1, &cuv);
    n = strlen(s + 1);

    for (i = 1; i <= cuv; i++) {
        scanf("%s\n", aux + 1);
        cnt = strlen(aux + 1);

        dims.pb(cnt);
        hashes.pb( get_hash(aux, 1, cnt) );
        memset(aux, 0, cnt + 7);
    }

    char_to_bucket();

    scanf("%d", &k);
    refresh = sqrt(n + k);
    cont = refresh;

    poww[0] = 1;
    for (i = 1; i <= n + k; i++)
        poww[i] = (poww[i - 1] * base) % moddo;

    last = 0;


    for (int kk = 1; kk <= k; kk++) {
        scanf("%d", &op);

        if (--cont == 0) {
            cont = refresh;
            bucket_to_char();
            char_to_bucket();
        }


        if (op == 0) { //! insert
            scanf("%d %c %d %d", &poz, &c, &a, &b);

            if (last == 0)
                poz ^= a;
            else
                poz ^= b;

            add_to(poz, c);
        } else { //! query
            scanf("%d%d%d%d", &poz, &ind, &a, &b);
            ind--;

            if (last == 0)
                poz ^= a;
            else
                poz ^= b;

            int now_hash = get_big_hash(poz - dims[ind] + 1, poz);
            last = (now_hash == hashes[ind]);

            printf("%d\n", last);
        }
    }


    return 0;
}
