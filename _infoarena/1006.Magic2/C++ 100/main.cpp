#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 10010

long n,i,j,x;
long a[maxN][maxN],l[maxN],c[maxN];
vector<long> line,column;
long cont,val;

vector<pair<long,pair<long,long> > > ans;
pair<long,pair<long,long> >  tmp;

int main()
{
    freopen("magic2.in","r",stdin);
    freopen("magic2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            scanf("%ld",&a[i][j]);
            l[i] += a[i][j];
            c[j] += a[i][j];
        }
    }

    cont = 1; val = l[1];
    for(i=2;i<=n;i++){
        if(cont == 0) val = l[i];
        if(val == l[i]) cont++; else cont--;
    }
    for(i=1;i<=n;i++){
        if(cont == 0) val = c[i];
        if(val == c[i]) cont++; else cont--;
    }

    for(i=1;i<=n;i++){
        if(l[i] != val) line.push_back(i);
        if(c[i] != val) column.push_back(i);
    }

    if(line.size() == column.size() && line.size() == 0){
        printf("magic\n");
        return 0;
    }

    printf("nu este magic\n");
    if(line.size() == 1){
       ans.push_back(make_pair(a[line[0]][column[0]] + val - c[column[0]],make_pair(line[0],column[0])));
       ans.push_back(make_pair(a[line[0]][column[1]] + val - c[column[1]],make_pair(line[0],column[1])));
    } else {
        if(column.size() == 1) column.push_back(column[0]);

        if(l[line[1]] != c[column[1]]) {long t=line[0];line[0]=line[1];line[1]=t;}

        ans.push_back(make_pair(a[line[0]][column[0]] + val - l[line[0]],make_pair(line[0],column[0])));
        ans.push_back(make_pair(a[line[1]][column[1]] + val - l[line[1]],make_pair(line[1],column[1])));
    }

    if(ans[0].second.first > ans[1].second.first ||
       (ans[0].second.first == ans[1].second.first && ans[0].second.second > ans[1].second.second)){
            tmp = ans[0]; ans[0] = ans[1]; ans[1] = tmp;
       }

    printf("%ld %ld %ld %ld\n%ld %ld\n",ans[0].second.first,ans[0].second.second,ans[1].second.first,ans[1].second.second,ans[0].first,ans[1].first);

    return 0;
}
