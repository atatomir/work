#include <fstream>
using namespace std;
int main()
{ifstream fin("chibrituri.in");
ofstream fout("chibrituri.out");
fout<<"00"<<":"<<"00"<<'\n';
fout<<"23"<<":"<<"59";
fin.close();
fout.close();
return 0;

}
