/* Se citesc datele, se memoreaza pentru fiecare culoare pozitia (indicele)
   pe care apare prima data si ultima data. Cautam apoi culoarea pentru care
   diferenta dintre prima si ultima aparitie este maxima. In acest fel e
   suficienta o singura parcurgere a sirului (doua "for"-uri pentru un sir
   de 10000 numere inseamna timp de executie prea mare). In plus, nu e nevoie
   nici de memorarea numerelor din sir. Desigur, exista si alte metode de 
   optimizare a cautarii, aproape la fel de eficiente */
   
#include <stdio.h>
#define MAX_C 201
void main()
{FILE *f;
 int n,c,i,k,max=0,cmax,prim[MAX_C],ultim[MAX_C];
f=fopen("PANGLICA.IN","r");
fscanf(f,"%d %d",&n,&c);
for(i=1;i<=c;i++) prim[i]=0;
for(i=1;i<=n;i++) {
   fscanf(f,"%d",&k);
   if(prim[k]==0) prim[k]=i;
   ultim[k]=i; }
for(i=1;i<=c;i++)
  if(ultim[i]-prim[i]+1>max) {
    max=ultim[i]-prim[i]+1; cmax=i; }
f=fopen("PANGLICA.OUT","w");
fprintf(f,"%d\n%d\n%d\n%d\n",max,cmax,prim[cmax]-1,n-ultim[cmax]);
fclose(f); }
 
/*  Varianta Pascal :
program p71;
const MAX_C=201;
var n,c,i,k,max,cmax:integer; 
    prim,ultim:array[1..MAX_C] of integer;
    f:text;
begin
assign(f,'PANGLICA.IN'); reset(f);
readln(f,n,c);
for i:=1 to c do prim[i]:=0; max:=0;
for i:=1 to n do begin
   readln(f,k);
   if prim[k]=0 then prim[k]:=i;
   ultim[k]:=i  end;
close(f);
for i:=1 to c do
  if ultim[i]-prim[i]+1 > max then begin
      max:=ultim[i]-prim[i]+1; cmax:=i end;
assign(f,'PANGLICA.OUT'); rewrite(f);
writeln(f,max);writeln(f,cmax);writeln(f,prim[cmax]-1);writeln(f,n-ultim[cmax]);
close(f) end.      */