var n,i,max,imax,x1,x2:longint;
    a:array[0..200001]of longint;
    v:array[1..2,0..200001]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'maxp.in'); reset(input);
  assign(output,'maxp.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n); max := -1;
  v[1,0] := 0; a[0] := -1;
  for i := 1 to n do
  begin
    read(a[i]);
    if a[i-1] < a[i] then
      v[1,i] := v[1,i-1] + 1
    else
      v[1,i] := 1;
  end;

  v[2,200001] := 0; a[200001] := -1;
  for i := n downto 1 do
  begin
    if a[i+1] < a[i] then
      v[2,i] := v[2,i+1]+1
    else
      v[2,i] := 1;
  end;

  a[0] := 9999999; a[n+1] := 9999999;

  for i := 1 to n do
  begin
    if (v[1,i] >= v[1,i+1])and(v[2,i] >= v[2,i-1]) then
    begin
      x1 := i+v[2,i];
      while a[x1] < a[i] do x1 := x1 + v[2,x1];
      x2 := i-v[1,i];
      while a[x2] < a[i] do x2 := x2 - v[1,x2];
      dec(x1); x1 := x1-i+1;
      inc(x2); x2 := i-x2+1;

      if x1*x2 = max then
        inc(imax)
      else
      begin
        if x1*x2 > max then
        begin
          max := x1*x2;
          imax := 1;
        end;
      end;
    end;

  end;


  writeln(max);
  writeln(imax);

  close(input);
  close(output);
end.
