#include <fstream>

using namespace std;

ifstream fin("coins.in");
ofstream fout("coins.out");

const long cdef = 1 << 22;

int confs[cdef],all,last;
long t,ti,n,i,x,nconf,p,sum=0,cost,modif;

int main()
{
    for(x=0;x<cdef;x++){
        all = 1; last = -1; modif = 1;
        for(i=0;i<=21;i++){
            if((x >> i)&1) {
                if(last >= 0){
                    nconf = x;
                    nconf ^= 1 << i;
                    nconf ^= 1 << last;

                    modif = 0;
                    all&= confs[nconf];
                    if(all == 0) break;
                }
            } else {
                last = i;
            }
        }
        all ^= 1; all |= modif;
        confs[x] = all;
    }

    fin >> t;
    for(ti=1;ti<=t;ti++){
        x = 0; cost = 0;
        for(i=0;i<22;i++){
            fin >> p;
            if(p){
                x ^= 1 << i;
                cost++;
            }
        }
        if(confs[x]) sum += cost;
    }

    fout << sum;

    fin.close();
    fout.close();
    return 0;
}
