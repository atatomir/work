program martisoare;
var f,g:text;
   n,i,s:longint;
   a,c:array[1..100] of longint;
begin
assign(f,'martisoare.in');
assign(g,'martisoare.out');
reset(f);
rewrite(g);
readln(f,n);
for i:=1 to n do
begin
read(f,c[i]);
a[i]:=c[i];
end;
s:=1;
for i:=2 to n do
if c[i-1]+1<>c[i] then
s:=0;
if s=1 then
begin
writeln(g,'0',' ','0');
writeln(g,c[n]);
end;
close(f);
close(g);
end.