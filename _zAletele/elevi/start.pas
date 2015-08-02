type
om=record
nume:string[255];
varsta:integer;
end;
var f:text;
    i:integer;
    a:array[1..10] of om;
    x:om;
    corect:boolean;

begin

assign(f,'file.bin');
reset(f);

for i := 1 to 10 do
begin
readln(f,a[i].nume);
readln(f,a[i].varsta);
writeln(a[i].nume);
writeln(a[i].varsta);
end;

repeat
corect := false;
for i := 1 to 9 do
begin
if ( a[i].varsta > a[i+1].varsta) or ( ( a[i].varsta = a[i+1].varsta )  and ( a[i].nume > a[i+1].nume) ) then
begin
x := a[i];
a[i] := a[i+1];
a[i+1] := x;
corect := true;
end;


end;

until corect = false;
writeln('--------------------------');
for i := 1 to 10 do
begin
write(i);
write('. ');
write(a[i].nume);
write(' ');
writeln(a[i].varsta);
end;






writeln('--------------------------');
close(f);
read(i);
end.
