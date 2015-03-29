#include <fstream>
#include <vector>

using namespace std;

struct stackElem {
    long pos,v;
} elem;

long n,m,i,g,h,a[400005],stn,pos,j,nrelem,ap,ak,p,k;
vector<stackElem> st[7];
long sol[400005][6];

int main()
{
    ifstream f("ismquery.in");
    ofstream fo("ismquery.out");

    f >> n >> m;
    for(i=1;i<=n;i++) f >> a[i];
    f >> g >> h;

    for(i=1;i<=n;i++) {
        for(stn = 5;stn > 0;stn--) {
            pos = st[stn].size()-1; nrelem = pos;

            if (pos >= 0)
            while(st[stn][pos].v < a[i]) {
                pos--;
                if (pos < 0) break;
            }
            pos ++;

            for(j=pos;j<=nrelem;j++) {
                sol[st[stn][j].pos][stn] = i;
                st[stn+1].push_back(st[stn][j]);
            }
            for(j=pos;j<=nrelem;j++) {
                st[stn].pop_back();
            }

        }
        elem.pos= i;
        elem.v = a[i];
        st[1].push_back(elem);
    }

    ap = 1; ak = 1;
    for(i=1;i<=m;i++) {
        p = 1 + (i+ap*g)%n;
        k = 1 + (i+ak*h)%5;
        fo << sol[p][k] << '\n';
        ap = p; ak = k;
    }

    f.close();
    fo.close();
    return 0;
}
