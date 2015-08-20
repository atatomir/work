#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

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
        int search(int k) {
            int lim = 1,ans=0;
            while ( (lim<<1) <= n ) lim <<= 1;

            for (int step = lim; step > 0; step >>= 1) {
                if ( (ans|step) > n ) continue;

                if (data[ans|step] < k) {
                    ans |= step;
                    k -= data[ans];
                }
            }

            return ans+1;
        }

    private:
        int n;
        int *data;

        int zrs(int x) {
            return (x^(x-1))&x;
        }
};

ifstream fin("nums.in");
ofstream fout("nums.out");

int n,i,cnt,op,x;
string Nr[maxN];
vector< int > Events;
int ind[maxN],pos[maxN],last;

aib Active;
int aib_data[maxN];
unordered_map< string,bool > M;

bool cmp(const int& a,const int& b) {
    if( Nr[a].size() == Nr[b].size() )
      return Nr[a] < Nr[b];

    return Nr[a].size() < Nr[b].size();
}

int main()
{
    fin >> n;
    for (i = 1; i <= n; i++) {
        fin >> op;
        if (op == 1) {
            fin >> Nr[++cnt];

            Events.pb( -1 );
        } else {
            fin >> x;
            Events.pb( x );
        }
    }

    for (i = 1; i <= cnt; i++) ind[i] = i;
    sort( ind+1,ind+cnt+1,cmp );
    for (i = 1; i <= cnt; i++) pos[ ind[i] ] = i;

    Active.init(cnt,aib_data);
    M.clear();

    for (auto actEvent:Events) {
        if (actEvent == -1) {
            last++;

            if ( M[ Nr[last] ] ) continue;
            M[ Nr[last] ] = true;
            Active.add( pos[last] );
        } else {
            int wh = Active.search(actEvent);
            fout << Nr[ ind[wh] ] << '\n';
        }
    }


    return 0;
}
