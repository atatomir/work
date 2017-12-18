#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long


struct gauss {
    vector< vector<double> > data;
    int ec, rez;
    const double eps = 1e-11;
    vector<double> solutions;

    bool equal(double a, double b) {
        a -= b;
        if (a < -eps || eps < a) return false;
        return true;
    }

    void init(int _ec, int _var) {
        ec = _ec; rez = _var + 1;
        data = vector< vector<double> >(ec + 3, vector<double>(rez + 3, 0));
    }

    void rm_gauss() {
        int i, j, k, l;

        i = 1; j = 1;
        while (i <= ec && j < rez) {
            int found = 0;
            for (k = i; k <= ec; k++)
                if (!equal(data[k][j], 0.00))
                    {found = k; break;}

            if (!found) {
                j++;
                continue;
            }

            swap(data[i], data[found]);
            for (k = i + 1; k <= ec; k++) {
                if (equal(data[k][j], 0.00)) continue;

                double delta = data[k][j] / data[i][j];
                for (l = j; l <= rez; l++) data[k][l] -= data[i][l] * delta;
            }

            i++; j++;
        }
    }

    bool solve() {
        int i, j, k;

        rm_gauss();
        solutions = vector<double>(rez + 3, 0.00);

        for (i = ec; i > 0; i--) {
            for (j = 1; j < rez && equal(data[i][j], 0.00); j++);
            if (j == rez) {
                if (!equal(data[i][rez], 0.00)) return false;
                continue;
            }

            int pos = j;
            solutions[pos] = data[i][rez];

            for (j++; j < rez; j++) {
                if (equal(data[i][j], 0.00)) continue;
                solutions[pos] -= data[i][j] * solutions[j];
            }

            solutions[pos] /= data[i][pos];
        }

        return true;
    }
};


int main()
{
    freopen("*.in","r",stdin);
    freopen("*.out","w",stdout);

    //gauss work;
    //work.init(count_of_ecuation, count_of_variable);
    //work.solve() solves the sistem and returns false if it is invalid. solutions can be found in work.solutions[]
    //if you need to simplify the system just execute work.rm_gauss();

    return 0;
}
