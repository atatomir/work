#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back

int dim, i, state;
string s;

int pas;
vector<int> states;

void comp() {
    int i, j, lim;

    states.pb(0);
    states.pb(1);

    for (i = 2; i <= dim; i++) {
        lim = states.size();
        for (j = lim - 1; j >= 0; j--)
            states.pb(states[j] + (1 << (i - 1)));
    }
}

void genTest(int state) {
    //! generate test
    ofstream fin("bulbs.in");

    for (int bit = 1 << (dim - 1); bit; bit >>= 1)
        if (state & bit) {
            fin << '1';
            cout << '1';
        } else {
            fin << '0';
            cout << '0';
        }

    cout << "   -   ";
    fin.close();
}

int main()
{
    srand(time(NULL));

    //! read t, n, ....
    cin >> dim;

    comp();

    for (state = 0; state < (1 << dim); state++) {
        genTest(states[state]);

        system("./bulbs");
        ifstream fin("bulbs.out");
        s.clear();
        fin >> s;
        cout << s << '\n';
    }

    return 0;
}
