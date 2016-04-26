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

#define maxN 1024

int n, S, i, j;
int v[maxN];

int mid, need;
vector<int> first_two, last_two;
int ans;

vector<int> aux;



void get_count() {
    int l, r;

    l = 0; r = last_two.size() - 1;

    while (l < first_two.size() && r >= 0) {
        while (r >= 0) {
            if (first_two[l] + last_two[r] <= need) break;
            r--;
        }

        if (r < 0) {l++; continue;}
        if (first_two[l] + last_two[r] != need) {l++; continue;}

        int new_l = l;
        int new_r = r;

        while (first_two[new_l] == first_two[l])
            if(++new_l == first_two.size()) break;

        while (last_two[new_r] == last_two[r])
            if (--new_r == -1) break;

        ans += (new_l - l) * (r - new_r);
        l = new_l; r = new_r;
    }
}

void add_value(vector<int>& ret, int pos) {
    int i, s1, s2, ins;

    aux.resize(pos - 1);
    for (i = 1; i < pos; i++) aux[i - 1] = v[i] + v[pos];

    s1 = ret.size(); s2 = aux.size();
    ret.resize(s1 + s2);

    ins = s1 + s2 - 1; s1--; s2--;
    while (s1 >= 0 && s2 >= 0) {
        if (ret[s1] > aux[s2])
            ret[ins--] = ret[s1--];
        else
            ret[ins--] = aux[s2--];
    }

    //while (s1 >= 0) ret[ins--] = ret[s1--]; //! nothing to do..
    while (s2 >= 0) ret[ins--] = aux[s2--];

    aux.clear();
}

void rm_value(vector<int>& ret, int pos) {
    int i, j, ins;

    aux.resize(n - pos);
    for (i = pos + 1; i <= n; i++) aux[i - pos - 1] = v[pos] + v[i];

    ins = 0; j = 0;
    for (int e : aux) {
        while (ret[j] < e) ret[ins++] = ret[j++];
        j++;
    }

    while (j < ret.size()) ret[ins++] = ret[j++];
    ret.resize(ins);

    aux.clear();
}



int main()
{
    freopen("take5.in","r",stdin);
    freopen("take5.out","w",stdout);

    scanf("%d%d", &n, &S);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);

    sort(v + 1, v + n + 1);
    first_two.reserve(n * n);
    last_two.reserve(n * n);

    first_two.pb(v[1] + v[2]);
    for (i = 4; i <= n; i++)
        for (j = i + 1; j <= n; j++)
            last_two.pb(v[i] + v[j]);
    sort(last_two.begin(), last_two.end());

    for (mid = 3; mid + 2 <= n; mid++) {
        need = S - v[mid];

        get_count();
        add_value(first_two, mid);
        rm_value(last_two, mid + 1);
    }

    printf("%d", ans);


    return 0;
}
