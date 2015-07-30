#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define maxS (2*1024*1024+3)

struct Node{
    Node *lSon,*rSon;
    int cnt;

    Node(){
        lSon=rSon=NULL;
        cnt = 0;
    }
    Node* goTo(char c){
        if(c=='0'){
            if(lSon==NULL) lSon = new Node();
            return lSon;
        } else {
            if(rSon==NULL) rSon = new Node();
            return rSon;
        }
    }
};

int a,b,fr,n,i,j;
char s[maxS];
Node *R,*act;
set<int> S;

short pre[maxS];
int ans[25];
vector<string> sol[25];
string wh;

void search(Node* R,int lvl){
    if(lvl>=a){
        int cnt = R->cnt;
        if( S.count(cnt) == 0 ){
            S.insert(cnt);
            if(S.size() > fr)S.erase(S.begin());
        }
    }

    if(lvl==b) return;
    if(R->lSon != NULL) search(R->lSon,lvl+1);
    if(R->rSon != NULL) search(R->rSon,lvl+1);
}

void SearchAndDrop(Node* R,int lvl){
    if(lvl>=a){
        if(pre[ R->cnt ]!=0){
            sol[ pre[ R->cnt ] ].push_back(wh);
        }
    }

    if(lvl==b) return;
    wh.push_back('1');
    if(R->rSon != NULL) SearchAndDrop(R->rSon,lvl+1);
    wh.erase( wh.size()-1,1 );
    wh.push_back('0');
    if(R->lSon != NULL) SearchAndDrop(R->lSon,lvl+1);
    wh.erase( wh.size()-1,1 );
}

bool better(const string& a,const string& b){
    for(int i=0;i<a.size();i++){
        if(a[i]!=b[i]) return (a[i]=='1');
    }
}
bool cmp(const string& a,const string& b){
    if(a.size()>b.size()) return true;
    if(a.size()<b.size()) return false;

    return better(a,b);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    scanf("%d%d%d\n%s",&a,&b,&fr,s+1);
    R = new Node();

    for(i=1;s[i]!='2';i++){
        act = R;
        for(j=1;j<=b && s[i+j-1]!='2';j++){
            act = act->goTo(s[i+j-1]);
            act->cnt++;
        }
    }

    S.clear();
    if(R->lSon!=NULL)search(R->lSon,1);
    if(R->rSon!=NULL)search(R->rSon,1);

    int how = S.size();
    for(set<int>::iterator it = S.begin();it!=S.end();it++){
        pre[*it] = how;
        ans[how--] = *it;
    }
    how = S.size(); S.clear();

    wh = "1";
    if(R->rSon!=NULL)SearchAndDrop(R->rSon,1);
    wh = "0";
    if(R->lSon!=NULL)SearchAndDrop(R->lSon,1);


    for(i=1;i<=how;i++){
        sort(sol[i].begin(),sol[i].end(),cmp);
        printf("%d ",ans[i]);
        for(j=0;j<sol[i].size();j++)
            printf("%s ",sol[i][j].c_str());
        printf("\n");
    }

    return 0;
}

