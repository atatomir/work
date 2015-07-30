#include <fstream>

using namespace std;

int main()
{ifstream f("cool.in");
ofstream g("cool.out");
int n,k,A[50],i,p,T[50],j,max,l=0;
f>>p;
f>>n>>k;
for(i=1;i<=n;i++)
{f>>A[i];if(A[i]<A[i+1] / A[i]>A[i-1]){T[j++]=A[i];g<<T[j]<<'';max++;}
for(i=1;i<=n;i++)g<<A[i];
max=k;
g<<"Lungimea maxima a unei secvente cool este"<< max<<'/n/';
if(max==j) l++;
g<<"Avem "<< l << "secvente cool cu lungime maxima";
return 0;}}
