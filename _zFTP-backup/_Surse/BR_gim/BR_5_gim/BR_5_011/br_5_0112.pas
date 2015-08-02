program piramide;
var f,g:text;
    n,k,x,y,m,j,i,v,s,o:longint;
    c,a,p:array[1..100] of longint;
begin
assign(f,'piramide.in');
assign(g,'piramide.out');
reset(f);
rewrite(g);
readln(f,n,x,k);
for i:=1 to k do
read(f,c[i]);
y:=2;
a[1]:=3;
m:=3;
j:=1;
if n-m>6 then
begin
m:=9;
a[2]:=9;
y:=y+1;
j:=2;
end;
repeat
y:=y+1;
j:=j+1;
a[j]:=m+(a[j-1]-a[j-2])+y;
m:=a[j];
until n<m+(a[j-1]-a[j-2])+y;
if x<3 then
writeln(g,'1');
for i:=1 to j-1 do
if (x<a[i+1]) and (a[i]<x) then
writeln(g,i+1);
writeln(g,j);
writeln(g,n-m);
for i:=1 to k do
if c[i]<3 then
p[1]:=p[1]+1;
o:=1;
for i:=1 to j-1 do
begin
o:=o+1;
for v:=1 to k do
if (c[v]>a[i]) and (c[v]<a[i+1]) then
p[o]:=p[o]+1;
end;
for i:=1 to o do
begin
s:=1;
for v:=1 to o do
if p[i]<p[v] then
s:=0;
if s=1 then
begin
writeln(g,i);
p[i]:=k+1;
end;
end;
close(f);
close(g);
end.