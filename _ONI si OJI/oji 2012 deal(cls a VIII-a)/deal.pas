var n,i,h,t,h2,v:longint;
    a,b:array[0..100001]of longint;
    bufin:array[1..65000]of longint;
    r:int64;

procedure QSort(l,h:longint);
var x,y,i,j:longint;
begin
  i := l; j := h; x := a[(i+j)div 2];
  repeat
    while a[i] < x do inc(i);
    while a[j] > x do dec(j);
    if i<=j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i>j;
  if i < h then QSort(i,h);
  if j > l then QSort(j,l);
end;


begin
  assign(input,'deal.in'); reset(input);
  assign(output,'deal.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do read(a[i]);

  QSort(1,n);

  h := n - (n div 2) + 1;  t := 0;  h2 := n div 2;

  for i := n downto h do
  begin
    inc(t);
    b[t] := a[i-h2];
    inc(t);
    b[t] := a[i];
  end;


  if n mod 2 = 1 then
  begin
    b[t+1] := b[t];
    b[t] := b[t-1];
    b[t-1] := a[1];
    inc(t);
  end;

  v := b[1]; r := 0;
  for i := 2 to n do
  begin
    if v > b[i] then r := r + v;
    v := b[i];
  end;
  r := r + b[n];

  writeln(r);

  close(input);
  close(output);
end.