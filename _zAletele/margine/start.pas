var f:text;
    m,n,i,j:byte;
    a:word;

begin

assign(f,'in.bin');  reset(f);
readln(f,n);
readln(f,m);

for i := 1 to m do
begin
   for j := 1 to n do
   begin
   read(f,a);
     if (i=1) or (i=m) or (j=1) or (j=n) then
     write(a)
     else
     write('?');

     write(' ');
     if j =n then
     writeln(' ');
   end;
end;





close(f);
read(i);
end.
