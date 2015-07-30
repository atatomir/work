#include <cstdio>

using namespace std;

int main()
{
    long a,b,t,rez=0,points=0;

    scanf("%ld %ld",&a,&b);

    if (a > b) { t = a; a = b; b = t;}

    char c;
    for (int i = 0;i<=a;i++) scanf("%*c",&c);
    for (int i = a+1;i<=b;i++) {
        scanf("%c",&c);
        if (c=='U') {
            rez++;
            points++;
        } else {
            if (rez > 0) {
                rez--;
                points--;
            } else {
                points++;
            }
        }
    }

    printf("%ld",points);

    return 0;
}
