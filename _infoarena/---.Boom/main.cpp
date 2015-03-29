#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("boom.in");
ofstream fout("boom.out");

struct sarja{
    long mask,p;
} s[70];

struct queueElem{
    long conf,cost;
    queueElem operator()(long lconf,long lcost){
        conf = lconf; cost = lcost;
        return *this;
    }
} elem,local;

struct {
    long source;
    int sarja;
} recon[1 << 23];

long n,m,i,mask,t,x;
long pmin[1 << 23];
const long inf = 1 << 30;
int sol[1 << 23];
queue<queueElem> q;


int main()
{
    fin >> n >> m;

    mask = (1 << n) -1;
    for(i=1;i<=m;i++) {
        fin >> s[i].p;
        fin >> t;
        s[i].mask = mask;
        for(;t;t--){
            fin >> x; x--;
            s[i].mask ^= 1 << x;
        }
    }
    for(i=0;i<=mask;i++) pmin[i] = inf;

    q.push(elem(mask,0));
    long nconf,ncost,antconf;
    while(!q.empty()){
        elem = q.front(); q.pop();

        if(elem.cost > pmin[elem.conf]) continue;
        if(elem.cost > pmin[0]) continue;

        for(i=1;i<=m;i++) {
            nconf = elem.conf & s[i].mask;
            nconf = (nconf << 1)|(nconf >> 1);
            nconf &= mask;
            ncost = elem.cost + s[i].p;

            if(ncost < pmin[nconf]){
                pmin[nconf] = ncost;
                recon[nconf].source = elem.conf;
                recon[nconf].sarja = i;
                if(nconf){
                    q.push(local(nconf,ncost));
                }
            }

        }
    }

    i=0;
    while(recon[i].source != mask){
        sol[++sol[0]] = recon[i].sarja;
        i = recon[i].source;
    }
    sol[++sol[0]] = recon[i].sarja;

    fout << pmin[0] << '\n' << sol[0] << '\n';
    for(i=sol[0];i>=1;i--){
        fout << sol[i] << '\n';
    }

    return 0;
}
