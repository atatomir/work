/*
    Constantin Galatan
    Complexitate: O(n)
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
using VI = vector<int>;

VI a, b, c; // sirul sirul inaltimilor, sirul sortat, sir auxiliar
int n, V;

int main()
{
    ifstream fin("risc2.in");
    ofstream fout("risc2.out");

	int hmax(0), pmax(-1);
	fin >> V >> n;
	a = VI(n);
	for (int i = 0; i < n; ++i)
	{
		fin >> a[i];
		if ( a[i] > hmax )
			hmax = a[i], pmax = i;
	}

	if ( V == 1 )
	{
	    bool ok = true;
		for (int i = 0; i < n && ok; ++i)
		{
			if ( i && i <= pmax && a[i - 1] > a[i] )
				ok = false;

			if ( i > pmax && a[i - 1] < a[i] )
				ok = false;
		}

		if ( ok && pmax && a[pmax - 1] > a[n - 1])
			ok = false;
		if ( ok )
			fout << pmax + 1 << '\n';
		else
			fout << -1 << '\n';
	}
	else
	{
		b = VI(n); c = VI(hmax + 1);
		for (int i = 0; i < n; i++)
			c[a[i]]++; // c[i] - numarul elem egale cu i (frecventele)

		for (int i = 1; i <= hmax; i++)  //  O(n)
			c[i] += c[i-1];  // c[i] - numarul elem mai mici sau egale cu i

		for (int i = 0; i < n; i++)
			b[c[a[i]] - 1] = a[i];

		int cntAsc(0), cntDesc(0), k(0);
		for (int i(0), j(0); i < n; ++i)    //  partea crescatoare
        {
			if (a[i] == b[j] )
				cntAsc++, j++;

			if ( i == pmax )
                k = cntAsc;
        }

		for (int i(pmax), j(n - 1); i < n; ++i) // partea descrescatoare
			if (a[i] == b[j] )
				cntDesc++, j--;

		fout << n - max(cntAsc, cntDesc + k) << '\n';
	}

	fin.close();
	fout.close();
	return 0;
}
