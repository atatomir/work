#include <iostream>
#include <vector>
#include <fstream>

#define mod 705007

using namespace std;


long n,i,v;
char(c);
long long rez = 0,act;
vector< pair<long long,long> > a[mod];

inline long convert(char c) {
    if (c > 'Z') {
        return (long)(c-'a'+26);
    } else {
        return (long)(c-'A');
    }
}

inline long hadd(long long id,long val) {
    long long dir = id % mod,nr = a[dir].size();
    for(long i=0;i<nr;i++){
        if (a[dir][i].first == id) {
            a[dir][i].second += val;
            return a[dir][i].second;
        }
    }
    if (val > 0 ) a[dir].push_back(make_pair(id,val));
    return val;
}

int main()
{
    while (!cin.eof()) {
        cin >> n;
        if(cin.eof()) return 0;

        act = 0; rez = 0;

        for(i=0;i<mod;i++) a[i].clear();
        hadd(0,1);

        for(i=1;i<=n;i++) {
            cin >> c;
            v = convert(c);

            act ^= 1LL << v;
            rez += hadd(act,0) ;
            for(long j=0;j<52;j++)
                rez += hadd(act ^ (1LL << j),0);
            hadd(act,1);
        }

        cout << rez << '\n';

    }


    return 0;
}
