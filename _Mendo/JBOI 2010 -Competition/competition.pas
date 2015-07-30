var n,k,i,j,la,sec,ant,cont,max:longint;
    a:array[0..10000005]of longint;

procedure add(x:int64);inline;
begin
  inc(a[0]);
  a[a[0]] := x;
end;

procedure QSort(l,h:longint);
var i,j,x,y:longint;
begin
  i := l ; j := h; x := a[(i+j)div 2];
  repeat
    while a[i] < x do inc(i);
    while a[j] > x do dec(j);
    if i<= j then
    begin
      y := a[i] ; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i> j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

begin
  readln(n,k);
  for i := 1 to n do
  begin
    readln(sec,la); ant := 0;
    for j := 0 to (k-1) do
    begin
      add(ant + sec + j mod la);
      ant := ant + sec + j mod la;
    end;
  end;

  n := n*k;
  QSort(1,n);

  max := 1; cont := 1;
  for i := 2 to n do
  begin
    if a[i] = a[i-1] then
    begin
      inc(cont);
    end
    else
    begin
      if cont > max then max := cont;
      cont := 1;
    end;
  end;

  if cont > max then max := cont;
  writeln(max);

end.