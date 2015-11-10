#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

struct comp2 {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)const  {
        return a.first > b.first;
    }
};
struct comp3 {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)const  {
        return a.second > b.second;
    }
};
struct comp4 {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)const  {
        return a.second < b.second;
    }
};

int n, i, k, auxX, auxY, auxXX, auxYY;
long long ans = 1000000000000002015;
multiset< pair<int, int> > _left;
multiset< pair<int, int> , comp2> _right;
multiset< pair<int, int> , comp3> _up;
multiset< pair<int, int> , comp4> _down;

int used[7];
vector< pair<int, int> > rez[7];

void rmVal(pair<int, int> p) {
    auto it = _left.find(p);
    _left.erase(it);

    /**/ it = _right.find(p);
    _right.erase(it);

    /**/ it = _up.find(p);
    _up.erase(it);

    /**/ it = _down.find(p);
    _down.erase(it);
}

void addVal(pair<int, int> &p) {
    _left.insert(p);
    _right.insert(p);
    _up.insert(p);
    _down.insert(p);
}

void back(int pas, int how) {
    if (_down.size() != n - k + how) while(1) {}

    if (pas == 5) {
        long long xx1 = _left.begin()->first ;
        long long xx2 = _right.begin()->first ;

        long long yy1 = _down.begin()->second;
        long long yy2 = _up.begin()->second;

        xx2 -= xx1;
        yy2 -= yy1;

        xx2 = (xx2 + 1LL) / 2LL;
        yy2 = (yy2 + 1LL) / 2LL;


        long long area = 1LL * xx2 * 1LL * yy2;
        ans = min(ans, area);

        //cerr << _down.size() << ' ' << n - k + how << '\n';

        return;
    }

    used[pas] = 0;
    back(pas + 1, how);
    rez[pas].clear();

    for (int i = 1; i <= how; i++) {
        used[pas] = i;

        pair<int, int> who;

        if (pas == 1) who = *_left.begin();
        else
        if (pas == 2) who = *_right.begin();
        else
        if (pas == 3) who = *_up.begin();
        else
        if (pas == 4) who = *_down.begin();

        rmVal(who);
        rez[pas].pb(who);

        back(pas + 1, how - used[pas]);
    }

    used[pas] = 0;
    //cerr << '!' << _down.size() << '\n';
    for (auto who : rez[pas]) addVal(who);
    //cerr << '?' << _down.size() << '\n';
    rez[pas].clear();

}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d %d", &n, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &auxXX, &auxYY, &auxX, &auxY);
        auxX += auxXX;
        auxY += auxYY;

        pair<int, int> def = mp(auxX, auxY);

        _left.insert(def);
        _right.insert(def);
        _up.insert(def);
        _down.insert(def);

        //for (auto it = _down.begin(); it != _down.end(); it++)
        //cerr << it->first << ' ' << it->second << '\n';
        //cerr << '\n';
    }


    back(1, k);
    ans = max(ans, 1LL);
    printf("%I64d", ans);


    return 0;
}
