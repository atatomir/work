#include <iostream>
#include <stack>
#include <fstream>
#include <cassert>

#define maxn 100010
#define inf 100000000010LL

using namespace std;

ifstream fin("atlas.in");
ofstream fout("atlas.out");

stack<pair<int,int> > st;
int a[maxn],n,q,t;
long long need[2*maxn],which[2*maxn],width[2*maxn],height[2*maxn];
long long current;

long long cmmdc (long long a, long long b)
{
    if (b == 0) return a;
    return cmmdc(b,a%b);
}

int main()
{
    int test;

    fin >> test;

    for (;test; --test)
    {
        while (!st.empty())
            st.pop();
        t = 0;

        fin >> n;
        assert (1 <= n && n <= 100000);

        for (int i = 1; i <= n; ++i)
        {
            fin >> a[i];
            assert(0 <= a[i] && a[i] <= 100000);
        }

        a[0] = inf;
        a[n+1] = inf;

        need[0] = 0;
        which[0] = 0;
        long long current = 0;
        st.push(make_pair(a[0],0));

        for (int i = 1; i <= n; ++i)
        {
            ++t;
            need[t] = current;
            which[t] = i;
            width[t] = i - st.top().second;
            height[t] = a[i];

            int last = a[i];
            st.push(make_pair(a[i],i));

            while (a[i+1] > st.top().first)
            {
                current += (i - st.top().second) * (st.top().first - last);

                ++t;
                need[t] = current;
                which[t] = i;
                height[t] = st.top().first;

                last = st.top().first;
                st.pop();

                width[t] = i - st.top().second;
            }

            current += (i - st.top().second)*(max(0,a[i+1] - last));
        }

        fin >> q;
        assert(1 <= q && q <= 100000);

        for (int i = 1; i <= q; ++i)
        {
            long long quantity;
            fin >> quantity;
            assert(1 <= quantity && quantity <= 10000000000LL);

            int lo = 0, hi = t+1;

            while (hi - lo > 1)
            {
                int mid = (lo + hi)/2;

                if (quantity > need[mid])
                    lo = mid;
                else hi = mid;
            }

            long long nr = height[lo]*width[lo] + quantity - need[lo];
            long long num = width[lo];
            long long c = cmmdc(nr,num);

            fout << which[lo] << " " << nr/c << "/" << num/c << "\n";
        }
    }
}
