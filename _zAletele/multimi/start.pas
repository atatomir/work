var n,a,b,amax,bmin,i:integer;
    f:text;

begin

assign(f,'file.bin');
reset(f);

readln(f,n);
read(f,a);    readln(f,b);
amax:= a ;    bmin := b;

for i:=2 to n do
begin
read(f,a);  readln(f,b);
if a > amax then
amax:= a;
if b < bmin then
bmin := b ;
end;


write('Multimea contine elementul/ele : ');


if amax > bmin then
write('Multimea nu are niciun element!')
else
begin
for i := amax to bmin do
begin
write(i);
write(' ');
end;



end;





read(i);
close(f);
end.
