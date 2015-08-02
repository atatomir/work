#include <iostream>
#include <fstream>

using namespace std;

int a[5002],v[1002],p;

int esteCool(int r ,int l) {
    int aux,m,gasit=1,cn=0;
    int b[5001];
    for (m=0;m<l;m++) b[m]=a[m+r];
    while (gasit) {
        gasit=0;
        for (m=0;m<l-1-cn;m++) {
            if (b[m]>b[m+1]) {
                aux = b[m]; b[m]=b[m+1];b[m+1]=aux;
                gasit=1;
            }
        }
        cn++;
    }
    for (m=0;m<l-1;m++) {
        if(b[m] != b[m+1]-1) return 0;
    }
    return b[l-1];
}

int main()
{
    int n,i,j,k,cnt=0,lmax=0,catelmax=0;
    ifstream f ("cool.in");
    ofstream g ("cool.out");
    f>>p>>n>>k;
    for (i=0;i<n;i++) {
        f>>a[i];
    }
    if (p == 1) {
        if (esteCool(0,k)) {
            g<<esteCool(0,k);
        }
        else {
            for (i=0;i<k;i++) {
                v[a[i]]++;
            }
            for (i=1;i<=1000;i++) {
                if (v[i]==1) cnt++;
            }
            g<<cnt;
        }
    }
    else {
        for (i=n;i>1;i--) {
            for (j=0;j<=n-i;j++){
                if (esteCool(j,i)) {
                    lmax=i;
                    catelmax++;
                }
            }
            if (lmax!=0) break;

        }
        g<<lmax<<"\n";
        g<<catelmax;
    }
    f.close();
    g.close();

    return 0;
}
