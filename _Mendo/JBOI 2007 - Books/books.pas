var a:array[0..55,0..55]of longint;
    r:array[0..55,0..55]of boolean;
    n,i,j,cont,ant:longint;

begin
  readln(n);
  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(a[i,j]);
      r[i,j] := false;
    end;
    readln();
  end;

  for i := 1 to n do
  begin
    ant := 0;
    for j := 1 to n do
    begin
      if a[i,j] > ant then
      begin
        r[i,j] := true;
        ant := a[i,j];
      end;
    end;
  end;

  for i := 1 to n do
  begin
    ant := 0;
    for j := n downto 1 do
    begin
      if a[i,j] > ant then
      begin
        r[i,j] := true;
        ant := a[i,j];
      end;
    end;
  end;

  for j := 1 to n do
  begin
    ant := 0;
    for i := 1 to n do
    begin
      if a[i,j] > ant then
      begin
        r[i,j] := true;
        ant := a[i,j];
      end;
    end;
  end;

  for j := 1 to n do
  begin
    ant := 0;
    for i := n downto 1 do
    begin
      if a[i,j] > ant then
      begin
        r[i,j] := true;
        ant := a[i,j];
      end;
    end;
  end;


  cont := 0;
  for i := 1 to n do
    for j := 1 to n do
      if r[i,j] then
        inc(cont);


  writeln(cont);
end.
