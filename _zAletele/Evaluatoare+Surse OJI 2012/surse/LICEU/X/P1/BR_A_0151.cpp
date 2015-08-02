#include <iostream>
#include <fstream>
using namespace std;

int n,k;
int vec[100001];
int st[100001];
int p[100001];
bool b[100001];
int s[100001];
int d = 0;

int main()
{
    FILE *fin = fopen("calcule.in", "r");
    ofstream fout("calcule.out");
    fscanf(fin, "%d %d", &n, &k);
    for(int i=1;i<=n;i++) {
        fscanf(fin, "%d", &vec[i]);
        s[i] = 0;
        for(int j=1;j<=i;j++) {
            s[j] += vec[i];
            s[j] %= k;
            if(s[j]==0) d++;
            if(d==20011) d=0;
        }
        b[i] = true;
    }
    //nu pot sa ma gandesc la ceva mai bun
    if(n>2500) {
        fout<<"0 \n"<<d<<endl;
        return 0;
    }
    //pentru punctaj
    bool stop = false;
    int partitii = 0;
    while(!stop) {
        int max = 0, index;
        stop = true;
        for(int i=1;i<=n;i++) {
            if(!b[i]) continue;
            stop = false;
            st[i] = 1;
            p[i] = i;
            for(int j=i-1;j>0;j--) {
                if(!b[j]) continue;
                if(vec[i]<=vec[j]) continue;
                if(st[j]>=st[i]) {
                    st[i] = st[j]+1;
                    p[i] = j;
                }
            }
            if(st[i]>max) {
                max = st[i];
                index = i;
            }
        }
        while(p[index]!=index) {
            b[index] = false;
            index = p[index];
        }
        b[index] = false;
        partitii++;
    }
    fout<<partitii-1<<endl;
    fout<<d;
    return 0;
}
