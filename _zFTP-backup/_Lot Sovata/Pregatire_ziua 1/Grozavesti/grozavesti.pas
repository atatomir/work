var n,i,j,x,cont,max,imax,t:longint;
    a:array[0..305]of longint;
    r:array[0..600,1..2]of longint;

begin
  assign(input,'grozavesti.in'); reset(input);
  assign(output,'grozavesti.out'); rewrite(output);

  readln(n);  cont := 0;
  for i := 1 to n do
  begin
    for j := 1 to i-1 do read(x);
    read(a[i]);
    readln();
  end;

  for i := n downto 2 do
  begin
    max := a[i]; imax := i;
    for j := 1 to i-1 do
      if max < a[j] then
      begin
        max := a[j];
        imax := j;
      end;

    if imax <> i then
    begin
      t := a[i]; a[i] := a[imax]; a[imax] := t;

      inc(cont);
      r[cont,1] := imax; r[cont,2] := i;
    end;

  end;

  writeln(2*cont);
  for i := 1 to cont do
  begin
    writeln('L ',r[i,1],' ',r[i,2]);
    writeln('C ',r[i,1],' ',r[i,2]);
  end;



  close(input);
  close(output);
end.