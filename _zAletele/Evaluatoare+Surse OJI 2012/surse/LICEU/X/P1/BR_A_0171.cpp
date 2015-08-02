#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("calcule.in");
    ofstream g("calcule.out");

    int s[100001],i,j,n,k,min,x,poz,nr,u,v;
    f>>n>>k;
    min=20001;
    for(i=1;i<=n;i++)
        f>>s[i];

    //
   // while(o!=0)
    //{
        s[7]=0;
        s[10]=0;
        for(i=1;i<=n;i++)
            if(s[i]<min && s[i]!=0)
                {

                    min=s[i];
                    poz=i;
                }
        cout<<min<<endl;
        x=poz;
        u=0;
        while(min!=20001)
        {
            min=20001;
            for(i=x+1;i<=n && u==0;i++)
                {
                    if(s[i]<min && s[i]>s[x] && s[i]!=0 )
                        {
                        min=s[i];
                        poz=i;
                        }
                    if(s[i]==s[x])
                        {
                            v=i;
                            u=1;
                        }
                }
            for(i=x+1;i<v && u==1;i++)
                if(s[i]<min && s[i]>s[x] && s[i]!=0 )
                    {
                        min=s[i];
                        poz=i;
                    }
            s[x]=0;
            s[poz]=0;
            x=poz;

        }

        // Stop while
      //  o=0;
        //for(i=1;i<=n && o==0;i++)
          //  if(s[i]!=0)
            //    o=1;
            for(i=1;i<=n;i++)
            cout<<s[i]<<" ";
  //  }


    return 0;
}
