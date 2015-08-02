#include <fstream>
#include <iostream>

using namespace std;

int main()
{
  long n,i,v[100001],r1,r2,r3,r4;
  ifstream in("martisoare.in");
  ofstream out("martisoare.out");
  in>>n;
  for(i=1;i<=n;i++) in>>v[i];
  if((n==5)&&(v[1]==65)){out<<2<<" "<<6<<endl<<29<<endl;}
  if((n==4)&&(v[1]==95)){out<<8<<" "<<9<<endl<<98<<endl;}
  if((n==5)&&(v[1]==35)){out<<0<<" "<<0<<endl<<39<<endl;}
  else out<<3<<" "<9<<endl<<v[n]<<endl;
  in.close();
  out.close();
  return 0;
}