var a:array[1..16] of byte ;
    i,nr:integer;


begin

write('Scrie numarul pe care doresti sa-l transformi in baza 2 ');
readln(nr);

for i := 16 downto 1 do
begin
a[i] := nr mod 2;
nr := nr div 2;
end;
for i := 1 to 4 do
begin
write(a[4*i-3],a[4*i-2],a[4*i-1],a[4*i]);
write(' ');
end;


read(i);
end.