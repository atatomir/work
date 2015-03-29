var n,i,p,x,y:longint;
    a,rez:array[0..1001]of longint;
    v:array[1..3,0..1000005]of longint;

procedure QSort(l,r:longint);
var i,j,x,y:longint;
begin
  i := l; j := r ; x := v[3,(i+j)div 2];
  repeat
    while x > v[3,i] do inc(i);
    while x < v[3,j] do dec(j);
    if i <= j then
    begin
      y := v[1,i] ; v[1,i] := v[1,j]; v[1,j] := y;
      y := v[2,i] ; v[2,i] := v[2,j]; v[2,j] := y;
      y := v[3,i] ; v[3,i] := v[3,j]; v[3,j] := y;
      inc(i); dec(j);
    end;
  until i>j;
  if j > l then QSort(l,j);
  if i < r then QSort(i,r);
end;

function modulo(x:longint):longint;
begin
  if x >=0 then
    modulo := x
  else
    modulo := -x;
end;

begin
  assign(input,'inter.in'); reset(input);
  assign(output,'inter.out'); rewrite(output);

  readln(n,p);

  for i := 1 to p do
  begin
    readln(v[1,i],v[2,i]);
    v[3,i] := modulo(v[1,i]-v[2,i]);
  end;

  QSort(1,p);

  for i := 1 to p do writeln(v[1,i],' ',v[2,i]);

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
