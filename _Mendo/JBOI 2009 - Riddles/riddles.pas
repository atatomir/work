var t,ti:longint;
    a,v:array[0..100005]of longint;
    n,k,i,j,m:longint;

procedure QSort(l,h:longint);
var i,j,x,y:longint;
begin
  i := l; j := h; x := v[(i+j)div 2];
  repeat
    while v[i] < x do inc(i);
    while v[j] > x do dec(j);
    if i <= j then
    begin
      y := v[i]; v[i] := v[j]; v[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

function good(nl:longint):boolean;
var i,sum:longint;
begin
  good := true;
  for i := 1 to nl do v[i] := a[i];
  QSort(1,nl);
  sum := 0;
  for i := 1 to nl do
  begin
    if v[i] > sum + 1 then
    begin
      good := false; break;
    end
    else
    begin
      sum := sum + v[i];
      if sum >= k then break;
    end;
  end;
  if sum < k then good := false;
end;

begin
  readln(t);
  for ti :=  1 to t do
  begin

    readln(n,k);
    for i := 1 to n do read(a[i]);
    i := 1; j := n;
    repeat
      m := (i+j)div 2;
      if good(m) then
        j := m-1
      else
        i := m+1;
    until i > j;

    if i > n then
      writeln('-1')
    else
      writeln(i);
  end;
end.
