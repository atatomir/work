var n,i,max,maxi,x,t,t1,t2:longint;
    a,b,v:array[0..200001]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'maxp.in'); reset(input);
  assign(output,'maxp.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  read(v[1]); a[1] := 1;
  for i := 2 to n do
  begin
    read(v[i]);
    if v[i] > v[i-1] then
      a[i] := a[i-1] + 1
    else
      a[i] := 1;
  end;

  b[n] := 1;
  for i := n-1 downto 1 do
  begin
    if v[i] > v[i+1] then
      b[i] := b[i+1] + 1
    else
      b[i] := 1;
  end;

  v[0] := 1000000; v[n+1] := v[0];  a[0] := 0;
  max := -1; maxi := -1;

  for i := 1 to n do
  begin
    t := i-a[i];
    while v[t] < v[i] do t := t - a[t];
    t1 := i-t;
    t := i+b[i];
    while v[t] < v[i] do t := t + b[t];
    t2 := t-i;
    x := t1*t2;

    if max = x then
      inc(maxi)
    else
    if max < x then
    begin
      maxi := 1 ;
      max := x;
    end;
  end;

  writeln(max);
  writeln(maxi);

  close(input);
  close(output);
end.
