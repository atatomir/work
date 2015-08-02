#include <fstream>
using namespace std;

void ord(int test[5001], int k) {
    int i,aux;
    for(int j=1;j<=k;j++)
    for(i=1;i<k;i++)
    if(test[i]>test[i+1]) {
    aux=test[i];
    test[i]=test[i+1];
    test[i+1]=aux;
    }
}

int cool(int test[5001], int k) {
int i;
bool ok=false;
    for(i=1;i<k&&ok==false;i++)
    if(test[i]+1!=test[i+1])
    ok=true;

    return ok;
}

int main()
{
    ifstream in("cool.in");
    ofstream out("cool.out");
    int p,n,k,i;
    in>>p>>n>>k;
    if(p==1) {
        int test[k+1];
        //Punctul 1
    //Citire
    for(i=1;i<=k;i++) {
        in>>test[i];
    }
        //Ordonare test
    ord(test, k);

    //Verificare cool
    bool ok;
    ok=cool(test, k);
    if(!ok)
    out<<test[k]<<endl;
    else {
        int j,nrv=0;
        for(j=1;j<=k;j++) {
    for(i=1;i<=k;i++)
    if(test[i]==test[j]&&i!=j)
    nrv++;
        }
        out<<k-nrv<<endl;
    }
    }
    in.close();
    out.close();
    return 0;
}
