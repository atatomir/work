#include <iostream>
#include <fstream>
using namespace std;
int numere[5000];
int main()
{
    int x,n,k,i,j,nc,dc,sp;
    int max=0;
    int d=0;
    int td=0;
    int daf=0;
    int tr=0;
    ifstream in("cool.in");
    ofstream out("cool.out");
    in>>x;
    in>>n;
    in>>k;
    k-=1;
    n-=1;
    for(i=0;i<=n;i++){
    in>>numere[i];
    }
    if(x==1){
    for(i=0;i<=k;i++){
    if(numere[i]>max){
    max=numere[i];
    }
    for(j=1;j<=k;j++){
    if(j==k&&i==k){
    dc=1;
    goto cool;
    }
    if(numere[i]==numere[j]&&i!=j){
    nc=1;
    goto noncool;
    }
    }
    }
    cool:
    noncool:
    if(nc==1){
    for(i=0;i<=k;i++){
    for(j=0;j<=k;j++){
    if(numere[i]==numere[j]&&i!=j){
    d=1;
    }
    if(j==k){
    if(d==0){
    td+=1;
    }
    d=0;
    }
    }
    }
    out<<td;
    }
    if(dc==1){
    out<<max;
    }
    }
    else {
    for(i=0;i<=n;i++){
    if(max<d){
    daf=0;
    max=d;
    }
    if(max==d){
    daf+=1;
    }
    for(j=i;j<=n;j++){
    for(sp=i;sp<=j;sp++){
    if(numere[sp]==numere[j]&&sp!=j){
    d=j-i;
    tr=1;
    }
    if(tr==1){
    break;
    }
    }
    if(tr==1){
    tr=0;
    break;
    }
    }
    }
    out<<max;
    out<<"\n";
    out<<daf;
    }
    return 0;
}
