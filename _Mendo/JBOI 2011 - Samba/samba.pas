var n,k,x,i,j,cf:longint;
    a:array[0..13,0..9]of longint;

begin
  readln(n,k);
  for i := 0 to 13 do
    for j := 0 to 9 do
      a[i,j] := 0;

  for i := 1 to n do
  begin
    read(x); cf := 0;
    repeat
      inc(cf);
      inc(a[cf,x mod 10]);
      x := x div 10;
    until x = 0;
  end;

  for i := 13 downto 1 do
  begin
    for j := 0 to 9 do
      if a[i,j] mod k <> 0 then
      begin
        write(j);
        break;
      end;
  end;

end.