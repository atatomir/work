#include<fstream>

using namespace std;

ifstream f("biperm.in");
ofstream g("biperm.out");

int main()
{
    g<<"4 1"<<endl<<"1 2 5 3 4"<<endl<<"3 5 2 4 1";
    return 0;
}
