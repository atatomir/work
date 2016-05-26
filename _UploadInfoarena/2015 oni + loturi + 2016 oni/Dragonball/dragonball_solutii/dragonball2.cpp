#include<stdio.h>
#include<queue>
using namespace std;

#define NMAX 1005
#define MMAX 10005
#define baza 10

int v[NMAX][MMAX],vmax[NMAX][MMAX],scanduri[NMAX];
char s[MMAX];
int n,t,ok;

inline void GiveValue(int a[], char s[])
{
    a[0] = strlen(s);
    for(int i = a[0]; i >= 1; i--)
        a[i] = s[a[0] - i] - '0';
}

inline void Difference(int a[], int b[])
{
    int i, t = 0;
    for(i = 1; i <= a[0] || i <= b[0] || t; i++)
    {
        if(i > a[0])
            a[i] = 0;
        if(i > b[0])
            b[i] = 0;
        a[i] = a[i] - b[i] - t;
        if(a[i] < 0)
        {
            a[i] += baza;
            t = 1;
        }
        else
            t = 0;
    }
    while(a[0] > 0 && !a[a[0]])
        a[0]--;
}

inline void Equality(int a[], int b[])
{
    for(int i = 0; i <= b[0]; i++)
        a[i] = b[i];
}

inline void Divizion(int index)
{
    int i, t = 0;
    for(i = v[index][0]; i >= 1; i--)
    {
        vmax[index][i] = (t * baza + v[index][i]) / scanduri[index];
        t = (t * baza + v[index][i]) % scanduri[index];
    }
    while(vmax[index][0] > 0 && !vmax[index][vmax[index][0]])
        vmax[index][0]--;
    if(t > 0)
    {
        for(i = 1; i <= vmax[index][0] && vmax[index][i] == 9; i++)
            vmax[index][i] = 0;
        if(i > vmax[index][0])
        {
            vmax[index][0] = i;
            vmax[index][i] = 1;
        }
        else
            vmax[index][i]++;
    }
}//37 2    1

inline int Compare(int a[], int b[])
{
    if(a[0] > b[0])
        return 1;
    if(a[0] < b[0])
        return -1;
    for(int i = a[0]; i >= 1; i--)
        if(a[i] > b[i])
            return 1;
        else if(a[i] < b[i])
            return -1;
    return 0;
}

inline void PrintNum(int a[])
{
    for(int i = a[0]; i >= 1; i--)
        printf("%d", a[i]);
    printf("\n");
}

class cmp
{
public:
    bool operator()(const int& a,const int& b)
    {
        ok = Compare(vmax[a], vmax[b]);
        if(!ok)
            return a > b;
        return (ok == -1);
    }
};

priority_queue<int, vector<int>, cmp> myheap;

int main ()
{
    int i, best;

    freopen("dragonball.in","r",stdin);
    freopen("dragonball.out","w",stdout);

    scanf("%d%d ",&n,&t);
    scanf("%s",s);
    GiveValue(v[n + 1], s);
    for(i = 1; i <= n; i++)
    {
        scanf("%s",s);
        GiveValue(v[i], s);
    }
    n++;
    for(i = n; i >= 1; i--)
    {
        Difference(v[i], v[i - 1]);
        Equality(vmax[i], v[i]);
        scanduri[i] = 1;
        //PrintNum(vmax[i]);
    }
    for(i = 1; i <= n; i++)
        myheap.push(i);
    for(i = 1; i <= t; i++)
    {
        //printf("La pasul %d\n",i);
        best = myheap.top();
        myheap.pop();
        scanduri[best]++;
        Divizion(best);
      //  printf("Bestul este %d %d\n",best,scanduri[best]);
      //  PrintNum(v[best]);
       // PrintNum(vmax[best]);
        myheap.push(best);
    }
    best = myheap.top();

    PrintNum(vmax[best]);

    return 0;
}




