#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

#define maxN 3333

int n, m, i, j, ln, co;
char s[maxN][maxN];
int how_ln[maxN], how_co[maxN];

bool added_ln[maxN], added_co[maxN];
queue<int> Q;
int removed;

vector<string> work;
string aux;

bool is_possible() {
    int i, j;
    
    ln = n; co = m;
    for (i = 1; i <= n; i++)
        if (how_ln[i] == co || how_ln[i] == 0)
            Q.push(i), added_ln[i] = true;
    for (i = 1; i <= m; i++)
        if (how_co[i] == ln || how_co[i] == 0)
            Q.push(-i), added_co[i] = true;   
    
            
    
    while (!Q.empty()) {
        int act = Q.front(); Q.pop();
        
        //printf("Now : %d\n", act);
        
        if (act > 0) { //! line
            ln--;
            removed += co;
        
            for (i = 1; i <= m; i++) {
                if (added_co[i]) continue;
                
                if (s[act][i] == 'R') {
                    how_ln[act]--;
                    how_co[i]--;
                }
                
                if (how_co[i] == ln || how_co[i] == 0) {
                    Q.push(-i);
                    added_co[i] = true;
                }
            }
            
        } else { //! column
            act *= -1;
            co--;
            removed += ln;
            
            for (i = 1; i <= n; i++) {
                 if(added_ln[i]) continue;
                
                if (s[i][act] == 'R') {
                    how_ln[i]--;
                    how_co[act]--;
                }
                
                if (how_ln[i] == co || how_ln[i] == 0) {
                    Q.push(i);
                    added_ln[i] = true;
                }
            }
        }
    }
    
    return removed == n * m;
}

int main() {
    scanf("%d %d\n", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s[i] + 1);
        for (j = 1; j <= m; j++) {
            if (s[i][j] == 'R') {
                how_ln[i]++;
                how_co[j]++;
            }
        }
    }
    
    if (!is_possible()) {
        printf("-1");
        return 0;
    }
    
    int ans = n + m - 1;
    
    //! try with lines
    work.clear();
    for (i = 1; i <= n; i++) {
        aux.clear();
        for (j = 1; j <= m; j++) aux.pb(s[i][j]);
        work.pb(aux);
    }
    
    sort(work.begin(), work.end());
    
    for (i = 0; i < work.size(); i = j + 1) {
        for (j = i; j + 1 < work.size(); j++) 
            if (work[j + 1] != work[i]) break;
            
        ans = min(ans, n + m - (j - i + 1));
    }
    
    //! try with columns
    work.clear();
    for (j = 1; j <= m; j++) {
        aux.clear();
        for (i = 1; i <= n; i++) aux.pb(s[i][j]);
        work.pb(aux);
    }
    
    sort(work.begin(), work.end());
    
    for (i = 0; i < work.size(); i = j + 1) {
        for (j = i; j + 1 < work.size(); j++) 
            if (work[j + 1] != work[i]) break;
            
        ans = min(ans, n + m - (j - i + 1));
    }
   
    
    printf("%d", ans); 
    
}

