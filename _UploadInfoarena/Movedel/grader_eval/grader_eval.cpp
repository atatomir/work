#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 2016
#define limit 200011
#define def 16000

int n, m, i, pos;
string a, b;

bool ciur[limit];
vector<int> primes;
int cnt;

int p1, p2;


void result(char msg[], int p){
    fprintf(stderr, "%s", msg);
    printf("%d", p);
    exit(0);
}

void make_ciur() {
    ll i, j;

    for (i = 2; i < limit && primes.size() < def; i++) {
        if (ciur[i]) continue;
        primes.pb(i);
        for (j = i * i; j < limit; j += i)
            ciur[j] = true;
    }
}

bool check() {
    p1 = p2 = 0;
    n = a.size();

    for (i = 0; i < n; i++) {
        if ('a' > a[i] || a[i] > 'z') result("Utilizeaza doar litere mici ale alfabetului englez :)", 0);
        p1 |= 1 << (a[i] - 'a');
    }

    for (i = 0; i < n; i++) {
        if ('a' > b[i] || b[i] > 'z') result("Utilizeaza doar litere mici ale alfabetului englez :)", 0);
        p2 |= 1 << (b[i] - 'a');
    }

    return ((p1 & p2) != 0) && (n != 0);
}

void rotate(int how) {
    how %= a.size();

    string aux = "";
    for (i = 0; i < how; i++) aux.pb(a[i]);
    for (i = how; i < a.size(); i++) a[i - how] = a[i];
    a.resize(a.size() - how);
    a += aux;
}

void del() {
    int pos = 0;
    n = a.size();

    for (i = 0; i < n; i++) {
        if (a[i] == b[i]) continue;
        a[pos] = a[i];
        b[pos] = b[i];
        pos++;
    }

    n = pos;
    a.resize(pos);
    b.resize(pos);
}



int main()
{
    ifstream fin("movedel.in");
    ifstream fout("movedel.out");

    fin >> n >> m;
    fout >> a >> b;

    if (a.size() != n) result("Sirul a nu contine fix n caractere", 0);
    if (b.size() != n) result("Sirul b nu contine fix n caractere", 0);

    make_ciur();

    pos = 0;
    while (check() && pos < primes.size()) {
        cnt++;
        rotate(primes[pos++]);
        del();
    }

    double ans = min(1.00, 1.00 * cnt / m);
    int score = 10.00 * ans;

    if (score == 0) result("Mai incearca", score);
    if (score <= 6) result("Binisor", score);
    if (score <= 9) result("Inca un pic", score);
    result("Perfect", score);


    return 0;
}
