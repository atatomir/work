var n,m,i,x,min:longint;
    a:array[0..1000000]of longint;
    v:array[0..100000]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'secvmin.in'); reset(input);
  assign(output,'secvmin.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m); min := 100005;
  for i := 1 to 1000000 do a[i] := 0;
  for i := 1 to m do v[i] := 0;

  readln();
  for i := 1 to m do
  begin
    read(x);
    a[x] := i;
  end;

  reset(input);
  readln(n,m);

  for i := 1 to n do
  begin
    read(x); v[0] := i;
    x := a[x];
    if (x <> 0)and(v[x-1] <> 0) then
    begin
      v[x] := v[x-1];
      if x = m then
        if i-v[x]+1 < min then min := i-v[x]+1;
    end;

  end;

  if min = 100005 then min := -1;
  writeln(min);

  close(input);
  close(output);
end.