#include <fstream>
#include <bitset>

using namespace std;

long n,i,j,mid;
char c;
bitset<500005> a,sol;
long nr,rez;

inline int check(long l) {
    if (l > n) return 1;

    sol.reset();
    long bitelim = 1L << (l-1) , val = 0,i;
    for(i=1;i<=l;i++) {
        val <<= 1;
        if (a[i] == 1) val ^= 1L;
    }
    sol[val] = 1;
    for(i=l+1;i<=n;i++) {
        if (a[i-l]) val ^= bitelim;
        val <<= 1;
        if (a[i]) val ^= 1L;

        sol[val] = 1;
    }

    bitelim = (bitelim << 1) - 1;  // ATENTIE la paranteze .
    for(i=0;i<=bitelim;i++){
        if(!sol[i]){
            rez = i;
            return 1;
        }
    }
    return 0;
}

int main()
{
    ifstream fin("string.in");
    ofstream fout("string.out");

    fin >> n;
    for(i=1;i<=n;i++) {
        fin >> c;
        if(c == 'b') a[i] = 1;
    }

    i = 1; j = 20;
    do {
        mid = (i+j)/2;
        if (check(mid))
            j = mid-1;
        else
            i = mid+1;
    }   while (i <= j);

    fout << i << '\n';
    i = 1L << i;
    do {
        i >>= 1;
        if (rez & i) fout << 'b'; else fout << 'a';
    }   while (i > 1);

    fin.close();
    fout.close();
    return 0;
}
