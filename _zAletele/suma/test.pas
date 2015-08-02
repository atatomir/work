var a:integer;
    i:byte;
    b:array[1..10] of integer;
    s:integer;
    f:text;
    fout:text;
    gasit:boolean;
    y:integer;
    d:integer;
    sp:integer;
    si:integer;
    first:boolean;
begin
sp  := 0;
si  := 0;
assign(f,'t.bin');
reset(f);
assign(fout,'fout.bin');
rewrite(fout);
for i := 1 to 5 do
begin
read(f,b[i]);
write(fout,b[i]);
If i<> 5 then
write(fout,'+');
end;
close(f);
for i := 1 to 5 do
begin
S := S + b[i]
end;
write(fout,'=');
write(fout,s);
writeln(fout);
repeat
gasit := false;
for i := 1 to 4 do
begin
if b[i]>b[i+1] then
begin
gasit:= true;
y:= b[i];
b[i] := b[i+1];
b[i+1] := y;
end;
end;
until gasit=false;
d:= b[5];
for i:= 5 downto 1 do
begin
write(fout,b[i]);
if i<>1 then
write(fout,'-');
if i<>5 then
d := d - b[i];

end;

write(fout,'=');
write(fout,d);
writeln(fout,' ');
first:= false;

for i:= 1 to 5 do
begin
if b[i] mod 2 = 0 then
begin
if first=true then
write(fout,'+');
sp:= sp+ b[i];
first := true ;
write(fout,b[i]);
write(fout,' ');
end;
end;
write(fout,'=');
writeln(fout,sp);

first:= false;

for i:= 1 to 5 do
begin
if b[i] mod 2 = 1 then
begin
if first=true then
write(fout,'+');
first := true;
si:=si + b[i];
if first = true then
write(fout,b[i]);
write(fout,' ');
end;
end;
write(fout,'=');
writeln(fout,si);





close(fout);
end.
