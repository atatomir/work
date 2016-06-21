#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>


using namespace std;


#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 4016

int n, i;
int dim[maxN], id[maxN];
char s[maxN][maxN];

vector< pair<int, int> > act, aux; 
map< pair<int, int>, pair<int, int> > prov;

int belong[maxN];
vector<int> sol[2];




bool cmp(int a, int b) {
    return dim[a] < dim[b];
}

bool check(int sm, int bg) {
    if (dim[sm] >= dim[bg]) return false;
    
    int i, j;
    for (i = j = 1; i <= dim[sm]; i++) {
        while (j <= dim[bg] && s[bg][j] != s[sm][i]) j++;
        if (j > dim[bg]) return false;
        j++;
    }

    return true;
}

int main() {
    
    scanf("%d\n", &n); 
    scanf("%s\n", s[n + 1] + 1);
    for (i = 1; i <= n; i++) scanf("%s\n", s[i] + 1), dim[i] = strlen(s[i] + 1), id[i] = i;
    sort(id + 1, id + n + 1, cmp);
    
    prov.clear();
    
    n++; dim[n] = strlen(s[n] + 1);
    id[n] = n;
    act = {mp(n, n)};
    
    for (i = n - 1; i > 0; i--) {
        aux = act; act.clear();
        
        for (auto e : aux) {
            if (check(id[i], id[e.first])) act.pb(mp(i, e.second)), prov[mp(i, e.second)] = e;
            if (check(id[i], id[e.second])) act.pb(mp(i, e.first)), prov[mp(i, e.first)] = e;
        }
        
        sort(act.begin(), act.end());
        act.resize(unique(act.begin(), act.end()) - act.begin());
        
        if (act.size() == 0) break;
        
        for (int j = 0; j < act.size() && act.size() == 3; j++) {
            if (act[j].second != aux[0].first) continue; 
            act[j] = act.back();
            act.pop_back();
        }
    }
    
    if (act.empty()) {
        printf("impossible");    
        return 0;
    }
    
    auto now = act[0];
    belong[now.first] = 0;
    belong[now.second] = 1;
    
    sol[0].pb(now.first);
    sol[1].pb(now.second);
    
    while (now != mp(n, n)) {
        auto prev = prov[now];  
        
        if (now.second == prev.first) {
            belong[prev.second] = belong[now.first];
            sol[ belong[prev.second] ].pb(prev.second);
        } else {
            belong[prev.first] = belong[now.first];
            sol[ belong[prev.first] ].pb(prev.first);
        }
        
        now = prev;
    }
    
    sol[0].pop_back();
    sol[1].pop_back();
    
    printf("%d ", sol[0].size());
    printf("%d\n", sol[1].size());
    
    for (auto e : sol[0])
        printf("%s\n", s[id[e]] + 1);
    
    for (auto e : sol[1])
        printf("%s\n", s[id[e]] + 1);
    
    return 0;
}