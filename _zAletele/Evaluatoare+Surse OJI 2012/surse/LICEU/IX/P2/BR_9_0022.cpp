#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("clepsidru.in");
    ofstream h("clepsidru.out");
    int n,b,i,sec=0,s1,p1;
    int v[2000];
    f>>n>>b;
    v[1]=b;
    while(v[n+1]!=b)
        {
            sec++;
            for(i=1;i<=n;i++)
                if(v[i+1]==0)
                    {v[i]=v[i]-1;
                    v[i+1]=v[i+1]+1;
                    break;}
                else
                    {
                        v[i]=v[i]-1;
                        v[i+1]=v[i+1]+1;
                    }
        }
    cout<<sec;
    return 0;
}
