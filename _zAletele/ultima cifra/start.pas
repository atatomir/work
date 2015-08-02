var n:byte;
    f:text;
    i,s,ii:integer;
    ui,up:integer;

begin
s:= 0;
assign(f,'file.bin');
reset(f);

read(f,n);

for i:=1 to n do
begin
ui := i mod 10;
up:=1;
for ii:= 1 to i do
begin
up:=( up * ui) mod 10;


end;
s := (s + up) mod 10;
end;

write('Ultima cifra a sumei este:');
write(s);




close(f);
read(up);
end.

