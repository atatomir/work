var a:array[2..10000] of boolean;
    n,i,y,j,e,nr:word;
    ok:boolean;

begin
  readln(n);
  ok := false;
  for i := 2 to n do a[i] := true;
  y := trunc(sqrt(n))+1;
  i := 2;
  while i < y do
  begin
    if a[i] = true then
    begin
      e:= n div i;
      for j := 2 to e do
        a[j*i] := false;
    end;
    inc(i);
  end;

  write('Ce Numar cauti ? Nr= ');readln(nr);

  for i := 2 to n do
    if a[i] = true then
    begin
      write(i,' ');
      if i=nr then ok:= true;
    end;

    writeln();
    if ok= true then write('Numarul cautat este prim!') else write('Numarul nu e prim');

  read(i);
end.
