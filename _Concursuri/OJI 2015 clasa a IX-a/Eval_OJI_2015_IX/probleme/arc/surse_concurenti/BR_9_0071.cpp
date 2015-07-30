#include <iostream>
#include <fstream>

using namespace std;








int main()
{
    ifstream input("arc.in");
    ofstream output("arc.out");

    //citire
    int v;
      input >> v;
    int n;
      input >> n;
    int bile[n];
    for(int i=0; i<n; i++) input >> bile[i];

    //cerinta 1
    if(v==1){
     int x=1,y;
     y=bile[0];
       for(int i=0; i<n; i++){
         if(bile[i]==y) continue;
            else{
             x++;
             y=bile[i];
            }
         }
         output << x;
    }

    //cerinta 2
    if(v==2){

    }


    return 0;
}
