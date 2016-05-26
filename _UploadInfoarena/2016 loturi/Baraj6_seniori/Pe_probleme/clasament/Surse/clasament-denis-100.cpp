#include <cassert>
#include <fstream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <bitset>
#include <set>
#include <cmath>
#include <iomanip>
#include <map>
#include <stack>
#include <vector>
#include <bitset>
//#include <iostream>

using namespace std;

#define FOR(i, a, n) for (int i = a; i <= n; ++i)
#define ROF(i, a, n) for (int i = n; i >= a; i--)
#define FIT(i, v) for (auto &i : v)
#define pb push_back
#define mp make_pair
#define mt make_touple
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define sz(x) ((int)(x).size())
typedef long long ll;
typedef pair<int,int> pii;
const int mod = 1000000009;
ll powmod(ll a, ll b) {ll res=1; a %= mod; assert(b >= 0); for(; b; b >>= 1) {if (b & 1) res = res * a % mod; a = a * a % mod;} return res;}

ifstream cin("ar.in");
ofstream cout("ar.out");

const int maxN = 100000;
const int maxM = 500000;
const int N = maxN + 5;
const int M = maxM + 5;

class TreapNode {
private:
    pair<ll, ll> hash;
    long long basePow1, basePow2;
    static int base;
    static int mod1;
    static int mod2;
public:
    TreapNode *l, *r;
    double score;
    int index, pr;
    
    long long getBasePow1() {
        return basePow1;
    }
    long long getBasePow2() {
        return basePow2;
    }
    pair<ll,ll> getHash() {
        return hash;
    }
    void update() {
        long long bpa1, bpa2, bpb1, bpb2;
        pair<ll,ll> ha, hb;
        if (!this->l) {
            bpa1 = 1;
            bpa2 = 1;
            ha = {0,0};
        } else {
            bpa1 = this->l->getBasePow1();
            bpa2 = this->l->getBasePow2();
            ha = this->l->getHash();
        }
        if (!this->r) {
            bpb1 = 1;
            bpb2 = 1;
            hb = {0,0};
        } else {
            bpb1 = this->r->getBasePow1();
            bpb2 = this->r->getBasePow2();
            hb = this->r->getHash();
        }
        
        this->basePow1 = bpa1 * bpb1 % mod1 * base % mod1;
        this->basePow2 = bpa2 * bpb2 % mod2 * base % mod2;
        this->hash = {((ha.first * base + this->index) % mod1 * bpb1 + hb.first) % mod1, ((ha.second * base + this->index) % mod2 * bpb2 + hb.second) % mod2};
    }
    TreapNode(int index, double score) {
        this->pr = rand();
        this->l = this->r = NULL;
        this->basePow1 = this->basePow2 = base;
        this->hash = {index, index};
        this->index = index;
        this->score = score;
    }
};
int TreapNode::base = 666013;
int TreapNode::mod1 = 1000000000 + 7;
int TreapNode::mod2 = 1000000000 + 9;
class Treap {
public:
    TreapNode* root;
    
    pair<ll,ll> getHash() {
        return root->getHash();
    }
    void split(TreapNode* t,double score,TreapNode* &l,TreapNode* &r) {
        if(!t) {
            l = r = NULL;
        }
        else if(score < t->score) {
            split(t->l, score, l, t->l), r=t;
        } else {
            split(t->r, score, t->r, r), l=t;
        }
        if (t) {
            t->update();
        }
    }
    void merge(TreapNode* &t,TreapNode* l,TreapNode* r) {
        if(!l||!r) {
            t = l ? l : r;
        } else if(l->pr > r->pr) {
            merge(l->r, l->r, r), t=l;
        } else {
            merge(r->l, l, r->l), t=r;
        }
        if (t) {
            t->update();
        }
    }
    void insert(TreapNode* &t, TreapNode* it) {
        if (!t) {
            t = it;
            return;
        } else if (it->pr > t->pr) {
            split(t, it->score, it->l, it->r), t = it;
        } else {
            insert(it->score > t->score ? t->r : t->l, it);
        }
        if (t) {
            t->update();
        }
    }
    void erase(TreapNode* &t, double score) {
        if (!t) {
            return;
        }
        if(t->score == score) {
            TreapNode *aux;
            merge(aux, t->l, t->r);
            delete(t);
            t = aux;
        }
        else {
            erase(score > t->score ? t->r : t->l, score);
        }
        if (t) {
            t->update();
        }
    }
};
int main() {
    ifstream cin("clasament.in");
    ofstream cout("clasament.out");
    int n, m;
    cin >> n >> m;
    assert (n >= 1 && n <= maxN);
    assert (m >= 1 && m <= maxM);
    Treap treap;
    vector<double> score(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> score[i];
        TreapNode* node = new TreapNode(i, score[i]);
        treap.insert(treap.root, node);
    }
    
    map<pair<ll,ll>, int> ap;
    ap[treap.getHash()]++;
    for (int i = 1; i <= m; ++i) {
        int x; double y;
        cin >> x >> y;
        treap.erase(treap.root, score[x]);
        score[x] = y - (double)i / (m + 1);
        TreapNode* node = new TreapNode(x, score[x]);
        treap.insert(treap.root, node);
        cout << ap[treap.getHash()] << "\n";
        ap[treap.getHash()]++;
    }
    return 0;
}