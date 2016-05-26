#include <fstream>
#include <vector>
#define MOD 44449
using namespace std;
ifstream f("labirint.in");
ofstream g("labirint.out");
int n,sol,A[141],C[4097],viz[30],b,t,*p,*q,*a,sp[141],sq[141],x[30];
void P(int,int),D(int,int),B(int),S(int),doit();
vector<int> v[30],s[141];
int main()
{
    int i,j,k;
    for(i=1,j=1;i<=6;i++,j<<=2)A[1]+=j;
    C[A[1]]=1;P(7,8);P(13,14);
    for(b=1,t=1;b<=t;b++)S(A[b]);
    f>>n;
    p=sp;q=sq;p[1]=1;
    for(;n;n--)
    {
        for(i=1;i<=t;i++)
        {
            for(auto it:s[i])
                q[it]=q[it]+p[i]<MOD?q[it]+p[i]:q[it]+p[i]-MOD;
            p[i]=0;
        }

        a=p;p=q;q=a;
    }
    for(i=1;i<=t;i++)
    {
        for(j=1,k=A[i];j<=6;j++,k>>=2)if(!(k&3))break;
        if(j==7)sol=sol+p[i]<MOD?sol+p[i]:sol+p[i]-MOD;
    }
    g<<sol;
    return 0;
}
void S(int val)
{
    int i,j,i2,j2,i3,j3;
    for(i=15,j=0;i<=20;i++,j+=2)x[i]=(val>>j)&3;
    for(i=15;i<=20;i++){if(!x[i])continue;P(i,i-7);}
    for(i2=16;i2<=19;i2++)if(x[i2]==2)break;for(j2=19;j2>=16;j2--)if(x[j2]==2)break;if(i2<j2)P(i2,j2);
    for(i3=16;i3<=19;i3++)if(x[i3]==3)break;for(j3=19;j3>=16;j3--)if(x[j3]==3)break;if(i3<j3)P(i3,j3);
    B(8);
    if(i3<j3)D(i3,j3);if(i2<j2)D(i2,j2);
    for(i=15;i<=20;i++)if(x[i])D(i,i-7);
}
void B(int r)
{
    if(r==14){doit();return;}
    if(v[r].size()==3)return;//asta se poate la ultima camera daca am primit deja o
    if(v[r].size()==2){B(r+1);return;}
    if(v[r].size()==0){P(r,r+1);P(r,r-7);B(r+1);D(r,r-7);D(r,r+1);return;}
    P(r,r+1);B(r+1);D(r,r+1);
    P(r,r-7);B(r+1);D(r,r-7);
}
void P(int i,int j){v[i].push_back(j);v[j].push_back(i);}
void D(int i,int j){v[i].pop_back();v[j].pop_back();}
void doit()
{
    int i,j,k,aux,c[30],y[10],cnt=0;
    for(i=1;i<=20;i++)c[i]=0;
    for(i=1;i<=20;i++)
    {
        if(c[i])continue;
        if(v[i].size()==2)continue;
        if(v[i].size()==0){cnt++;continue;}
        j=i;k=v[j][0];cnt+=2;
        while(v[k].size()==2)
        {
            aux=v[k][0]+v[k][1]-j;
            j=k;k=aux;cnt++;
        }
        c[i]=k;
        c[k]=i;
    }
    if(cnt!=20)return;
    aux=2;
    for(i=1,k=2;i<=6;i++)
    {
        if(c[i]==0){y[i]=0;continue;}
        if(c[i]<i)continue;
        if(c[i]>6){y[i]=1;continue;}
        y[i]=y[c[i]]=k++;
    }
    for(i=6,k=0;i>=1;i--)k=4*k+y[i];
    if(!C[k]){t++;A[t]=k;C[k]=t;}
    s[b].push_back(C[k]);
}
