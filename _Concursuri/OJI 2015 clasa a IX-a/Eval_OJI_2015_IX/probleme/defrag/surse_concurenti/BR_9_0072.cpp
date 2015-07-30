#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream input("defrag.in");
    ofstream output("defrag.out");

    int v;
    input >> v;
    int p, s;
    input >> p >>s;
    int c;
    input >> c;
    int P[c], S[c];
    for(int i=0; i<c; i++){
        input >> P[i] >>S[i];
    }


    if(v==1){
         int y=P[0],k=1;
        for (int i=0; i<c; i++){
            if(P[i]==y) continue;
             else{
                k++;
                y=P[i];
             }

        }

        output << p-k;

    }


    return 0;
}
