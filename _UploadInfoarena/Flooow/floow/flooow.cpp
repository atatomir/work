#include <fstream>
#include <algorithm>

using namespace std;

const char InFile[]="flooow.in";
const char OutFile[]="flooow.out";
const int MaxN=200005;
const int MaxL=200111;
const int MAX_AINT_SIZE=MaxL*4;

ifstream fin(InFile);
ofstream fout(OutFile);

struct AintNode
{
    bool updated;
    int leftMinInd;
    int rightMinInd;
    int leftMaxInd;
    int rightMaxInd;
    int leftMinSum;
    int rightMinSum;
    int leftMaxSum;
    int rightMaxSum;
    int minSum;
    int maxSum;
    int minSumLeftInd;
    int minSumRightInd;
    int maxSumLeftInd;
    int maxSumRightInd;
    int sum;
};

int N,K,L[MaxN],V[MaxL];
int offsetBegin[MaxL],offsetEnd[MaxL];
AintNode AINT[MAX_AINT_SIZE];

int AINT_index;
int AINT_left,AINT_right;

void _Propagate(int nod, int st, int dr)
{
    if(!AINT[nod].updated)
    {
        AINT[nod].sum=-AINT[nod].sum;

        swap(AINT[nod].minSum,AINT[nod].maxSum);
        AINT[nod].minSum=-AINT[nod].minSum;
        AINT[nod].maxSum=-AINT[nod].maxSum;
        swap(AINT[nod].minSumLeftInd,AINT[nod].maxSumLeftInd);
        swap(AINT[nod].minSumRightInd,AINT[nod].maxSumRightInd);

        swap(AINT[nod].leftMinSum, AINT[nod].leftMaxSum);
        AINT[nod].leftMinSum=-AINT[nod].leftMinSum;
        AINT[nod].leftMaxSum=-AINT[nod].leftMaxSum;
        swap(AINT[nod].leftMinInd,AINT[nod].leftMaxInd);

        swap(AINT[nod].rightMinSum, AINT[nod].rightMaxSum);
        AINT[nod].rightMinSum=-AINT[nod].rightMinSum;
        AINT[nod].rightMaxSum=-AINT[nod].rightMaxSum;
        swap(AINT[nod].rightMinInd,AINT[nod].rightMaxInd);

        if(st!=dr)
        {
            int l=nod<<1;
            int r=l+1;
            AINT[l].updated=!AINT[l].updated;
            AINT[r].updated=!AINT[r].updated;
        }
        AINT[nod].updated=true;
    }
}

void _UpdateNode(int nod, int st, int dr)
{
    int mid=((st+dr)>>1);
    int l=nod<<1;
    int r=l+1;

    _Propagate(l,st,mid);
    _Propagate(r,mid+1,dr);

    AINT[nod].sum=AINT[l].sum+AINT[r].sum;

    if(AINT[l].leftMinSum < AINT[l].sum+AINT[r].leftMinSum)
    {
        AINT[nod].leftMinSum=AINT[l].leftMinSum;
        AINT[nod].leftMinInd=AINT[l].leftMinInd;
    }
    else
    {
        AINT[nod].leftMinSum=AINT[l].sum+AINT[r].leftMinSum;
        AINT[nod].leftMinInd=AINT[r].leftMinInd;
    }

    if(AINT[l].leftMaxSum > AINT[l].sum+AINT[r].leftMaxSum)
    {
        AINT[nod].leftMaxSum=AINT[l].leftMaxSum;
        AINT[nod].leftMaxInd=AINT[l].leftMaxInd;
    }
    else
    {
        AINT[nod].leftMaxSum=AINT[l].sum+AINT[r].leftMaxSum;
        AINT[nod].leftMaxInd=AINT[r].leftMaxInd;
    }

    if(AINT[r].rightMinSum < AINT[r].sum+AINT[l].rightMinSum)
    {
        AINT[nod].rightMinSum=AINT[r].rightMinSum;
        AINT[nod].rightMinInd=AINT[r].rightMinInd;
    }
    else
    {
        AINT[nod].rightMinSum=AINT[r].sum+AINT[l].rightMinSum;
        AINT[nod].rightMinInd=AINT[l].rightMinInd;
    }

    if(AINT[r].rightMaxSum > AINT[r].sum+AINT[l].rightMaxSum)
    {
        AINT[nod].rightMaxSum=AINT[r].rightMaxSum;
        AINT[nod].rightMaxInd=AINT[r].rightMaxInd;
    }
    else
    {
        AINT[nod].rightMaxSum=AINT[r].sum+AINT[l].rightMaxSum;
        AINT[nod].rightMaxInd=AINT[l].rightMaxInd;
    }

    AINT[nod].minSum=AINT[l].rightMinSum+AINT[r].leftMinSum;
    AINT[nod].minSumLeftInd=AINT[l].rightMinInd;
    AINT[nod].minSumRightInd=AINT[r].leftMinInd;

    if(AINT[nod].minSum > AINT[l].minSum)
    {
        AINT[nod].minSum=AINT[l].minSum;
        AINT[nod].minSumLeftInd=AINT[l].minSumLeftInd;
        AINT[nod].minSumRightInd=AINT[l].minSumRightInd;
    }
    if(AINT[nod].minSum > AINT[r].minSum)
    {
        AINT[nod].minSum=AINT[r].minSum;
        AINT[nod].minSumLeftInd=AINT[r].minSumLeftInd;
        AINT[nod].minSumRightInd=AINT[r].minSumRightInd;
    }

    AINT[nod].maxSum=AINT[l].rightMaxSum+AINT[r].leftMaxSum;
    AINT[nod].maxSumLeftInd=AINT[l].rightMaxInd;
    AINT[nod].maxSumRightInd=AINT[r].leftMaxInd;

    if(AINT[nod].maxSum < AINT[l].maxSum)
    {
        AINT[nod].maxSum=AINT[l].maxSum;
        AINT[nod].maxSumLeftInd=AINT[l].maxSumLeftInd;
        AINT[nod].maxSumRightInd=AINT[l].maxSumRightInd;
    }
    if(AINT[nod].maxSum < AINT[r].maxSum)
    {
        AINT[nod].maxSum=AINT[r].maxSum;
        AINT[nod].maxSumLeftInd=AINT[r].maxSumLeftInd;
        AINT[nod].maxSumRightInd=AINT[r].maxSumRightInd;
    }
}

