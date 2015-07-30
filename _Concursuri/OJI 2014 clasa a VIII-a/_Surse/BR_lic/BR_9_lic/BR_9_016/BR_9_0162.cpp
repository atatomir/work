#include <fstream>

using namespace std;

int main()
{
    ifstream in("pseudobil.in");
    ofstream out("pseudobil.out");
    int p,n,k,d;
    in>>p;
    if(p==1) {
    in>>n>>k>>d;
    if(d==2)
    out<<"1";
    if(d==4)
    out<<"5";
    if(d>4) {
    out<<d-1+4+(4*((d/2)-2));
    }
    }
    in.close();
    out.close();
    return 0;
}
