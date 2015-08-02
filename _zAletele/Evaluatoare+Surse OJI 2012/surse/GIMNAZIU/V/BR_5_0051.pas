program bete;
var f,g:text;
    n,u,max,max2,l,nr2,t,o,l1,i,y,j,nr,nr1:longint;
    s,a,b,max1:array [1..100000] of longint;
begin
assign(f,'bete.in');
assign(g,'bete.out');
reset(f);
rewrite(g);
readln(f,n);
for i:=1 to n do
     read(f,a[i]);
for i:=1 to n do
read(f,b[i]);
for i:=1 to n do
begin
o:=i*n;
    for j:=1 to n do
    begin
    y:=y+1;
    s[y]:=a[i]+b[j];
    end;
for t:=1 to o do
if max<=s[t] then
begin
max:=s[t];
max1[t]:=max;
nr:=nr+1;
end;
end;
for i:=1 to nr*nr do

if max=max1[i] then
nr2:=nr2+1;
for i:=1 to n do
   for j:=1 to n do
   if s[i]=s[j] then
   if s[i]>max2 then
   max2:=s[i];
writeln(g,max2);
writeln(g,max);
writeln(g,nr2);
close(f); close(g);
end.