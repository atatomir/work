#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

int main()
{
    ifstream in("triunghi.in");
    ofstream out("triunghi.out");
    //Declarari si citiri.
    int v,k,lungimi[200],n,i,j,x,setnou[200],lungadaugat,min=99999;
    in>>v;
    in>>n;
    in>>k;
    for (i=1;i<=n;i++)
        in>>lungimi[i];
    //Incheiere citiri si declarari

    if (v==1)
    {for (i=1;i<=n;i++)
        if (min>lungimi[i])
            min=lungimi[i];//retin valoare minima din lungimi in variabila min

    setnou[1]=min;
    cout<<"Introduceti lungimiele (care pot fi negative sau pozitive) care vor fi adaugate/scazute la lungimea initiala : "<<'\n';
    for (i=2;i<=k;i++)
    {
        cin>>lungadaugat;
        setnou[i]=min+lungadaugat;
    }
    for (i=1;i<=k;i++)
        out<<setnou[i]<<" ";}


    if (v==2)
    {
        for (i=1;i<=n;i++)
            setnou[i]=lungimi[i];
        cout<<"Introduceti lungimiele care vor fi adaugate la sirul initial : "<<'\n';
        for (i=n+1;i<=k;i++)
            {cin>>lungadaugat;
            setnou[i]=lungadaugat;}
        for (i=1;i<=k;i++)
            out<<setnou[i]<<" ";
    }
    in.close(); out.close();
    return 0;
}
