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

#define maxN 500011
#define base 47
#define mod 13777
#define inf 1000000000
#define dbg(work) {print_treap(work); cerr << '\n';}

vector<int> poww;
vector<int> poww2;

struct treap {
    treap* son[2];
    int key;

    int ch;
    int hash;
    int bottom;

    treap(treap* n1, treap* n2, int _key, int _ch) {
        son[0] = n1;
        son[1] = n2;
        key = _key;
        ch = _ch;
        update_node();
    }

    void update_node() {
        if (key == -1) {
            bottom = hash = 0;
            //hash2 = 0;
            return;
        }

        bottom = 1 + son[0]->bottom + son[1]->bottom;
        hash = (poww[son[1]->bottom + 1] * son[0]->hash +
                poww[son[1]->bottom] * ch +
                son[1]->hash) ;
        /*hash2 = (1LL * poww2[son[1]->bottom + 1] * son[0]->hash2 +
                 1LL * poww2[son[1]->bottom] * ch +
                 son[1]->hash2) % mod2;*/
    }
};

treap* nil;

void print_treap(treap* node) {
    if (node == nil) return;

    print_treap(node->son[0]);
    cerr << (char)('a' + node->ch);
    print_treap(node->son[1]);
}

void rot_left(treap* &node) {
    treap* aux = node;

    node = aux->son[0];
    aux->son[0] = aux->son[0]->son[1];
    node->son[1] = aux;
}

void rot_right(treap* &node) {
    treap* aux = node;

    node = aux->son[1];
    aux->son[1] = aux->son[1]->son[0];
    node->son[0] = aux;
}

void balance(treap* &node) {
    if (node->son[0]->key > node->key) rot_left(node);
    if (node->son[1]->key > node->key) rot_right(node);

    node->son[0]->update_node();
    node->son[1]->update_node();
    node->update_node();
}

void insert(treap* &node, int pos, treap* ch) {
    if (node == nil) {
        node = ch;
        return;
    }

    if (pos <= node->son[0]->bottom + 1)
        insert(node->son[0], pos, ch);
    else
        insert(node->son[1], pos - (node->son[0]->bottom + 1), ch);

    balance(node);
}

void erase(treap* &node, int pos) {
    if (node->son[0] == node->son[1]) { //! == nil
        node = nil;
        return;
    }

    int cnt = node->son[0]->bottom + 1;
    if (cnt == pos) {
        if (node->son[0]->key > node->son[1]->key)
            rot_left(node);
        else
            rot_right(node);
    }

    if (pos <= node->son[0]->bottom)
        erase(node->son[0], pos);
    else
        erase(node->son[1], pos - (node->son[0]->bottom + 1) );

    balance(node);
}

pair<treap*, treap*> split(treap* &node, int pos) {
    //! split in [l, pos - 1] ans [pos, r]
    treap* aux = new treap(nil, nil, inf, -1);

    insert(node, pos, aux);
    return mp(node->son[0], node->son[1]);
}

treap* merge(treap* &R1, treap* &R2) {
    treap* aux = new treap(R1, R2, inf, -1);
    erase(aux, aux->son[0]->bottom + 1);
    return aux;
}

int hash_between(treap* &node, int p, int lg) {
    int ans;
    treap* w1, *w2, *w3;
    auto now = split(node, p);
    w1 = now.first;
    w2 = now.second;

    now = split(w2, lg + 1);
    w2 = now.first;
    w3 = now.second;

    /*dbg(w1);
    dbg(w2);
    dbg(w3);
    cerr << "!!\n";*/

    ans = w2->hash;

    w1 = merge(w1, w2);
    node = merge(w1, w3);

    return ans;
}


//! ----------------------------------

int n, m, i;
treap* work, *aux;
char s[maxN];

int op, p1, p2, p, lg;
char c;

int h1, h2;

int main()
{
    srand(time(NULL));
    nil = new treap(NULL, NULL, -1, -1);
    work = nil;

    freopen("diez.in","r",stdin);
    freopen("diez.out","w",stdout);

    poww.pb(1); poww2.pb(1);
    for (i = 1; i < maxN; i++) {
        poww.pb( (poww.back() * base)  );
        //poww2.pb( (poww2.back() * base) % mod2 );
    }

    scanf("%d%d\n%s\n", &n, &m, s + 1);
    for (i = 1; i <= n; i++) {
        aux = new treap(nil, nil, rand() % inf, s[i] - 'a' + 1);
        insert(work, i, aux);
    }



    for (i = 1; i <= m; i++) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %c\n", &p, &c);
            aux = new treap(nil, nil, rand() % inf, c - 'a' + 1);
            insert(work, p + 1, aux);
        } else {
            scanf("%d%d%d", &p1, &p2, &lg);

            if (hash_between(work, p1 + 1, lg) == hash_between(work, p2 + 1, lg))
                printf("1\n");
            else
                printf("0\n");
        }
    }



    return 0;
}