void _BuildAINT(int nod, int st, int dr)
{
    AINT[nod].updated=true;
    if(st==dr)
    {
        int val=V[offsetBegin[AINT_index]+st-1];

        AINT[nod].sum=val;
        AINT[nod].minSum=val;
        AINT[nod].minSumLeftInd=st;
        AINT[nod].minSumRightInd=st;
        AINT[nod].leftMinSum=val;
        AINT[nod].leftMinInd=st;
        AINT[nod].rightMinSum=val;
        AINT[nod].rightMinInd=st;
        AINT[nod].maxSum=val;
        AINT[nod].maxSumLeftInd=st;
        AINT[nod].maxSumRightInd=st;
        AINT[nod].leftMaxSum=val;
        AINT[nod].leftMaxInd=st;
        AINT[nod].rightMaxSum=val;
        AINT[nod].rightMaxInd=st;

        return;
    }

    int mid=((st+dr)>>1);
    int l=nod<<1;
    int r=l+1;

    _BuildAINT(l,st,mid);
    _BuildAINT(r,mid+1,dr);

    _UpdateNode(nod,st,dr);
}

void BuildAINT(int aint)
{
    AINT_index=aint;
    _BuildAINT(1,1,L[AINT_index]);
}

void QueryAINT(int &sum, int &left, int &right)
{
    _Propagate(1,1,L[AINT_index]);

    sum=AINT[1].maxSum;
    left=AINT[1].maxSumLeftInd;
    right=AINT[1].maxSumRightInd;
}

void _UpdateAINT(int nod, int st, int dr)
{
    if(AINT_left<=st && dr<=AINT_right)
    {
        AINT[nod].updated=!AINT[nod].updated;
        _Propagate(nod,st,dr);
        return;
    }

    _Propagate(nod,st,dr);

    int mid=((st+dr)>>1);
    int l=nod<<1;
    int r=l+1;

    if(AINT_left<=mid)
    {
        _UpdateAINT(l,st,mid);
    }
    if(mid<AINT_right)
    {
        _UpdateAINT(r,mid+1,dr);
    }

    _UpdateNode(nod,st,dr);
}

void UpdateAINT(int left, int right)
{
    AINT_left=left;
    AINT_right=right;

    _UpdateAINT(1,1,L[AINT_index]);
}

int main()
{
    fin>>N>>K;
    for(int i=1;i<=N;++i)
    {
        fin>>L[i];
        offsetBegin[i]=offsetEnd[i-1];
        offsetEnd[i]=offsetBegin[i]+L[i];
        for(int j=offsetBegin[i];j<offsetEnd[i];++j)
        {
            fin>>V[j];
        }
    }
    fin.close();

    int sol=0;

    for(int i=1;i<=N;++i)
    {
        if(L[i]==0)
        {
            continue;
        }
        BuildAINT(i);
        for(int j=1;j<=K;++j)
        {
            int left=-1,right=-1,maxSum=-1;
            QueryAINT(maxSum,left,right);
            if(maxSum<=0)
            {
                break;
            }
            sol+=maxSum;
            UpdateAINT(left,right);
        }
    }

    fout<<K<<" "<<sol<<"\n";
    fout.close();
    return 0;
}
