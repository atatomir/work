/*
    prof. Constantin Galatan
    O(Q * T * log n)
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <deque>

using namespace std;
using PII = pair<int, int>;

#define I q1.front().first
#define J q1.front().second

deque<PII> q, q1, q2, q3;
int n, m;

int CountRobots(int L);

int main()
{
    ifstream fin("roboti2.in");
    ofstream fout("roboti2.out");

	int x, y, p, T, L;

	fin >> p >> n >> m >> T;
	for (int i = 1; i <= T; ++i)
	{
		fin >> x >> y;
		q.push_back({x, y});
	}

    sort(q.begin(), q.end());

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

                if ( CountRobots(L) <= k)
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
    int lastJ, lastI, i1, i2, j1, cnt = 0;
    bool first(true);
    for (q1 = q; !q1.empty(); q1.swap(q2))
    {
		cnt++;
        lastJ = J, lastI = I, first = true;

        for ( ; !q1.empty();  )
        {
            // cobor cat pot pe verticala
            if (!q1.empty() && J <= lastJ && J > lastJ - L)
            {
            	q1.pop_front();
            	continue;
            }

			// daca e un nou robot si vin din stanga, atunci el ia  tot ce robotul pe orizontala
            if (first && !q1.empty() && J <= lastJ && I <= lastI + L - 1 )
            {
                q1.pop_front();
                continue;
            }

            // se pierde - va fi luat de urmatorul robot
            if ( !q1.empty() && J <= lastJ - L )
            {
                q2.push_back(q1.front());
                q1.pop_front();
                continue;
            }

			if ( J > lastJ )
			{
				i1 = I, i2 = min(n, i1 + L - 1), j1 = max(J, L);

                while ( !q1.empty() && I >= i1 && I <= i2 )
                {

                    // dreptunghiul pana sub copacul pe care a fost plasat robotul anterior
                    if ( !q1.empty() && J <= j1 && J >= lastJ - L + 1 )
                    {
                        q1.pop_front();
                        continue;
                    }

                    // suntem inca in intervalul de culisare (penultimul robot) spre stanga
                    if (first && !q1.empty() && J <= lastJ && I <= lastI + L - 1 )
                    {
                        q1.pop_front();
                        continue;
                    }

                    // ramane neacoperit in stanga robotului
                    if ( !q1.empty() && J <= lastJ - L )
                    {
                        q2.push_back(q1.front());
                        q1.pop_front();
                        continue;
                    }

                    // ce-i in dreapta și jos fata de copacull de la coloana J pun in alt sir
                    if ( !q1.empty() && J > j1 )
                    {
                        q3.push_back(q1.front());
                        q1.pop_front();
                        continue;
                    }
                }

                for (; !q3.empty(); q3.pop_back())
                    q1.push_front(q3.back());

                lastJ = j1;
				lastI = i1;
                first = false;
            }
        }
    }

    return cnt;
}



