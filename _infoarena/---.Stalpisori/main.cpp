#include <fstream>

using namespace std;

long n,k,i,a[1000005],maxim=0,bg,en,maxl,rez;

long getMax(long a,long b){
    if(a < b) {
        rez=b;
        return b;
    }
    else{
        rez = a;
        return a;
    }
}

int main()
{
    ifstream fin("stalpisori.in");
    ofstream fout("stalpisori.out");

    fin >> n >> k;
    for(i=1;i<=n;i++) fin >> a[i];
    a[n+1] = a[n];

    bg =1 ; en = k;
    for(i=1;i<=n;i++){
        maxl = getMax(a[i]-a[bg],a[en]-a[i]);
        while (maxl > getMax(a[i]-a[bg+1],a[en+1]-a[i])){
            bg++; en++;
            maxl = rez;

            if(en > n) en = n;
        }
        //fout << i << ' ' << maxl << '\n';
        maxim = getMax(maxim,maxl);
    }

    fout << maxim;

    fin.close();
    fout.close();
    return 0;
}
