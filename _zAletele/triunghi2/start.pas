var  f,fo:text;
     ln,lv:array[1..50] of integer;
     n,pos,i,j:byte;
     gasit:boolean;

begin

assign(f,'file.bin'); reset(f);
assign(fo,'fout.bin'); rewrite(fo);

readln(f,n);
read(f,pos);
readln(f,lv[pos]);
writeln(fo,' (',lv[pos],') ');

for i := 2 to n do
begin

for j := 1 to n do
begin
ln[j] := -1;
end;

read(f,pos);
readln(f,ln[pos]);



for j := pos+1 to i do
ln[j] := lv[j-1]-ln[j-1];

for j := pos-1 downto 1 do
ln[j]:= lv[j] - ln[j+1];



for j := 1 to i do
begin
write(fo,' (',ln[j],') ');
lv[j]:= ln[j];


end;

writeln(fo,' ');



end;















close(f);
close(fo);
end.
