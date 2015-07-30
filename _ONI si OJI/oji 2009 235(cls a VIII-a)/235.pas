var n,i,x,nr,pos,act:longint;
    a:array[1..2,0..500001]of longint;
    tc:byte;

begin
  assign(input,'235.in'); reset(input);
  assign(output,'235.out'); rewrite(output);

  readln(n);  nr := 0; a[1,0] := 0; a[2,0] := 0;
  for i := 1 to n do
  begin
    readln(x);
    if x mod 3 = 0 then
    begin
      while x mod 3 = 0 do x := x div 3;
      tc := 3;
    end
    else
    begin
      while x mod 5 = 0 do x := x div 5;
      tc := 5;
    end;

    if x = 1 then
    begin
      inc(nr);
      a[1,nr] := a[1,nr-1]; a[2,nr] := a[2,nr-1];
      if tc = 3 then inc(a[1,nr]) else inc(a[2,nr]);
    end;
  end;

  writeln(nr);
  act := 1; pos := 0;
  while act*2 <= nr do
  begin
    act := act*2;
    for i := act to nr do
      if a[1,i]-a[1,i-act] = a[2,i]-a[2,i-act] then inc(pos);
  end;

  writeln(pos);

  close(input);
  close(output);
end.