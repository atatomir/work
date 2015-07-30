#include <iostream>
#include <fstream>
using namespace std;

ifstream in("fractii2.in");
ofstream out("fractii2.out");
int p, k;

void first();
void second();

int main()
{
    in>>p>>k;
    if(p==1) first();
    else second();
    return 0;
}

void first() {
    for(int i=1;i<k;i++) out<<i<<" ";
    out<<k-1<<'\n';
}

void second() {
    long long a, b;
    a = 1;
    b = 1;
    for(int i=3;i<=k;i++) {
        int c = a+b;
        a = b;
        b = c;
    }
    out<<a%100003<<"\n";
}
