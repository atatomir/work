var f:text;
    corect:boolean;
    x,n,z,i:integer;
    a:array[1..100] of integer;

begin
assign(f,'file.bin');
reset(f);
readln(f,n);
for i:= 1 to n do
begin
read(f,a[i]);
write(a[i]);
write(' ');
end;
writeln();
read(f,z);

repeat
corect:= false;
for i:=  1 to n-1  do
begin
if a[i]> a[i+1] then
begin
corect :=  true;
x := a[i+1];
a[i+1] := a[i];
a[i] := x;
end;
end;

until corect = false;

if z < a[1] then
write( 'z < cel mai mic numar din sir')
else
if z > a[n] then
write('z > cel mai mare numar din sir')
else
begin
write('apartine sirului');

for i:= 1 to n do
begin

if a[i] > z then
begin
write('z se afla intre ');
write(a[i-1]);
write(' si ');
write(a[i]);
break;
end;
end;
end;









read(z);
end.
