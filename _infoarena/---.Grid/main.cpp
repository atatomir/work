#include <iostream>
#include <cstdio>

using namespace std;

struct Node{
    long val;
    Node *next;

    Node(long vall){
        val = vall;
        next = NULL;
    }
};

long n,m,i,j,x1,y1,x2,y2;
Node *Head[3],*tmp[3],*curr;

Node* Elim(long x,long y){
    Node *tmp = Head[x],*ant = Head[x];
    if(y == 0){
        Head[x] = Head[x]->next;
        return tmp;
    }
    tmp = tmp->next;
    for(long i=1;i<y;i++){
        ant = tmp; tmp = tmp->next;
    }
    ant->next = tmp->next;
    return tmp;
}

void Adaug(long x,long y,Node* curr){
    Node *tmp = Head[x],*ant = Head[x];
    if(y==0){
        Head[x] = curr;
        curr->next = tmp;
        return;
    }

    tmp = tmp->next;
    for(long i=1;i<y;i++){
        ant = tmp; tmp = tmp->next;
    }
    ant->next = curr;
    curr->next = tmp;
}

int main()
{
    freopen("grid.in","r",stdin);
    freopen("grid.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    Head[0] = new Node(1);
    Head[1] = new Node(n+1);
    Head[2] = new Node(2*n+1);

    tmp[0] = Head[0];
    tmp[1] = Head[1];
    tmp[2] = Head[2];

    for(i=2;i<=n;i++){
        for(j=0;j<3;j++){
            tmp[j]->next = new Node(tmp[j]->val+1);
            tmp[j] = tmp[j]->next;
        }
    }

    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld %ld",&x1,&y1,&x2,&y2);
        curr = Elim(x1,y1);
        Adaug(x2,y2,curr);
    }

    for(i=0;i<3;i++){
        while(Head[i] != NULL){
            cout << Head[i]->val << ' ';
            Head[i] = Head[i]->next;
        }
        cout << '\n';
    }

    return 0;
}
