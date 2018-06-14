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

const int maxN = 5012;

int k, i, j;
string s, aux;
vector<string> data;

int main()
{
    freopen("test.in","r",stdin);

    cin >> s >> k;
    for (i = 0; i < s.size(); i++) {
        aux.clear();
        for (j = 0; j < k && i + j < s.size(); j++) {
            aux.pb(s[i + j]);
            data.pb(aux);
        }

        if (data.size() > 100) {
            sort(data.begin(), data.end());
            data.resize(unique(data.begin(), data.end()) - data.begin());
            if (data.size() > k) data.resize(k);
        }
    }

    sort(data.begin(), data.end());
    data.resize(unique(data.begin(), data.end()) - data.begin());

    cout << data[k - 1];


    return 0;
}
