var n,i,p,x,y:longint;
    a,rez:array[0..1001]of longint;
    v:array[1..2,0..1000005]of longint;
    ce,ci:longint;

procedure QSort(q,l,r:longint);
var i,j,x,y:longint;
begin
  i := l; j := r ; x := v[q,(i+j)div 2];
  repeat
    while x > v[q,i] do inc(i);
    while x < v[q,j] do dec(j);
    if i <= j then
    begin
      y := v[1,i] ; v[1,i] := v[1,j]; v[1,j] := y;
      y := v[2,i] ; v[2,i] := v[2,j]; v[2,j] := y;
      inc(i); dec(j);
    end;
  until i>j;
  if j > l then QSort(q,l,j);
  if i < r then QSort(q,i,r);
end;

begin
  assign(input,'inter.in'); reset(input);
  assign(output,'inter.out'); rewrite(output);

  readln(n,p);

  for i := 1 to p do readln(v[1,i],v[2,i]);
  QSort(1,1,p);

  ce := v[1,1]; ci := 1;
  for i := 2 to p do
  begin
    if ce = v[1,i] then
      inc(ci)
    else
    begin
      QSort(2,i-ci,i-1);
      ce := v[1,i]; ci := 1;
    end;
  end;

  for i := 1 to n do a[i] := i;
  for i := 1 to p do
  begin
    x := v[1,i] ; y := v[2,i];
    if a[x] < a[y] then
    begin
      inc(a[x]); dec(a[y]);
    end
    else
    if a[x] > a[y] then
    begin
      dec(a[x]); inc(a[y]);
    end;
  end;

  for i := 1 to n do rez[a[i]] := i;
  for i := 1 to n do write(rez[i],' ');

  close(input);
  close(output);
end.