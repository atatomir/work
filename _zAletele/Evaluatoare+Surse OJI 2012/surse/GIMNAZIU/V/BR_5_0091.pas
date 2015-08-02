program bete;
var f,g:text;
    a,b:array[1..10000]of longint;
    n,i,min,l,k,p,max1,max2,s:longint
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
min:=10;
for i:=1 to n do
    if min>a[i] then
       min:=a[i];
max1:=0;
for i:=1 to n do
    if max1<b[i] then
       max1:=b[i];
l:=min+max1;
max2:=0;
for i:=1 to n do
    if max2<a[i];
        max2:=a[i];
k:=max1+max2;
for i:=1 to n do
        begin
        s:=a[i]+b[i];
        a[i]:=a[i+1];
        if s=k then
                 p:=p+1;
        end;
writeln(g,l);
writeln(g,k);
writeln(g,p);
close(f);
close(g);
end.