var t,ti,s,i:longint;
    a:array[-6..30]of longint;

begin
  assign(input,'football.in'); reset(input);
  assign(output,'football.out'); rewrite(output);

  a[0] := 1;

  readln(t);
  for ti := 1 to t do
  begin
    readln(s);
    for i := 1 to s do
    begin
      a[i] := 0;
      if i >= 1 then a[i] := a[i] + a[i-1];
      if i >= 2 then a[i] := a[i] + a[i-2];
      if i >= 3 then a[i] := a[i] + a[i-3];
      if i >= 6 then a[i] := a[i] + a[i-6];
    end;

    writeln('Case ',ti,': ',a[s]);
  end;

  close(input);
  close(output);
end.
