#include <iostream>
#include <fstream>

using namespace std;

#define maxN 13319

int main()
{
    ifstream f1("rotatii.out");
    ifstream f2("rotatii.ok");

    for(long i=1;i<=maxN;i++){
        long a,b;
        f1 >> a; f2 >> b;
        if(a==b) continue;
        cerr << i << ' ' << a << ' ' << b << '\n';
    }

    return 0;
}
