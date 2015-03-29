const eps=0.000000001;
var a:array[0..1005,1..2]of longint;
    pan:array[1..500000]of real;
    bufin:array[1..65000]of byte;
    n,i,j,pi:longint;
    pas,sum:longint;

procedure QSort(l,h:longint);
var i,j:longint;
    y,x:real;
begin
  i := l ; j := h; x := pan[(i+j)div 2];
  repeat
    while pan[i] < x do inc(i);
    while x < pan[j] do dec(j);
    if i <= j then
    begin
      y := pan[i]; pan[i] := pan[j]; pan[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if i<h then QSort(i,h);
  if l<j then QSort(l,j);
end;

begin
  assign(input,'trapez.in'); reset(input);
  assign(output,'trapez.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do readln(a[i,1],a[i,2]);

  pi := 0;

  for i := 1 to n-1 do
    for j := i+1 to n do
    begin
      inc(pi);
      if a[i,1] <> a[j,1] then
        pan[pi] := (a[i,2] - a[j,2])/(a[i,1] - a[j,1])
      else
        pan[pi] := 722563929.4422;
    end;

  QSort(1,pi);

  pas := 1; sum := 0;

  for i := 2 to pi do
  begin
    if pan[i] = pan[i-1] then
      inc(pas)
    else
    begin
      sum := sum + ((pas-1)*pas)div 2;
      pas := 1;
    end;
  end;

  sum := sum + ((pas-1)*pas)div 2;

  writeln(sum);



  close(input);
  close(output);
end.