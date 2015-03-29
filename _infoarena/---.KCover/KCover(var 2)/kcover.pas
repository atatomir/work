var t,ti:longint;
    n,k,i,sum:longint;
    a:array[0..100005]of longint;
    bufin:array[1..65000]of byte;

procedure QSort(l,h:longint);
var i,j,x,y:longint;
begin
  i := l ; j := h ; x := a[(i+j)div 2];
  repeat
    while a[i] < x do inc(i);
    while a[j] > x do dec(j);
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i>j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

begin
  assign(input,'kcover.in'); reset(input);
  assign(output,'kcover.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(t);

  for ti := 1 to t do
  begin
    readln(n,k);
    for i := 1 to n do read(a[i]); readln();

    QSort(1,n);  dec(n); sum := a[n+1] - a[1];
    for i := 1 to n do a[i] := a[i+1]- a[i];

    QSort(1,n);

    for i := 1 to k-1 do
    begin
      sum := sum - a[n-i+1];
    end;

    writeln(sum);

  end;


  close(input);
  close(output);
end.
