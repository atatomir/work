#include <fstream>
#include <vector>

#define mod 30007

using namespace std;

long n,i,op,x;
vector<long> a[mod];

inline int verif(long x) {
    long dir = x % mod,nr=a[dir].size();
    for(long i=0;i<nr;i++){
        if (a[dir][i] == x) {
            return 1;
        }
    }
    return 0;
}


inline void add(long x) {
    if (verif(x)) return;

    long dir = x % mod;
    a[dir].push_back(x);
}

inline void del(long x) {
    if (!verif(x)) return;

    long dir = x % mod,t,nr=a[dir].size();
    for(long i=0;i<nr;i++) {
        if (a[dir][i] == x) {
            t = a[dir][i]; a[dir][i] = a[dir][nr-1] ; a[dir][nr-1] = t;
            a[dir].pop_back();
            return;
        }
    }
}

int main()
{
    ifstream f("hashuri.in");
    ofstream fo("hashuri.out");

    f >> n;
    for(i=1;i<=n;i++) {
        f >> op >> x;
        switch (op) {
            case 1: add(x);
                    break;
            case 2: del(x);
                    break;
            case 3: fo << verif(x) << "\n";
                    break;
        }

    }

    f.close();
    fo.close();
    return 0;
}
