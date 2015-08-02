var nr:int64;
    a:array[1..18] of integer;
    i,j:integer;

begin
writeln('Scrie numarul dorit!');
readln(nr);

for i:=18 downto 1 do
begin
a[i] := nr mod 10 ;
nr := nr div 10;
if nr=0 then
begin
j := i;
break;
end;
end;

for i:= j to 18 do
begin
write(a[i]);
write(' ');
end;












read(a[7]);
end.
