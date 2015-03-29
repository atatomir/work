#include <iostream>
#include <cstdio>

using namespace std;

double X,Y,T,Z;

int main()
{
    freopen("meeting.in","r",stdin);
    freopen("meeting.out","w",stdout);

    scanf("%lf %lf %lf",&X,&Y,&Z);
    T = (Y-X)*60.0;

    printf("%.9lf",1-((T-Z)/T)*((T-Z)/T));

    return 0;
}
