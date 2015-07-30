/*
    prof. Constantin Galatan
    O(Q * (n^2) * log n)
*/
#include <fstream>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;
using VI = vector<int>;

const int MaxN = 155;
bitset<MaxN> b[MaxN];
vector<VI> a;
int n, m;

int CountRobots(int L);

ifstream fin("roboti2.in");
ofstream fout("roboti2.out");

int main()
{
	int x, y, p, T, L;

	fin >> p >> n >> m >> T;

	for (int i = 1; i <= T; ++i)
	{
		fin >> x >> y;
		b[x][y] = 1;
	}

	if ( p == 1 )
    {
         fin >> L;
         fout << CountRobots(L) << '\n';
    }
    else
    {
        int Q, k, lo, hi, Lmin;

        for (fin >> Q; Q--; fout << Lmin << '\n')
        {
            fin >> k;
            lo = 1, hi = n / k + 1;
            while (lo <= hi)
            {
                L = (lo + hi) / 2;

                if (CountRobots(L) <= k)
                {
                    Lmin = L;
                    hi = L - 1;
                }
                else
                    lo = L + 1;
            }
        }
    }

    fin.close();
    fout.close();
}

int CountRobots(int L)
{
	int cnt = 0;
	a = vector<VI>(n + 1, VI(m + 2));

    for (int i = 1; i <= n; ++i)
		for (int j = m; j >= 1; --j)
		{
			if ( b[i][j] )
			{
				if ( i > L && j <= m - L )
					a[i][j] = 1 + a[i - L][j + L];
				else
					a[i][j] = 1;
			}
			else
				a[i][j] = max(a[i][j + 1], a[i - 1][j]);

			cnt = max(cnt, a[i][j]);
		}

	return cnt;
}

