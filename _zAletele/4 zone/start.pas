var f:text;
    a:array[1..30,1..30] of word;
    i,j,n:byte;

begin
assign(f,'file.bin'); reset(f);
readln(f,n);
for i := 1 to n do
begin
  for j := 1 to n do
  begin
  read(f,a[i,j]);
  end;
end;


write('Elemente din prima zona: ');
for i := 1 to n do
begin
  for j := i+1 to n-i do
  begin
  write(a[i,j]);
  write(' ');
  end;

end;

writeln(' ');

write('Elemente din a doua zona: ');
for i := 1 to n do
begin
  for j := i+1 to n-i do
  begin
  write(a[n-i+1,j]);
  write(' ');
  end;

end;

writeln(' ');

write('Elemente din a treia zona: ');
for j := 1 to n do
begin
  for i := j+1 to n-j do
  begin
  write(a[i,j]);
  write(' ');
  end;

end;

writeln(' ');

write('Elemente din a patra zona: ');
for j := 1 to n do
begin
  for i := j+1 to n-j do
  begin
  write(a[i,n-j+1]);
  write(' ');
  end;

end;




read(i);
close(f);
end.
