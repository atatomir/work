// prof. Carmen Popescu - Colegiul National "Gh. Lazar" Sibiu
// O(n^2)
#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>

using namespace std;

int a[100001];
int n,mx,p;
ifstream f("risc2.in");
ofstream g("risc2.out");
bitset<100001> b;
bitset<100001> c;

int main()
{
    int v,i,j,k,mn;
    f>>v>>n;
    for (i=1;i<=n;i++)
    {
        f>>a[i];
        if (a[i]>mx)
        {
            mx=a[i]; p=i;
        }
    }
    if (v==1)
    {
        // ordinea din stanga
        for (i=1;i<p;i++)
            if (a[i]>a[i+1])
            {
                g<<-1<<"\n";
                return 0;
            }
        // ordinea din dreapta
        for (i=p+1;i<n;i++)
            if (a[i]<a[i+1])
            {
                g<<-1<<"\n";
                return 0;
            }
        // in stanga sunt numere mai mici decat minimul din dreapta
        if (a[p-1]>a[n] || a[p+1]<a[p-1])
        {
            g<<-1<<"\n";
            return 0;
        }
        g<<p<<"\n";
    }
    else
    {

        // CAZUL 1: mutam ce nu e ok din stanga si dreapta



        // mn = minimul valorilor ce vor fi in dreapta dupa mutari
        mn=a[p];

        // marcam nr din stanga ce nu respecta ordinea si vor fi mutate la sfarsit
        k=0;
        mx=-1;  // mx= maximul valorilor ce se muta la sfarsit
        for (i=2;i<p;i++)           // pt fiecare valoare din stanga
            for (j=i-1;j>=1;j--)    // mutam (marcam) numerele din fata sa care sunt mai mari, adica ele vor trebui mutate
                if (a[j]>a[i] && !b[j])
                {
                    b[j]=true;
                    k++;
                    if (a[j]>mx) mx=a[j];
                    if (a[j]<mn) mn=a[j];
                }

        // marcam valorile din dreapta care nu respecta ordinea si vor fi mutate la sfarsit
        for (i=p+2;i<=n;i++)
        {
            if (a[i]<mn)
                mn=a[i];
            for (j=i-1;j>p;j--)
                if (a[j]<a[i] && !b[j])
                {
                    b[j]=true;
                    k++;
                    if (a[j]>mx) mx=a[j];
                }
        }

        // marcam valorile care au ramas in stanga (nemutate) care sunt mai mari decat minimul din dreapta si care vor
        // fi mutate la sfarsit
        for (i=1;i<p;i++)
            if (!b[i] && a[i]>mn)
            {
                b[i]=true;
                k++;
                if (a[i]>mx) mx=a[i];
            }

        // verificam  valorile din dreapta care au ramas nemutate si care sunt mai mici decat
        // maximul celor mutate, ele trebuie mutate la sfarsit
        for (i=n;i>p;i--)
            if (!b[i] && a[i]<mx)
                    k++;

        // CAZUL 2: mutam maximul la sfarsit pe urma mutam ce nu respecta ordinea
        // mn = minimul valorilor ce se vor afla in dreapta
        mn=a[p];
        int k1=1;  // am mutat maximul la sfarsit
        for (i=2;i<=n;i++)
            if (i!=p)
                for (j=i-1;j>=1;j--)
                    if (j!=p && a[j]>a[i] && !c[j])
                    {
                        c[j]=true;
                        k1++;
                        if (a[j]<mn) mn=a[j];
                    }
        // cautam valorile ramase nemutate si care sunt mai mari decat minimul celor mutate
        // si ele vor fi mutate
        for (i=1;i<=n;i++)
            if (i!=p && !c[i] && a[i]>mn)
                k1++;

        // solutia e cea din cazul cel mai favorabil
        if (k<k1)
            g<<k<<"\n";
        else
            g<<k1<<"\n";
    }

    return 0;
}
