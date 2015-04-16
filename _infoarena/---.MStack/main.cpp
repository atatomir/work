#include <iostream>
#include <cstdio>

using namespace std;

#define maxS 10

long n,i;
char s[maxS];
long cnt,s1,s2,s3;

void reEchil(){
    long i,tot=s2+s3,how=tot/2;
    if(s2){
        for(i=1;i<=how;i++) printf("move 2 1\n");
        for(i=how+1;i<=tot;i++) printf("move 2 3\n");
        for(i=1;i<=how;i++) printf("move 1 2\n");

        s2 = how; s3 = tot-how;
    } else {
        for(i=1;i<=how;i++) printf("move 3 1\n");
        for(i=how+1;i<=tot;i++) printf("move 3 2\n");
        for(i=1;i<=how;i++) printf("move 1 3\n");

        s3 = how; s2 = tot-how;
    }
}

void getTop(){
    if(s3==0 && s2==1) {printf("top 2\n"); return;}
    if(s3==0) reEchil();
    printf("top 3\n");
}
void getMid(){
    if(s2==0 && s3==1) {printf("top 3\n"); return;}
    if(s2==0) reEchil();
    printf("top 2\n");
}
void pushNow(){
    s3 ++; cnt++; printf("push 3\n");
    if(s1 < cnt/2){
        if(s2==0) reEchil();
        printf("move 2 1\n"); s1++; s2--;
    }
}
void popNow(){
    cnt--;
    if(s1 > cnt/2) {printf("move 1 2\n"); s1--; s2++;}
    if(s2==1&&s3==0){printf("pop 2\n");s2--;return;}
    if(s3==0) reEchil();
    printf("pop 3\n"); s3--;
}

int main()
{
    freopen("mstack.in","r",stdin);
    freopen("mstack.out","w",stdout);

    for(scanf("%ld\n",&n);n;n--){
        scanf("%s\n",s+1);
        if(s[1] == 't') getTop(); else
        if(s[1] == 'm') getMid(); else
        if(s[2] == 'u') pushNow(); else
                        popNow();
    }


    return 0;
}
