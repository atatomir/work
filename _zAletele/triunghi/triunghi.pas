var a,b:array[1..100] of integer ;
    ii,i,n,p:integer;
    f:text;

begin
assign(f,'file.bin');
reset(f);

readln(f,n);
p:=n;

for i:= 1 to n do
 begin
 read(f,a[i]);
 write(a[i]);
 write(' ');
 end;

 writeln();

for ii:= 1 to p-1  do
begin

 for i := 1 to n-1 do
 begin
 b[i] := a[i] + a[i+1];
 write(b[i]);
 write(' ');
 a[i] := b[i];
 end;
 n:= n-1;
 writeln();

end;







 read(i);
 close(f)
end.
