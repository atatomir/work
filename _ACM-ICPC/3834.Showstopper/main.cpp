#include <iostream>
#include <fstream>

using namespace std;

struct {
    long x,y,z;
} a[1000000];

char s[105];
long i,cont,maxy,j,m,target,contor = 0;

//ifstream f("show.in");
//ofstream fo("show.out");

inline long getSum(long maxim) {
    static long max,i;
    long rez = 0;

    for(i=1;i<=cont;i++) {
        if (a[i].x > maxim) continue;

        max = maxim;
        if (a[i].y < max) max = a[i].y;
        rez += 1 + ((max - a[i].x)/a[i].z);
    }
    return rez;
}

inline long getLong() {
    long x = 0;
    while (s[i] == ' ') i++;
    while ((s[i] != ' ')&&(s[i] != '\0')) {
        x = x*10 + s[i] - '0' ;
        i++;
    }

    return x;
}

inline void getTest(){
    cin.getline(s,100,'\n');
    while(s[0] == '\0') cin.getline(s,100,'\n');

    cont = 0; maxy = 0;
    while(s[0] != '\0') {
        i = 0; cont++;
        a[cont].x = getLong(); //fo << a[cont].x << '\n';
        a[cont].y = getLong(); //fo << a[cont].y << '\n';
        a[cont].z = getLong(); //fo << a[cont].z << '\n' << '\n';

        if(maxy < a[cont].y) maxy = a[cont].y;

        if (cin.eof()) return;
        cin.getline(s,100,'\n');
    }
}

int main()
{

    while(!cin.eof()) {
        getTest();
        if(getSum(maxy) % 2 == 0)
            cout << "no corruption\n";
        else {

            i = 1; j = maxy;
            do {
                m = (i+j)/2;
                if (getSum(m) % 2 == 0)
                    i = m+1;
                else
                    j = m-1;
            }   while (i <= j);
            target = i;

            contor = 0;
            for(i=1;i<=cont;i++) {
                if ((a[i].x <= target)&&(a[i].y >= target))
                    if ((target - a[i].x)%a[i].z == 0) contor++;
            }

            cout << target << " " << contor << "\n";

        }

    }


    //f.close();
    //fo.close();
    return 0;
}
