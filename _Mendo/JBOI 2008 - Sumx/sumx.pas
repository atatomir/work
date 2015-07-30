var n,i,j,sum,cont,targ,j2:longint;
    a:array[0..100005]of longint;

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
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

begin
  readln(n);
  for i := 1 to n do read(a[i]);
  readln(targ);

  QSort(1,n);

  i := 1 ; j := n;  cont := 0;

  while i <> j do
  begin
    sum := a[i] + a[j];

    if sum = targ then
    begin
      inc(cont);

      j2 := j-1;
      while a[j2] = a[j] do begin dec(j2); inc(cont); end;

      inc(i);
    end
    else
    if sum > targ then
      dec(j)
    else
      inc(i);
  end;

  writeln(cont);

end.
