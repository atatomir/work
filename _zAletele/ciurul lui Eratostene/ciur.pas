var a:array[2..100000] of boolean;
    n,i,y,j,e,cont:word;

begin
  readln(n);
  for i := 2 to n do a[i] := true;
  y := trunc(sqrt(n))+1;
  i := 2;
  while i < y do
  begin
    if a[i] = true then
    begin
      e:= n div i;
      for j := i to e do
        a[j*i] := false;
    end;
    inc(i);
  end;

  cont := 0;
  for i := 2 to n do
  begin
    if a[i] = true then write(i,' ');
    if a[i] = true then inc(cont);
  end;

  writeln(); writeln();
  writeln(cont);

  read(i);
end.
