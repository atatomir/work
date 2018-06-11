#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

int defX[6] = {-1, 1, 0, 0, 0, 0};
int defY[6] = {0, 0, -1, 1, 0, 0};
int defZ[6] = {0, 0, 0, 0, -1, 1};

typedef pair<int, pair<int, int> > piii;

const pair<int, piii> ini = mp(0, mp(0, mp(0, 0)));

int n, m, k, q, x, y, z, i;
map< piii, int> M;
pair<int, piii> best, overall = ini;

int ask(int x, int y, int z) {
    if (x < 1 || x > n) return 0;
    if (y < 1 || y > m) return 0;
    if (z < 1 || z > k) return 0;

    auto& e = M[mp(x, mp(y, z))];

    if (e == 0) {
        printf("? %d %d %d\n", x, y, z);
        fflush(stdout);

        if (--q < 0) exit(-1);

        scanf("%d", &e);
        //e = n - abs(x - 1000000);
    }

    overall = max(overall, mp(e, mp(x, mp(y, z))));

    return e;
}

void check(int x, int y, int z) {
    int i, xx, yy, zz;

    for (int i = 0; i < 6; i++) {
        xx = x + defX[i];
        yy = y + defY[i];
        zz = z + defZ[i];

        if (ask(xx, yy, zz) > ask(x, y, z)) return;
    }

    printf("! %d %d %d\n", x, y, z);
    fflush(stdout);
    exit(0);
}


void solve_two_dimensions() {
    int i, l1, l2, c1, c2, mid;

    l1 = 1; l2 = n;
    c1 = 1; c2 = m;

    while (l2 - l1 + c2 - c1 > 0) {
        if (l2 - l1 > c2 - c1) {
            best = ini;
            mid = (l1 + l2) / 2;

            for (i = c1; i <= c2; i++)
                best = max(best, mp(ask(mid, i, 1), mp(mid, mp(i, 1))));

            x = best.second.first;
            y = best.second.second.first;
            z = 1;

            if (ask(x, y, z) <= overall.first) {
                if (overall.second.first != mid) {
                    if (overall.second.first < mid)
                        l2 = mid - 1;
                    else
                        l1 = mid + 1;

                    continue;
                }
            }

            check(x, y, z);

            if (ask(x - 1, y, z) > ask(x, y, z))
                l2 = mid - 1;
            else
                l1 = mid + 1;

        } else {
            best = ini;
            mid = (c1 + c2) / 2;

            for (i = l1; i <= l2; i++)
                best = max(best, mp(ask(i, mid, 1), mp(i, mp(mid, 1))));

            x = best.second.first;
            y = best.second.second.first;
            z = 1;



            if (ask(x, y, z) <= overall.first) {
                if (overall.second.second.first != mid) {
                    if (overall.second.second.first < mid)
                        c2 = mid - 1;
                    else
                        c1 = mid + 1;

                    continue;
                }
            }

            check(x, y, z);


            if (ask(x, y - 1, z) > ask(x, y, z))
                c2 = mid - 1;
            else
                c1 = mid + 1;
        }
    }

    check(l1, c1, 1);
}

void solve_one_dimension(int cc = 1, int hh = 1) {
    int l, r, mid;

    l = 1; r = n;

    while (r - l > 1) {
        mid = (l + r) >> 1;

        if (ask(l, cc, hh) >= ask(mid, cc, hh) && ask(l, cc, hh) >= ask(r, cc, hh)) {
            r = mid;
            continue;
        }

        if (ask(r, cc, hh) >= ask(mid, cc, hh) && ask(r, cc, hh) >= ask(l, cc, hh)) {
            l = mid;
            continue;
        }

        if (ask(mid, cc, hh) > ask(mid + 1, cc, hh))
            r = mid;
        else
            l = mid + 1;
    }

    check(l, cc, hh);
    check(r, cc, hh);

    if(ask(l, cc, hh) > ask(r, cc, hh)) {
        printf("! %d 1 1\n", l);
    } else {
        printf("! %d 1 1\n", r);
    }
    fflush(stdout);
    exit(0);
}

void solve_three_dimensions() {
    int i, j, l1, l2, c1, c2, h1, h2, mid;

    l1 = 1; l2 = n;
    c1 = 1; c2 = m;
    h1 = 1; h2 = k;

    while (l2 - l1 + c2 - c1 + h2 - h1 > 0) {

        if (c2 == c1 && h2 == h1)
            solve_one_dimension(c2, h2);

        if (l2 - l1 > c2 - c1 && l2 - l1 > h2 - h1) {
            best = ini;
            mid = (l1 + l2) / 2;

            for (i = c1; i <= c2; i++)
                for (j = h1; j <= h2; j++)
                    best = max(best, mp(ask(mid, i, j), mp(mid, mp(i, j))));

            x = best.second.first;
            y = best.second.second.first;
            z = best.second.second.second;

            if (ask(x, y, z) <= overall.first) {
                if (overall.second.first != mid) {
                    if (overall.second.first < mid)
                        l2 = mid - 1;
                    else
                        l1 = mid + 1;

                    continue;
                }
            }

            if (ask(x + 1, y, z) > ask(x, y, z)) {
                l1 = mid + 1;
                continue;
            }


            if (ask(x - 1, y, z) > ask(x, y, z)) {
                l2 = mid - 1;
                continue;
            }


            check(x, y, z);
            continue;
        }

        if (c2 - c1 > h2 - h1) {
            best = ini;
            mid = (c1 + c2) / 2;

            for (i = l1; i <= l2; i++)
                for (j = h1; j <= h2; j++)
                    best = max(best, mp(ask(i, mid, j), mp(i, mp(mid, j))));

            x = best.second.first;
            y = best.second.second.first;
            z = best.second.second.second;


            if (ask(x, y, z) <= overall.first) {
                if (overall.second.second.first != mid) {
                    if (overall.second.second.first < mid)
                        c2 = mid - 1;
                    else
                        c1 = mid + 1;

                    continue;
                }
            }

            if (ask(x, y + 1, z) > ask(x, y, z)) {
                c1 = mid + 1;
                continue;
            }

            if (ask(x, y - 1, z) > ask(x, y, z)) {
                c2 = mid - 1;
                continue;
            }



            check(x, y, z);

        } else {

            best = ini;
            mid = (h1 + h2) / 2;

            for (i = l1; i <= l2; i++)
                for (j = c1; j <= c2; j++)
                    best = max(best, mp(ask(i, j, mid), mp(i, mp(j, mid))));

            x = best.second.first;
            y = best.second.second.first;
            z = best.second.second.second;


            if (ask(x, y, z) <= overall.first) {
                if (overall.second.second.second != mid) {
                    if (overall.second.second.second < mid)
                        h2 = mid - 1;
                    else
                        h1 = mid + 1;

                    continue;
                }
            }

            if (ask(x, y, z + 1) > ask(x, y, z)) {
                h1 = mid + 1;
                continue;
            }

            if (ask(x, y, z - 1) > ask(x, y, z)) {
                h2 = mid - 1;
                continue;
            }



            check(x, y, z);

        }
    }

    check(l1, c1, h1);
}


int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d%d%d", &n, &m, &k, &q);

    if (m == 1 && k == 1) {
        solve_one_dimension();
        return 0;
    }

    if (k == 1) {
        solve_two_dimensions();
        return 0;
    }

    solve_three_dimensions();



    return 0;
}
