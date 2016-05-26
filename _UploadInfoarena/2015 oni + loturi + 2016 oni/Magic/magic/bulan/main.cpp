#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;
static int B16[100000],
B[16]={
1+2+4+8+16+32+64+128+256+512+1024+2048+4096+8192+16384+32768,
1  +4  +16   +64    +256    +1024     +4096     +16384,
1+2    +16+32       +256+512          +4096+8192,
1      +16          +256              +4096,
1+2+4+8             +256+512+1024+2048,
1  +4               +256    +1024,
1+2                 +256+512,
1                   +256,
1+2+4+8+16+32+64+128,
1  +4  +16   +64,
1+2    +16+32,
1      +16,
1+2+4+8,
1  +4,
1+2,
1};
int main()
{
	freopen("magic4.out","w",stdout);
	srand(time(NULL));

    int M,i,j,k,u,ans;

		for(i=1;i<=100000;i++) printf("%ld\n",i ^ ( rand()%(1<<16) ) );

	return 0;
}
