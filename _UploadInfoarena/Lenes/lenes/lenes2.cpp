// prof. Carmen Popescu - Colegiul National "Gh. Lazar" Sibiu
#include <fstream>
#include <climits>

using namespace std;

int a[502][502],sum[502],m,n;
int mn=INT_MAX;

ifstream f("lenes.in");
ofstream g("lenes.out");

int calc(int c,int k)
{
    int s=0,i1=1,i2=1,i;
    for (i=1;i<=k;i++)
        if (a[i1][c-1]<a[i2][c+1])
        {
            s+=a[i1][c-1];
            i1++;
        }
        else
        {
            s+=a[i2][c+1];
            i2++;
        }
    s+=sum[c];
    return s;
}

int main()
{
    int i,j,i1,i2,i3,ok,j1,k1,k2,k3,k4,p;
    int s1,s2,s;
    f>>p;
    f>>m>>n>>k1>>k2;
    for (i=1;i<=m;i++)
    {
        for (j=1;j<=n;j++)
        {
            f>>a[i][j];
            sum[j] += a[i][j];
        }
        a[i][0]=INT_MAX;
        a[i][n+1]=INT_MAX;
    }
    for (j=1;j<=n;j++)
    {
        a[0][j]=INT_MAX;
        a[m+1][j]=INT_MAX;
        // sortam coloana j
        for (i=1;i<m;i++)
            for (i1=i+1;i1<=m;i1++)
                if (a[i][j]>a[i1][j])
                {
                    s=a[i][j];
                    a[i][j]=a[i1][j];
                    a[i1][j]=s;
                }

    }

    if (p==1)
    {
        for (j=1;j<n;j++)
        {
            s=calc(j,k1);
            if (s<mn) mn=s;
        }
        g<<mn<<"\n";
    }
    else
    {
        int cc;
        // cazul 1: doua coloane alaturate (j si j+1)
        for (j=2;j<n-1;j++)
        {
            for (int g=1;g<=2;g++)
            {
                s=0;
                for (i=1;i<=k1;i++)
                    s=s+a[i][j-1];
                for (i=1;i<=k2;i++)
                    s+=a[i][j+2];

                s=s+sum[j]+sum[j+1];
                if (s<mn) mn=s;
                s1=k1; k1=k2; k2=s1;
            }

        }

        // cazul 2: coloanele j si j+2 (o coloana goala intre ele)

        for (j=2;j<n-2;j++)
            for (int g=1; g<=2; g++)
            {
                s1=0;
                for (i=1; i<=k1; i++)
                    s1+=a[i][j-1];
                for (i=1; i<=k2; i++)
                    s1+=a[i][j+3];

                // incercam sa inlocuim o parte din popasuri cu popasuri pe coloana din mijloc, j+1
                i1=k1; i2=1; i3=k2;
                s=s1;
                do
                {
                    ok=0;
                    if (i1>0 && a[i1][j-1]>=a[i3][j+3] && a[i1][j-1]>a[i2][j+1])  // inlocuim un popas de pe coloana j-1 cu popas pe
                    {
                        // coloana j+1
                        s=s+a[i2][j+1]-a[i1][j-1];
                        i1--;
                        i2++;
                        ok=1;
                    }
                    else if (i3>0 && a[i3][j+3]>=a[i1][j-1] && a[i3][j+3]>a[i2][j+1]) // inlocuim un popas de pe coloana j-1 cu popas pe
                    {
                        // coloana j+1
                        s=s+a[i2][j+1]-a[i3][j+3];
                        i3--;
                        i2++;
                        ok=1;
                    }
                }
                while (ok==1);
                s+=sum[j]+sum[j+2];
                if (s<mn) mn=s;

                s=k1; k1=k2; k2=s;
            }

        // caz particular la cazul 2: coloana 1 si coloana 3
        for (int g=1;g<=2;g++)
        {
            s1=0;
            for (i=1;i<=k1;i++)
                s1+=a[i][2];
            i1=k1+1; i2=1;
            for (i=1;i<=k2;i++)
                if (i1<=m && a[i1][2]<a[i2][4])
                {
                    s1+=a[i1][2]; i1++;
                }
                else
                {
                    s1+=a[i2][4]; i2++;
                }
            s1+=sum[1]+sum[3];
            if (s1<mn) mn=s1;

            s1=k1; k1=k2; k2=s1;
        }

        // caz particular la cazul 2: coloana n-2 si coloana n
        for (int g=1;g<=2;g++)
        {
            s1=0;
            for (i=1;i<=k1;i++)
                s1+=a[i][n-1];
            i1=k1+1; i2=1;
            for (i=1;i<=k2;i++)
                if (i1<=m && a[i1][n-1]<a[i2][n-3])
                {
                    s1+=a[i1][n-1]; i1++;
                }
                else
                {
                    s1+=a[i2][n-3]; i2++;
                }
            s1+=sum[n]+sum[n-2];
            if (s1<mn) mn=s1;

            s1=k1; k1=k2; k2=s1;
        }

        // cazul 3: doua linii total independente
        for (j=1;j<=n-3;j++)
        {
            s1=calc(j,k1); // dus pe j intrs pe j1
            s2=calc(j,k2); // dus pe j1 intors pe j
            for (j1=j+3;j1<=n;j1++)
            {
                i1=s1+calc(j1,k2);
                i2=s2+calc(j1,k1);
                if (i1<mn) mn=i1;
                if (i2<mn) mn=i2;
            }
        }
        g<<mn<<"\n";
    }
}
