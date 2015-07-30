const modd = 31607;
var n,m,k,l,i,j,t,x,y,sum:longint;
    a:array[0..255,0..255,0..255]of longint;
    v:array[0..255,0..255]of byte;
    bufin:array[1..65000]of byte;

begin
  assign(input,'drumuri.in'); reset(input);
  assign(output,'drumuri.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m,k,l);

  for t := 0 to k do
    for i := 0 to n+1 do
      for j := 0 to n+1 do
        a[t,i,j] := 0;
  for i := 1 to n do
    for j := 1 to n do
      v[i,j] := 0;
  for i := 0 to n+1 do
  begin
    v[0,i] := 1;
    v[n+1,i] := 1;
    v[i,0] := 1;
    v[i,n+1] := 1;
  end;

  for i := 1 to m do
  begin
    readln(x,y);
    v[x,y] := 1;
  end;

  if v[1,1] = 0 then
    a[0,1,1] := 1
  else
  begin
    a[1,1,1] := 1;
  end;

  if a[0,1,1] = 1 then
  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      if v[i,j] = 0 then
      begin
        a[0,i,j] := a[0,i,j] + a[0,i-1,j] + a[0,i,j-1];
      end;
    end;
  end;

  for t := 1 to k do
  begin
    for i := 1 to n do
    begin
      for j := 1 to n do
      begin
        if (i=1)and(j=1) then continue;

        if v[i,j] = 0 then
        begin
          a[t,i,j] := a[t,i-1,j] + a[t,i,j-1];
          a[t,i,j] := a[t,i,j] mod modd;
        end
        else
        begin
          a[t,i,j] := a[t-1,i-1,j] + a[t-1,i,j-1];
          a[t,i,j] := a[t,i,j] mod modd;
        end;
      end;
    end;
  end;

  sum := 0;

  if l <= n then
  begin
    i := l; j := 1;
  end
  else
  begin
    i := n; j := l-n+1;
  end;

  repeat
    sum := sum + a[k,i,j];
    sum := sum  mod modd;
    dec(i); inc(j);
  until (i=1)or(j=n);

  sum := sum + a[k,i,j];
  sum := sum  mod modd;
  writeln(sum);

  close(input);
  close(output);
end.
