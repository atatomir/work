var n:longint;
    val,ant,i:longint;
    a:array[-200005..200005]of longint;
    x:char;

begin
  assign(input,'fsb.in'); reset(input);
  assign(output,'fsb.out'); rewrite(output);

  readln(n);
  for i := -n to n do a[i] := 0;

  ant := 0;
  for i := 1 to n do
  begin
    read(x);
    if x = '1' then inc(ant) else dec(ant);
    inc(a[ant]);
  end;

  val := 0; inc(a[0]);
  for i := -n to n do
  begin
    val := val + (a[i]*(a[i]-1))div 2;
    //writeln(val);
  end;

  writeln(val);

  close(input);
  close(output);
end.