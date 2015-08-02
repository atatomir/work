#include<stdio.h>
#include<string.h>
int lung,k,n,i,l[5],min,poz,nr,j;
char s[5][50001],sir[70],x[1];
int main()
{
    freopen("subsecvente.in","r",stdin);
    freopen("subsecvente.out","w",stdout);
    scanf("%d",&n);
    min=1000;
    gets(x);
    for(i=0;i<n;i++)
    {
        gets(s[i]);
        l[i]=strlen(s[i]);
        if(l[i]<min)
        {
            min=l[i];
            poz=i;
        }
    }
    k=1;
    if(min<60)
        lung=min;
    else
        lung=60;
    while(k)
    {
        for(i=0;i<=min-lung && k;i++)
        {
            for(j=0;j<lung;j++)
                sir[j]=s[poz][i+j];
            k=0;
            sir[j]=NULL;
            for(j=0;j<n && k==0;j++)
                if(strstr(s[j],sir)==0)
                    k=1;
        }
        lung--;
    }
    lung++;
    printf("%d",lung);
    return 0;
}
