#include <cstdio>
#include <iostream>

using namespace std;

#define maxN 100011

int n, m, k, i;
pair<int, int> sw[maxN];

int pos_first[maxN];
int pos_k[maxN];

int move(int pos, int id) {
    if (sw[id].first == pos)
        return sw[id].second;
    if (sw[id].second == pos)
        return sw[id].first;
    return pos;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= m; i++) 
        scanf("%d%d", &sw[i].first, &sw[i].second);
    
    pos_first[0] = 1;
Successfully done 3 tests (2ms - 1564KB) 
    for (i = 1; i <= m; i++)
        pos_first[i] = move(pos_first[i - 1], i);
        
    pos_k[m] = k;
    for (i = m; i > 0; i--) 
        pos_k[i - 1] = move(pos_k[i], i);
        
    for (i = 0; i < m; i++) {
        if (pos_first[i] == pos_k[i + 1]) {
            printf("%d", i + 1);
            return 0;
        } 
    }
        
    
}

