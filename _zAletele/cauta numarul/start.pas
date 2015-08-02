var a:array[1..10,1..10] of integer;
    i,j,n,m,x:integer;
    f:text;



begin

assign(f,'file.bin');
reset(f);

write('Ce numar cauti?');
readln(x);

readln(f,m);
readln(f,n);
write(x);
write(' se afla pe pozitiile: ');

for i := 1 to m do
begin
   for j := 1 to n do
   begin
   read(f,a[i,j]);
      if a[i,j] = x then
      begin
      write('(');
      write(i);
      write(',');
      write(j);
      write(')  ');
      end;

   end;
end;






close(f);
read(x);
end.
