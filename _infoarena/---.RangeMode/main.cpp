#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <cmath>

#define SQRT_MAX 405
#define MAX 100005

using namespace std;

ifstream fin("rangemode.in");
ofstream fout("rangemode.out");

struct Query {
    long bg,en,ind;
    Query operator()(long lstart,long lstop,long lind){
        bg = lstart; en =lstop; ind = lind;
        return *this;
    }
}QElem;

long n,m,i,j,a[MAX],dim;
long ans[MAX],bg[MAX],en[MAX],own[MAX],ap[MAX],auxap[MAX];
long lbg,len,bulkmax,bulk,actq,maxim,maxind,auxmaxim,auxmaxind;
vector<Query> q[SQRT_MAX];

bool cmp(const Query& a,const Query& b){
    return (a.en < b.en);
}

void preProcess() {
    dim = (long)sqrt((double)n);
    for(long i=1;i<=n;i++){
        own[i] = (i+dim-1)/dim;
        if(!bg[own[i]]) bg[own[i]] = i;
        en[own[i]] = i;
    }
    bulkmax = own[n];
}

long brute(long bg,long en){
    memset(ap,0,sizeof(ap));
    long maxim=0,maxind=0;
    for(long i=bg;i<=en;i++){
        ap[a[i]]++;
        if((ap[a[i]] > maxim)||((ap[a[i]] == maxim)&&(a[i] < maxind))){
            maxim = ap[a[i]];
            maxind = a[i];
        }
    }
    return maxind;
}

void Reset(long start,long stop) {
    for(long i=start;i<=stop;i++){
        ap[a[i]]--;
    }
}

int main()
{
    fin >> n >> m;
    for(i=1;i<=n;i++) fin >> a[i];

    preProcess();
    for(i=1;i<=m;i++){
        fin >> lbg >> len;
        if(own[lbg]==own[len])
            ans[i] = brute(lbg,len);
        else {
            q[own[lbg]+1].push_back(QElem(lbg,len,i));
        }
    }

    for(bulk=2;bulk<=bulkmax;bulk++){
        memset(ap,0,sizeof(ap));
        j = bg[bulk];
        maxim = 0; maxind = 0;
        sort(q[bulk].begin(),q[bulk].end(),cmp);

        for(actq=0;actq<q[bulk].size();actq++){
            for(;j<=q[bulk][actq].en;j++){
                ap[a[j]]++;
                if((ap[a[j]] > maxim)||((ap[a[j]] == maxim)&&(a[j] < maxind))){
                    maxim = ap[a[j]];
                    maxind = a[j];
                }
            }

            auxmaxim = maxim; auxmaxind =maxind;

            for(i=q[bulk][actq].bg;i<bg[bulk];i++){
                ap[a[i]]++;
                if((ap[a[i]] > auxmaxim)||((ap[a[i]] == auxmaxim)&&(a[i] < auxmaxind))){
                    auxmaxim = ap[a[i]];
                    auxmaxind = a[i];
                }
            }

            ans[q[bulk][actq].ind] = auxmaxind;
            Reset(q[bulk][actq].bg,bg[bulk]-1);
        }
    }

    for(i=1;i<=m;i++) fout << ans[i] << '\n';

    fin.close();
    fout.close();
    return 0;
}
