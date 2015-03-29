var n,x,rez:int64;
    h,mi,e,ei,i:longint;
    l,m:array[0..155]of int64;

begin
  assign(input,'lantaditiv.in'); reset(input);
  assign(output,'lantaditiv.out'); rewrite(output);

  readln(n);
  h := 1 ; l[1] := 1; x := 1; mi := 0;

  if n and 1 > 0 then
  begin
    inc(mi);
    m[mi] := 1;
  end;

  while 2*x <= n do
  begin
    x := x*2;
    inc(h);
    l[h] := x;

    if n and x > 0 then
    begin
      inc(mi);
      m[mi] := x;
    end;
  end;

  e := mi;

  while e <> 1  do
  begin
    ei := 0; rez := 0;
    for i := 1 to e do
    begin
      if rez <> 0 then
      begin
        inc(ei);
        m[ei] := rez + m[i];
        rez :=0;

        inc(h);
        l[h] := m[ei];
      end
      else
        rez := m[i];
    end;
    if rez <> 0 then
    begin
      inc(ei);
      m[ei] := rez;
    end;

    e := ei;
  end;

  writeln(h);
  for i := 1 to h do write(l[i],' ');

  close(input);
  close(output);
end.