#include <fstream>

#define def 1001;

using namespace std;

long n,maxim,i,j,todo[100005],ok[100005],a[1005],tdc,rez;

ifstream fin("jocul.in");
ofstream fout("jocul.out");

inline int check(long x){
    if (x < 0) return 0;
    if (ok[x] < i)
        return 1;
    else
        return 0;
}

int main()
{

    fin >> n;
    for(i=1;i<=n;i++) {
        fin >> a[i];
        maxim += a[i];
    }

    rez = maxim;
    maxim /= 2;

    tdc = maxim;
    for(i=1;i<=tdc;i++) {
        todo[i] = i;
        ok[i] = def;
    }

    for(i=1;i<=n;i++){
        for(j=tdc;j;j--){
            if (check(todo[j]-a[i])) {
                ok[todo[j]] = i;
                todo[j] = todo[tdc--];
            }
        }

        if(ok[maxim] != 1001) break;
    }

    while (ok[maxim] == 1001) maxim--;
    rez = rez - maxim;

    fout << maxim << ' ' << rez << '\n';

    //for(i=1;i<=maxim;i++) fout << i << ' ' << ok[i] << '\n';

    fin.close();
    fout.close();
    return 0;
}
