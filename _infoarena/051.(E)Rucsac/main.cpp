#include <fstream>

using namespace std;

struct {
    long p,g;
} a[5005];

long n,g,i,pr[10005],maxim=0,j;

int main()
{
    ifstream fin("rucsac.in");
    ofstream fout("rucsac.out");

    fin >> n >> g;
    for(i=1;i<=n;i++) fin >> a[i].g >> a[i].p;

    for(i=1;i<=n;i++){
        for(j=g;j;j--) {
            if(j-a[i].g >= 0){
                if (pr[j] < pr[j-a[i].g] + a[i].p)
                    pr[j] = pr[j-a[i].g] + a[i].p;
            }
        }
    }
    for(i=1;i<=g;i++)
        if (maxim < pr[i]) maxim = pr[i];

    fout << maxim;

    fin.close();
    fout.close();
    return 0;
}
