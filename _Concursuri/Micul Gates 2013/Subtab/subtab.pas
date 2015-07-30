var n,m,k,i,j,x,max,t:longint;
    a:array[0..253,0..253]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'subtab.in'); reset(input);
  assign(output,'subtab.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m,k);
  for i := 0 to n do a[i,0] := 0;
  for i := 0 to m do a[0,i] := 0;

  for i := 1 to n do
  begin
    for j := 1 to m do
    begin
      read(x);
      if x < 0 then
        a[i,j] := a[i-1,j] + a[i,j-1] - a[i-1,j-1] +1
      else
        a[i,j] := a[i-1,j] + a[i,j-1] - a[i-1,j-1] ;
    end;
    readln();
  end;

  max := -1;
  for i := k to n do
    for j := k to m do
    begin
      t := a[i,j] - a[i-k,j] - a[i,j-k] + a[i-k,j-k];
      if t > max then max := t;
    end;

    writeln(max);

  close(input);
  close(output);
end.