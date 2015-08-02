#include <iostream>
#include <fstream>
using namespace std;
int main()
{ int n,k,s[1000];
long b,t;
ifstream f("clepsidru.in");
ofstream c("clepsidru.out");
f>>n>>b;

//timpul in care boabele de nisip ajung in incinta de jos a clepsidrei
t=b-1+n; c<<t<<"\n";

f.close();
g.close();
return 0;
}
