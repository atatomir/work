#include<iostream>
#include<fstream>
using namespace std;
int main()
{int n,s,i,j,c,nr,k;
ifstream f("galbeni.in");
ofstream g("galbeni.out");
f>>n;
f>>s;
f>>k;
for(i=1;i<=s;i++)
    {cin>>s[i];
    do
    {c=s%10;
    s=s/10;
    s=0;
    s[i+1]={[s[i]*c]*8}/9;
    nr++;
    k=s[i]%10;}
    while(s!=0&&c!=0)}
g<<"al n-le termen a luat"<<s[i+n]<<"galbeni";
f.close();
g.close();
return 0;
}
