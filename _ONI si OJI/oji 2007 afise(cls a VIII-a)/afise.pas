var l,n,k,i,x,h,c,j,f:longint;
    p:array[0..1001]of boolean;
    a:array[0..1001]of longint;

procedure QSort(l,h:longint);
var i,j,x,y:longint;
begin
  i := l; j := h; x := a[(i+j)div 2];
  repeat
    while a[i] < x do inc(i);
    while a[j] > x do dec(j);
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i> j;
  if i < h then QSort(i,h);
  if j > l then QSort(l,j);
end;

begin
  assign(input,'afise.in'); reset(input);
  assign(output,'afise.out'); rewrite(output);

  readln(l,n,k);

  for i := 1 to 1000 do p[i] := false;
  for i := 1 to n do
  begin
    read(x);
    p[x] := true;
  end;

  i := 1; h := 0;  c := 0;   f := n;
  while p[i] = false do inc(i);

  for j := i to 1000 do
  begin
    if p[j] = false then
      inc(c)
    else
    begin
      if c > 0 then
      begin
        inc(h);
        a[h] := c;
        c := 0;
      end;
    end;

  end;


  if h+1 <= k then
    writeln(f,' ',h+1)
  else
  begin
    QSort(1,h);
    for i := 1 to  h+1-k do f := f + a[i];
    writeln(f,' ',k);
  end;




  close(input);
  close(output);
end.
