program bete;
var a,b:array[1..100] of longint;
    f,g:text;
    k,p,n,x,j,i,l,s,s1:longint;
begin
assign(f,'bete.in');
assign(g,'bete.out');
reset(f);
rewrite(g);
readln(f,n);
for i:=1 to n do
  begin
   read(f,a[i]);
   read(f,b[i]);
  end;
  for i:=1 to n do
    begin
     s:=s+a[i];
     s1:=s1+b[i];
     l:=(s+s1) div n;
    end;
for i:=1 to n-1 do
for j:=2 to n do
if a[j]>a[i] then
                begin
                 x:=a[i];
                 a[i]:=a[j];
                 a[j]:=x;
                end;
x:=0;
for i:=1 to n-1 do
for j:=i+2 to n do
 if b[j]>b[i] then
                begin
                 x:=b[i];
                 b[i]:=b[j];
                 b[j]:=x;
                end;
for i:=1 to n do
 if a[i]+b[i]>k then
                k:=a[i]+b[i];
for i:=1 to n do
if k=a[i]+b[i] then
                p:=p+1;
writeln(g,l);
writeln(g,k);
writeln(g,p);
close(f);
close(g);
end.
