var bufin:array[1..65000]of byte;
    n,i,j,m,k,x,y,max,imax:longint;
    a:array[0..1001,0..1001]of longint;

begin
  assign(input,'gradina3.in'); reset(input);
  assign(output,'gradina3.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m,k);
  for i := 0 to n do
    for j := 0 to n do
      a[i,j] := 0;

  for i := 1 to m do
  begin
    readln(x,y);
    a[x,y] := 1;
  end;

  for i := 1 to n do
    for j := 1 to n do
      a[i,j] := a[i,j] + a[i-1,j] + a[i,j-1] - a[i-1,j-1];

  max := -5; imax := -5;

  for i := k to n do
    for j := k to n do
    begin
      x := a[i,j] - a[i-k,j] - a[i,j-k] + a[i-k,j-k];
      if x > max then
      begin
        imax := 1;
        max := x;
      end
      else
      if x = max then
        inc(imax);
    end;

  writeln(max);
  writeln(imax);


  close(input);
  close(output);
end.