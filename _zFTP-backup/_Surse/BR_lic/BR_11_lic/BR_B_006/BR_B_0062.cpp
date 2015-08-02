#include <fstream>
using namespace std;
int p,n,i;
int main()
{
    ifstream f("fractii2.in");
    ofstream g("fractii2.out");
    f>>p>>n;
    if(p==1){
        if(n==1) g<<"0";
        else
            for(i=1;i<n;i++)
                g<<i<<' ';
        g<<i-1<<'\n';}
    f.close();
    g.close();
    return 0;
}
