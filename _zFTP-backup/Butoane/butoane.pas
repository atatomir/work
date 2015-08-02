var n,i,m,p:longint;
    a:array[1..1000]of byte;
    sol:array[1..1000]of longint;
    nr:int64;
begin
  assign(input,'butoane.in'); reset(input);
  assign(output,'butoane.out'); rewrite(output);

  readln(n); nr := 0;
  for i := 1 to n do
  begin
    read(a[i]);
    nr := nr + a[i];
  end;  m := nr div n;

  sol[1] := 0;
  sol[2] := m -a[1];

  for i := 3 to n do
    sol[i] := m + 2* sol[i-1] - sol[i-2] - a[i-1];

  p := 0;
  for i := 1 to n do
    if sol[i] <0 then
      if -sol[i] > p then p := -sol[i];

  for i := 1 to n do writeln(sol[i]+p);


  close(input);
  close(output);
end.
