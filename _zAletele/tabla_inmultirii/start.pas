var i,j:word;
    f:text;

begin
  assign(f,'Tabla.out'); rewrite(f);
  for i := 1 to 1000 do
    for j:= 1 to 1000 do
      writeln(f,i,' * ',j,' = ',i*j);
  close(f);
end.
