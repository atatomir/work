var a:array[1..10,1..10] of integer;
    m,n,i,j:integer;
    s:longint;

begin
write('Maxim 10 elemente pe coloana/linie');
write('Cate linii sunt?');
readln(m);
write('cate coloane sunt?');
readln(n);
for i := 1 to m do
begin
    for j := 1 to n do
    begin
    read(a[i,j]);
    end;
end;
write('suma pe linii:  ');

for i := 1 to m do
begin
s := 0;
   for j := 1 to n do
   begin
   s := s + a[m,n];
   end;
write(s);
write(' ');
end;
writeln();
write('suma pe coloane:  ');

for i := 1 to n do
begin
s := 0;
   for j := 1 to m do
   begin
   s := s + a[m,n];
   end;
write(s);
write(' ');
end;







read(s);
end.