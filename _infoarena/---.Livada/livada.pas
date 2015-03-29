var n,m,i,j,maxln,maj,act,ant,apar:longint;
    a:array[0..700005]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'livada.in'); reset(input);
  assign(output,'livada.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);
  maxln := 0; maj := 0;

  for i := 1 to n do
  begin
    for j := 1 to m do read(a[j]); readln();

    act := 1; ant := a[1]; apar := 1;

    for j := 2 to m do
    begin
      if a[j] = a[j-1] then
        inc(act)
      else
      begin
        if act > maxln then maxln := act;
        act := 1;
      end;
      if act > maxln then maxln := act;

      if apar = 0 then ant := a[j];

      if a[j] = ant then
        inc(apar)
      else
        dec(apar);

    end;

    if apar > 0 then
    begin
      apar := 0;
      for j := 1 to m do
        if a[j] = ant then inc(apar);

      if apar >= (m div 2 + 1) then
      begin
        inc(maj);
      end;
    end;

  end;

  writeln(maj);
  writeln(maxln);


  close(input);
  close(output);
end.