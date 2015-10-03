#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    ofstream fout("input.in");

    srand(time(NULL));

    fout << 100000 << '\n';
    for(int i = 1; i <= 100000; i++) {
        fout << (rand() % 9) + 1 << ' ';
    }

    return 0;
}
