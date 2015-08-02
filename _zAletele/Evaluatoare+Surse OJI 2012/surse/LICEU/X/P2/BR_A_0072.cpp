#include <fstream>
using namespace std;
int n,k,a[100000],c[100000],b[100000],d[100000],i,j,q;
int main()
{
    ifstream f("calcule.in");
    ofstream g("calcule.out");
    f>>n>>k;
    for(i=1;i<=n;i++)
        f>>a[i];
    b[1]=1;c[1]=1;
    for(i=2;i<=n;i++){
        q=0;
        d[i]=1;
        c[i]=i;
        for(j=i-1;j>=1;j--)
            if(a[i]>a[j]&&(a[c[i]]<a[c[j]]||!c[j])){
                b[i]=b[i-1];
                q=j;
                d[i]=d[j]+1;
                }
        if(!q){
            b[i]=b[i-1]+1;
        }
        else{
            for(j=1;j<q;j++)
                if(c[j]&&(c[j]==c[q]||c[j]==q))
                    c[j]=i;
            c[q]=i;
        }
        c[i]=0;
    }
    g<<b[n]<<'\n';
    f.close();
    g.close();
    return 0;
}
