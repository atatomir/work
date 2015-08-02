program munte;
var f,g:text;
    a:array[1..1000]of longint;
    n,i,c,b:longint;
begin
assign(f,'munte.in');
assign(g,'munte.out');
reset(f);
rewrite(g);
readln(f,n);
for i:=1 to n do
read(f,a[i]);
for i:=1 to n do
if i<>n-1 then
if i>1 then
        if (a[i+1]>a[i])and(a[i+2]<a[i+1]) then
            begin
            c:=c+1;
            if (a[i]>a[i-1])and(a[i]>a[i+2]) then
            b:=b+1;
            end;
writeln(g,c);
writeln(g,b+c);
close(f);
close(g);
end.