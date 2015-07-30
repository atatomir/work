#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxP 10005
#define x first
#define y second

long p,i;
char s[maxP];
pair<long,long> pos,newPos;
long det=0,arie=0;
long nord=0,est=0,vest=0,sud=0;

int main()
{
    freopen("ape.in","r",stdin);
    freopen("ape.out","w",stdout);

    scanf("%ld\n%s",&p,s+1);
    for(i=1;i<=p;i++){
        newPos = pos;
        switch(s[i]){
            case 'N': {
                        newPos.y++;
                        break;
                      }
            case 'S': {
                        newPos.y--;
                        break;
                      }
            case 'E': {

                        newPos.x++;
                        break;
                      }
            case 'V': {
                        newPos.x--;
                        break;
                      }
        }
            det += pos.x*newPos.y - pos.y*newPos.x;
            pos = newPos;

        nord = max(nord,newPos.y);
        sud  = min(sud ,newPos.y);
        est  = max(est ,newPos.x);
        vest = min(vest,newPos.x);
    }

    printf("%ld %ld",est-vest-1,nord-sud-1);
    if(det > 0) printf(" 1 "); else printf(" 0 ");

    if(det < 0) det = -det;

    arie = det + 2 - p;
    arie = arie / 2;

    printf("%ld\n",arie);

    return 0;
}
