#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;
ifstream f("triunghi.in");
ofstream g("trunghi.out");
int main()
{int j,min,v,n,k,sir[100],max,med,s;
    f>>v>>n>>k;
    for(j=1;j<=n;j++)
    {f>>sir[j];}
   for(j=1;j<=n;j++)
   if(sir[1]>sir[j])
   min=sir[j];
      for(j=1;j<=n;j++)
   if(sir[1]<sir[j])
  max=sir[j];
   s=min+max;
   med=s/2;
   if(v==1){
    vector<int> sir1(k);
   fill(sir1.begin(),sir1.end(),min);
    replace(sir1.begin()+2,sir1.end(),min,min*10);
    replace(sir1.begin()+3,sir1.end(),min*10,min*6);
    replace(sir1.begin()+4,sir1.end(),min*6,min*7);
    for(size_t t=0;t<sir1.size();t++)
    g<<sir1[t]<<" ";}
    else {

                      vector<int> sir2(k);
                     fill(sir2.begin(),sir2.end(),min);
                     replace(sir2.begin()+1,sir2.end(),min,med);
                     replace(sir2.begin()+2,sir2.end(),med,max);
                     replace(sir2.begin()+3,sir2.end(),max,med-3);
                     replace(sir2.begin()+4,sir2.end(),med-3,min-1);
                         for(size_t h=0;h<sir2.size();h++)

                     g<<sir2[h]<<" ";
                  }
    f.close();
    g.close();
    return 0;
}

