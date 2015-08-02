var n,m,i,x:integer;
    a:array [1..100] of integer;
    b:array [1..100] of integer;
    c:array [1..100] of integer;
    f:text;
    corect:boolean;
    out:text;
begin
assign(f,'file.bin');
reset(f);
assign(out,'out.bin');
rewrite(out);
readln(f,n);
for i:=1 to n do
read(f,a[i]);
repeat
corect := false;
for i:= 1 to n-1 do
 if a[i]>a[i+1] then
 begin
 corect := true;
 x := a[i];
 a[i]:= a[i+1];
 a[i+1] := x;
 end;
until corect = false;
for i:= 1 to n do
begin
write(out,a[i]);
if i <> n then
write(out,'<');
end;
writeln(out);


readln(f,m);
for i:=1 to m do
read(f,b[i]);
repeat
corect := false;
for i:= 1 to m-1 do
 if b[i]>b[i+1] then
 begin
 corect := true;
 x := b[i];
 b[i]:= b[i+1];
 b[i+1] := x;
 end;
until corect = false;
for i:= 1 to m do
begin
write(out,b[i]);
if i <> m then
write(out,'<');
end;
for i := 1 to m do
begin
c[i]:= b[i];
end;
for i := 1 to n do
begin
c[i] := a[i+ m];
end;
writeln(out);

repeat
corect:= false;
for i := 1 to m+n-1 do
begin
if c[i]>c[i+1] then
begin
corect := true;
x := c[i + 1] ;
c[i+1] := c[i];
c[i] := x;



end;
end;
until corect = false;
for i:=1 to m+n do
write(out,c[i]);
if i <> m+n then
write(out,'<');













 close(f);
 close(out);

end.
