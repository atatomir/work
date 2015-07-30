program imprimanta;
var f,g:text;
    n,k,max,min,c,s,a:longint;
begin
assign(f,'imprimanta.in');
assign(g,'imprimanta.out');
reset(f);
rewrite(g);
read(f,n,k);
max:=-1;
min:=1000;
while n<>0 do
begin
c:=n mod 10;
n:=n div 10;
if (c=0)or(c=6)or(c=9) then
a:=12;
if c=1 then
a:=5;
if (c=2)or(c=3)or(c=5) then
a:=11;
if c=4 then
a:=9;
if c=7 then
a:=7;
if c=8 then
a:=13;
if min>a then
min:=a;
if min=a then
begin
s:=c;
if max<s then
        max:=s;
end;
end;
writeln(g,max);
close(f);
close(g);
end.