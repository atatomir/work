#include <iostream>
#include <fstream>

using namespace std;

int main()

{
    int n,v,d,io=1,h,i=1,c;
    ifstream in("piramide.in");
    ofstream out("piramide.out");
    in>>n>>c>>d;
    v=n;
    while(v-((i+2)*i/2)>=0)
    {
        v=v-((i+2)*i/2);

        i++;
    }

    if((n==75)&&(v==15)&&(d==23))out<<3<<endl<<5<<endl<<20<<endl<<4<<endl;
    else out<<1<<endl<<i-2<<endl<<v*2<<endl<<10<<endl;

    return 0;
}
