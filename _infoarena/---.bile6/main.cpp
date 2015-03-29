#include <fstream>
#include <cstdio>

using namespace std;

//ATENTIE , printf a mers mai repede

long n,i,bile,pare,impare,first,first2;

int main()
{
    ifstream fin("bile6.in");

    freopen("bile6.out","w",stdout);

    fin >> n;
    bile = 2*n+1;
    pare = n / 2;
    impare = n - pare;

    first = 2*pare+1 + impare ;
    first2 = pare;

    for(i=1;i<n;i = i+2){
            printf("%ld %ld\n%ld %ld\n",first,first+i,first2,first2+i+1);
            first--;
            first2--;

    }
    if(n % 2 == 1) {
        printf("%ld %ld\n",first,first+i);
    }

    printf("%ld\n",pare+1);

    fin.close();
    return 0;
}
