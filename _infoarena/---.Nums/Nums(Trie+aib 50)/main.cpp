#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100022
#define def 100000

class aib {
    public:
        void init(int _n,int *_data) {
            n = _n; data = _data;
            memset( data, 0 , (n+5)*sizeof(int) );
        }
        void add(int pos) {
            while (pos <= n) {
                data[pos]++;
                pos += zrs(pos);
            }
        }
        pair<int,int> search(int k) {
            int lim = 1,ans=0;
            while ( (lim<<1) <= n ) lim <<= 1;

            for (int step = lim; step > 0; step >>= 1) {
                if ( (ans|step) > n ) continue;

                if (data[ans|step] < k) {
                    ans |= step;
                    k -= data[ans];
                }
            }

            return mp(ans+1,k);
        }

    private:
        int n;
        int *data;

        int zrs(int x) {
            return (x^(x-1))&x;
        }
};

struct Trie {
    int sum;
    Trie* wh[10];

    Trie(){
        sum = 0;
        memset(wh,0,sizeof(wh));
    }
};

ifstream fin("nums.in");
ofstream fout("nums.out");

int n,i,op,sz,k;
string s;

aib HowMany;
int aib_data[maxN];
Trie* Head[maxN];

bool FindIt() {
    Trie* act = Head[sz];

    for (int i = 0; i < sz; i++) {
        if (act->wh[ s[i]-'0' ] == NULL) return false;
        act = act->wh[ s[i]-'0' ];
    }

    return true;
}

void addTrie(){
    Trie* act = Head[sz];

    for (int i = 0; i < sz; i++) {
        int to = s[i]-'0';

        if (act->wh[ to ] == NULL) act->wh[to] = new Trie;
        act = act->wh[ to ];

        act->sum++;
    }
}

void Query() {
    Trie* act = Head[sz];

    for (int i = 0; i < sz; i++) {

        int to;
        for (to = 0; to < 10; to++) {
            if (act->wh[to] == NULL) continue;

            if (act->wh[to]->sum >= k) break;
            k -= act->wh[to]->sum;
        }

        fout << to ;
        act = act->wh[to];
    }
}

int main()
{
    fin >> n ;

    HowMany.init(def,aib_data);
    for (i = 1; i <= def; i++) Head[i] = new Trie;

    for (i = 1; i <= n; i++) {
        fin >> op ;

        if ( op == 1 ) {
            fin >> s; sz = s.size();
            if ( FindIt() ) continue;

            HowMany.add(sz);
            addTrie();
        } else {
            fin >> k;
            auto need = HowMany.search(k);

            sz = need.first;
            k = need.second;

            Query();
            fout << '\n';
        }
    }

    return 0;
}
