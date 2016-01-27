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
  
#define maxN 50011
 
int n, i, t;
char s[maxN];
int pos1, pos2;
 
int get_min_lex() {
    int pos = 1;
    int best = 0;
    int l = 0;
     
    while (pos < n && best + l + 1 < n) {
        if (s[best + l] == s[(pos + l) % n]) l++;
        else
        if (s[best + l] < s[(pos + l) % n]) pos += l + 1, l = 0;
        else
        if (s[best + l] > s[(pos + l) % n]) best = max(pos, best + l + 1), pos = best + 1, l = 0;
    }
     
    return best;
}
  
int main()
{
    freopen("csir.in","r",stdin);
    freopen("csir.out","w",stdout);
  
    for(scanf("%d", &t); t > 0; t--) {
        memset(s, 0, sizeof(s));
        scanf("%s", s);
        n = strlen(s);
             
        pos1 = get_min_lex();
         
        for (i = 0; i < n; i++)
            s[i] = (s[i] == 'A' ? 'B' : 'A');
             
        pos2 = get_min_lex();
         
        for (i = 0; i < n; i++)
            s[i] = (s[i] == 'A' ? 'B' : 'A');
             
        int n1, n2;
        bool good = true;
        n1 = n2 = 0;
         
        for (i = 0; i < n; i++) {
            n1 += s[ (pos1 + i) % n ] - 'A';
            n2 += s[ (pos2 + i) % n ] - 'A';
             
            if (n1 - n2 < -1 || n1 - n2 > 1)
                good = false;
        }
         
        //printf("%d %d\n", pos1, pos2);
         
        if (good)
            printf("1\n");
        else
            printf("0\n");
    }
  
    return 0;
}
