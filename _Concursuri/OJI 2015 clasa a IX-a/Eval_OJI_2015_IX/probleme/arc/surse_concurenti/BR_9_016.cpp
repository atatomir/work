#include<fstream>
using namespace std;
int main()
{
    int n,v[90],i,a,d[90],o=0,j,k,nr=0;
    ifstream f("arc.in");
    ofstream g("arc.out");
    f>>a>>n;
    for(i=1;i<=n;i++)f>>v[i];
    if(a==1){
    while(nr==0)for(i=1;i<=n;i++)if(v[i]!=v[i+1])nr++;
        else{k=0;
                for(j=i;j<=n;j++)if(v[i]==v[i+j])k++;
        if(k!=0)nr++;}
    g<<nr-1<<'\n';}
    f.close();
    g.close();
    return 0;
}
