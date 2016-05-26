#include <fstream>
#include <vector>
#include <utility>
#define MOD 44449
using namespace std;
ifstream f("labirint.in");
ofstream g("labirint.out");
void gen_stare(int,int,int),rez_stare(int),F0(int),F1(int),
F22(int),F202(int),F2002(int),F2332(int),F2233(int),Fill(int,int),
finalizare();
int n,U[10][10],D[10][10],L[10][10],R[10][10],viz[10][10],x[10],
d,corect,S1,S2,Enc[200000],Dec[150],M[2][150][150],sol[2][150];
vector<pair<int,int> > Per;
int main()
{
    f>>n;
    gen_stare(1,0,0);
    finalizare();
    return 0;
}
void linia3(int j)
{
    int i,k,zi,zk;
    if(j==7)
    {
        if(R[3][6])return;
        for(i=0;i<=4;i++)
            for(k=0;k<=7;k++)
                viz[i][k]=0;
        d=0;corect=1;
        for(i=1;i<=6;i++)
            if(!viz[3][i])
            {
                d++;Fill(3,i);
            }
        if(!corect)return;
        int cicli=2,S2=0;
        for(k=0;k<6;k++)x[k]=-viz[4][k+1];
        for(k=0,zk=100000;k<6;k++,zk/=10)
        {
            if(x[k]>=0)continue;
            for(i=k+1,zi=zk/10;i<6;i++,zi/=10)
                if(x[i]==x[k])
                    break;
            if(i==6){S2+=zk;continue;}
            x[k]=-x[k];x[i]=-x[i];
            S2+=cicli*(zk+zi);cicli++;
        }
        Enc[S1]=1;
        Enc[S2]=1;
        Per.push_back(make_pair(S1,S2));
        return;
    }
    L[3][j]=R[3][j-1];
    U[3][j]=D[2][j];
    if(L[3][j]+U[3][j]==2){D[3][j]=R[3][j]=0;linia3(j+1);return;}
    if(L[3][j]+U[3][j]==0){D[3][j]=R[3][j]=1;linia3(j+1);return;}
    D[3][j]=1;R[3][j]=0;linia3(j+1);
    D[3][j]=0;R[3][j]=1;linia3(j+1);
}
void gen_stare(int j,int c,int cod)
{
    if(j==7)
    {
        S1=cod;
        linia3(1);
        return;
    }
    if(j==1)
    {
        F0(1);gen_stare(j+1,0,cod+0);
        F1(1);gen_stare(j+1,0,cod+100000);
    }
    if(j==2)
    {
        F0(2);gen_stare(3,0,cod);
        F1(2);gen_stare(3,0,cod+10000);
        F2002(2);gen_stare(6,1,cod+20020);
        F2332(2);gen_stare(6,1,cod+23320);
        F202(2);gen_stare(5,1,cod+20200);
        F22(2);gen_stare(4,1,cod+22000);
    }
    if(j==3)
    {
        F0(3);gen_stare(4,c,cod);
        F1(3);gen_stare(4,c,cod+1000);
        F22(3);gen_stare(5,1,cod+2200);
        F202(3);gen_stare(6,1,cod+2020);

    }
    if(j==4)
    {
        F0(4);gen_stare(5,c,cod);
        F1(4);gen_stare(5,c,cod+100);
        F22(4);
        if(c==0)gen_stare(6,1,cod+220);
        else gen_stare(6,1,cod+330);
    }
    if(j==5)
    {
        F0(5);gen_stare(6,c,cod);
        F1(5);gen_stare(6,c,cod+10);
    }
    if(j==6)
    {
        F0(6);gen_stare(7,c,cod);
        F1(6);gen_stare(7,c,cod+1);
    }
}
void F0(int j)
{
    for(int i=0;i<=2;i++)
        L[i][j]=R[i][j]=D[i][j]=U[i][j]=1;
}
void F1(int j)
{
    F0(j);
    D[0][j]=0;
    D[1][j]=U[1][j]=0;
    D[2][j]=U[2][j]=0;
}
void F22(int j)
{
    F0(j);F0(j+1);
    D[2][j]=D[2][j+1]=0;
    R[2][j]=L[2][j+1]=0;
}
void F202(int j)
{
    F0(j);F0(j+1);F0(j+2);
    D[2][j]=D[2][j+2]=0;
    R[2][j]=L[2][j+1]=0;
    R[2][j+1]=L[2][j+2]=0;
}
void F2002(int j)
{
    F0(2);F0(3);F0(4);F0(5);
    D[2][2]=D[2][5]=0;
    R[2][2]=R[2][3]=R[2][4]=0;
    L[2][3]=L[2][4]=L[2][5]=0;
}
void F2332(int j)
{
    F0(2);F0(3);F0(4);F0(5);
    D[2][2]=U[2][2]=0;
    D[1][2]=R[1][2]=0;
    L[1][3]=R[1][3]=0;
    L[1][4]=R[1][4]=0;
    L[1][5]=D[1][5]=0;
    D[2][5]=U[2][5]=0;
    D[2][3]=R[2][3]=0;
    L[2][4]=D[2][4]=0;
}
void Fill(int i,int j)
{
    viz[i][j]=d;
    if(i==0||i==4||j==0||j==7)return;
    if(L[i][j]&&R[i][j])
    {
        if(viz[i-1][j]&&viz[i+1][j]){corect=0;return;}
        if(viz[i-1][j]){Fill(i+1,j);return;}
        if(viz[i+1][j]){Fill(i-1,j);return;}
        Fill(i-1,j);Fill(i+1,j);return;
    }
    if(D[i][j]&&U[i][j])//go LR
    {
        if(viz[i][j-1]&&viz[i][j+1]){corect=0;return;}
        if(viz[i][j-1]){Fill(i,j+1);return;}
        if(viz[i][j+1]){Fill(i,j-1);return;}
        Fill(i,j+1);Fill(i,j-1);
        return;
    }
    if(D[i][j]&&L[i][j])//go UR
    {
        if(viz[i-1][j]&&viz[i][j+1]){corect=0;return;}
        if(viz[i-1][j]){Fill(i,j+1);return;}
        if(viz[i][j+1]){Fill(i-1,j);return;}
        Fill(i-1,j);Fill(i,j+1);return;
    }
    if(D[i][j]&&R[i][j])//go UL
    {
        if(viz[i-1][j]&&viz[i][j-1]){corect=0;return;}
        if(viz[i-1][j]){Fill(i,j-1);return;}
        if(viz[i][j-1]){Fill(i-1,j);return;}
        Fill(i-1,j);Fill(i,j-1);return;
    }
    if(U[i][j]&&L[i][j])//go UR
    {
        if(viz[i+1][j]&&viz[i][j+1]){corect=0;return;}
        if(viz[i+1][j]){Fill(i,j+1);return;}
        if(viz[i][j+1]){Fill(i+1,j);return;}
        Fill(i+1,j);Fill(i,j+1);return;
    }
    if(U[i][j]&&R[i][j])//go UL
    {
        if(viz[i+1][j]&&viz[i][j-1]){corect=0;return;}
        if(viz[i+1][j]){Fill(i,j-1);return;}
        if(viz[i][j-1]){Fill(i+1,j);return;}
        Fill(i+1,j);Fill(i,j-1);return;
    }
}
void finalizare()
{
    int i,j,k,a,b,A,B,Sol;
    d=1;
    for(i=0;i<=123321;i++)
        if(Enc[i])
        {
            Dec[d]=i;
            Enc[i]=d++;

        }
    for(auto it:Per)
        M[0][Enc[it.second]][Enc[it.first]]++;
    sol[0][Enc[111111]]=1;
    a=0;b=1;A=0;B=1;
    for(;n;n>>=1)
    {
        if(n&1)
        {
            for(i=1;i<=140;i++)
            {
                sol[B][i]=0;
                for(k=1;k<=140;k++)
                    sol[B][i]=(sol[B][i]+M[a][i][k]*sol[A][k])%MOD;
            }
            A=1-A;B=1-B;
        }
        for(i=1;i<=140;i++)
            for(j=1;j<=140;j++)
            {
                M[b][i][j]=0;
                for(k=1;k<=140;k++)
                    M[b][i][j]=(M[b][i][j]+M[a][i][k]*M[a][k][j])%MOD;
            }
        a=1-a;b=1-b;
    }
    Sol=0;
    for(i=1;i<=140;i++)
    {
        j=Dec[i];
        for(k=1;k<=6;k++,j/=10)
            if(j%10==0)
                break;
        if(k==7)
            Sol=(Sol+sol[A][i])%MOD;
    }
    g<<Sol;
}
