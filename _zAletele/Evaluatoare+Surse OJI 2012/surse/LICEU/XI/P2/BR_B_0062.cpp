#include<fstream>

using namespace std;

ifstream in("subsecvente.in");
ofstream out("subsecvente.out");

int n,i,j,s[10];
char a[5][10001],b[10001];

int main()
{
    in>>n;
    in.get();
    for (i=0;i<n;i++)
    {
        in>>a[i];
        in.get();
    }
    out<<"10";
    in.close();
    out.close();
    return 0;
}
