#include <fstream>
using namespace std;

ifstream f("betasah.in");
ofstream g("betasah.out");

int n, d, k, i, ii, nr, m, j, v[1001], v2[1001];

int main()
{
    f >> n >> d >> k;
    for(i=1; i<=d; i++){
        f >> ii >> j;
        v[ii]=2;}
    for(i=1; i<=k; i++){
        f >> ii >> j;
        if(!v2[ii]) v2[ii]=ii;
        v2[ii]--;
        if(!v2[ii]) v[ii]=1;
    }
    for(i=1; i<=n; i++){
        if(!v2[i] && v[i]!=1) v2[i]=i;
        if(v2[i]>m)
            m=v2[i];
            nr+=v2[i];
            if(v[i]==2 || v[i-1]==2 || v[i+1]==2 || v[i-i]==2 || v[i+i]==2 || v[i+i+1] || v[i-i-1]) nr--; }

    g << m << '\n' << nr;
    g << '\n';
    return 0;
}
