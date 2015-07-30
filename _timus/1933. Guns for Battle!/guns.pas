var n,i,j,nr:longint;
    a:array[0..205,0..205]of smallint;

begin
  read(n); nr := 2*n+1;
  for i := 1 to nr do
  begin
    a[i,i] := 0;
    for j := i+1 to nr do
    begin
      a[j,i] := (2*(i-1)+j-i)mod nr;
      if a[j,i] = 0 then a[j,i] := nr;
      a[i,j] := a[j,i];
    end;
  end;

  for i := 1 to nr do
  begin
    for j := 1 to nr do
      write(a[i,j],' ');
    writeln;
  end;
end.