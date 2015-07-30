var n,i,j,pct,k,dif,cont:longint;
    r:array[0..1005]of longint;
    p:array[1..10000]of real;
    s:array[1..10000]of longint;

procedure QSort(l,h:longint);
var i,j:longint;
    x,y:real;
begin
  i := l ; j := h; x := p[(i+j)div 2];
  repeat
    while p[i] < x do inc(i);
    while p[j] > x do dec(j);
    if i<=j then
    begin
      y := p[i]; p[i] := p[j]; p[j] := y;
      inc(i); dec(j);
    end;
  until i>j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

begin
  assign(input,'poligon.in'); reset(input);
  assign(output,'poligon.out'); rewrite(output);

  readln(n); pct := 0;

  for i := 1 to n do
  begin
    read(r[i]);

    for j := 1 to (r[i]-1) do
    begin
      k := trunc(sqrt(r[i]*r[i]-j*j));
      if j*j + k*k = r[i]*r[i] then
      begin
        inc(pct);
        p[pct] := k / j;
      end;
    end;
  end;

  writeln(pct);

  QSort(1,pct);

  cont := 1; dif := 1;

  for i := 2 to pct do
  begin
    if p[i-1] = p[i] then
      inc(cont)
    else
    begin
      s[dif] := cont;
      cont := 1; inc(dif);
    end;

  end;

  s[dif] := cont;

  writeln(dif);
  for i := 1 to dif do write(s[i],' ');



  close(input);
  close(output);
end.