#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>
#include <cstring>

using namespace std;

#define maxS 10

long n,i,j,pos;
char s[maxS];
vector<int> chars;
vector<long> wrong;

bitset<8> B;

int main()
{
    freopen("paritate.in","r",stdin);
    freopen("paritate.out","w",stdout);

    memset(s,0,sizeof(s));
    fread(s+1,1,8,stdin);

    for(pos=0;s[1]=='0'||s[1]=='1';pos++){
        if(pos==958){
            pos++; pos--;
        }

        for(j=0;j<8;j++){
            B[j] = s[1+j]-'0';
        }

        long ans = 0;
        for(j=1;j<8;j++) {
            ans = (ans<<1)|B[j];
            B[0] = B[0]^B[j];
        }

        if(B[0]==1 || (ans<32&&ans!=10) || (ans>127&&ans!=10)){
            wrong.push_back(pos);
        } else
        if(ans==10){
            chars.push_back(10);
        } else
            chars.push_back(ans);


        memset(s,0,sizeof(s));
        fread(s+1,1,8,stdin);
    }

    if(wrong.size()){
        printf("NU\n");
        for(i=0;i<wrong.size();i++) printf("%ld ",wrong[i]);
    } else {
        printf("DA\n");
        for(i=0;i<chars.size();i++){
            printf("%c",chars[i]);
        }
    }

    return 0;
}
