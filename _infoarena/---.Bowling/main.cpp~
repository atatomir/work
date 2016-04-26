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
  
#define maxN 1011
  
int t, ti, ans;
int n, i, j;
int last, x;
  
vector<int> aux;
int sg[maxN];
  
void precomp() {
    sg[0] = 0;
    sg[1] = 1;
  
    for (i = 2; i <= 200; i++) {
        aux.clear();
  
        for (j = 1; j <= i; j++)
            aux.pb(sg[j - 1] ^ sg[i - j]);
        for (j = 1; j < i; j++)
            aux.pb(sg[j - 1] ^ sg[i - j - 1]);
  
        sort(aux.begin(), aux.end());
        aux.resize(unique(aux.begin(), aux.end()) - aux.begin());
  
        aux.pb(-1);
        for (j = 0; aux[j] == j; j++);
        sg[i] = j;
    }
}
 
int get_sg(int x) {
    if (x <= 100) return sg[x];
     
     
    x -= 99;
    x %= 12; if (x == 0) x = 12;
     
    return sg[99 + x];
}
  
int main()
{
    freopen("bowling.in","r",stdin);
    freopen("bowling.out","w",stdout);
  
    precomp();
  
    scanf("%d", &t);
    for(ti = 1; ti <= t; ti++) {
        scanf("%d", &n);
  
        last = 0; ans = 0;
        for (i = 1; i <= n; i++) {
            scanf("%d", &x);
            if (x == 0) {
                ans ^= get_sg(last);
                last = 0;
            } else {
                last++;
            }
        }
  
        ans ^= get_sg(last);
        if (ans != 0)
            printf("Nargy\n");
        else
            printf("Fumeanu\n");
    }
  
  
    return 0;
}
