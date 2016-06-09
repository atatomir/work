#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;


#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 111

int n, i, x;
deque<int> base, act;
int sol;

void nosol() {
    printf("no quotation");
    exit(0);
}

bool check(int degree) {
    int i;
    
    act = base;
    for (i = degree; i > 1; i--) {
        if (act.empty()) return false;    
        
        int aux = act.front(); act.pop_front();
        if (aux < i) return false;
        aux -= i;
        if (aux > 0) act.push_front(aux);
        
        if (act.empty()) return false;
        
        aux = act.back(); act.pop_back();
        if (aux < i) return false;
        aux -= i;
        if (aux > 0) act.pb(aux);
    }

    if (act.empty()) return false;
    int aux = 0;

    while (!act.empty()) aux += act.back(), act.pop_back(); 
    if (aux % 2 == 1) return false;
    
    return true;
}

int main() {
    
    scanf("%d", &n);
    while (!base.empty()) base.pop_back();
    
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        base.pb(x);
    }
    
    sol = 0;
    if (n == 1 && base.front() == 2) sol = 1;
    if (n == 2 && base.front() == 1 && base.back() == 1) sol = 1;
    
    for (i = 2; i <= 100; i++)
        if (check(i))
            sol = i;
            
    if (sol == 0) nosol();
    printf("%d", sol);
    
    
    return 0;
}
