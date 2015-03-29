#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxWord 20011
#define maxS 2110
#define maxDWord 23

char s[maxS];
long i,n;
char w[maxWord][maxDWord];
long len[maxWord];

long prov[maxWord];
long cnt[maxWord];
long ant['z'+5];
char c;

long Ans,pAns;
vector<long> ww;

bool isLetter(char c){
    return 'a'<=c&&c<='z';
}

int main()
{
    freopen("text3.in","r",stdin);
    freopen("text3.out","w",stdout);

    gets(s+1);
    while(!feof(stdin)){
        if(s[1]=='\0') {
            gets(s+1);
            continue;
        }
        i = 1;
        while(s[i]!='\0'){
            while(s[i]==' ') s[i++]='\0';
            if(s[i]=='\0') continue;
            n++;
            while(isLetter(s[i])){
                w[n][++len[n]] = s[i];
                s[i++] = '\0';
            }
            while(s[i]==' ') s[i++]='\0';
        }
        gets(s+1);
    }

    for(i=1;i<=n;i++){
        c = w[i][1];
        prov[i] = ant[c];
        cnt[i] = cnt[ant[c]]+1;

        if(cnt[i]>cnt[ant[w[i][len[i]]]])
            ant[w[i][len[i]]] = i;

        if(cnt[i] > Ans){
            Ans = cnt[i];
            pAns = i;
        }
    }

    while(pAns!=0){
        ww.push_back(pAns);
        pAns = prov[pAns];
    }

    printf("%ld\n%ld\n",n,n-ww.size());
    for(i=ww.size()-1;i>=0;i--){
        printf("%s\n",w[ww[i]]+1);
    }

    return 0;
}
