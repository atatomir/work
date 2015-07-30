#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxL 50001
#define gogo 60

struct Node{
    Node *aa,*bb;
    int vaj;

    Node(){
        aa = bb = NULL;
        vaj = 0;
    }
    Node* goTo(char c){
        if(c=='a'){
            if(aa==NULL) aa = new Node();
            return aa;
        }else{
            if(bb==NULL) bb = new Node();
            return bb;
        }
    }
};

int n,i,j,l,defi,src;
Node *R,*act;
char s[maxL];
int ans;

void srcRez(Node* &act,int lvl){
    if(act->vaj == src) ans = max(ans,lvl);
    if(act->aa != NULL) srcRez(act->aa,lvl+1);
    if(act->bb != NULL) srcRez(act->bb,lvl+1);
}

int main()
{
    freopen("subsecvente2.in","r",stdin);
    freopen("subsecvente2.out","w",stdout);

    R = new Node();
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        memset(s,0,sizeof(s));
        scanf("%s",s+1); l = strlen(s+1);
        defi = 1<<i;
        src |= defi;

        for(j=1;j<=l;j++){
            act = R;
            int lim = min(l,j+gogo-1);
            for(int wh=j;wh<=lim;wh++){
                act = act->goTo(s[wh]);
                if(i>1&& act->vaj == 0) break;
                act->vaj |= defi;
            }
        }
    }

    srcRez(R,0);
    printf("%d",ans);

    return 0;
}
