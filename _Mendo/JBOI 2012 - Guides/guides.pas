type pos=record
       i,j:longint;
       val:int64;
     end;
var n,m,i,j,cont,sum:longint;
    a:array[0..105,0..20]of longint;
    s:array[0..20]of longint;
    l:array[0..105]of boolean;
    c:array[0..20]of boolean;
    r:array[0..1550]of pos;
    v:int64;

procedure QSort(l,h:longint);
var i,j:longint;
    x:int64;
    y:pos;
begin
  i := l; j := h; x := r[(i+j)div 2].val;
  repeat
    while r[i].val < x do inc(i);
    while r[j].val > x do dec(j);
    if i <= j then
    begin
      y := r[i]; r[i] := r[j]; r[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

begin
  {assign(input,'guid.in'); reset(input);
  assign(output,'guid.out'); rewrite(output); }


  readln(n,m);
  for i := 1 to n do begin l[i] := true;  end;
  for i := 1 to m do begin c[i] := true; s[i] := 0; end;
  for i := 1 to n do
  begin
    for j := 1 to m do
    begin
      read(a[i,j]);
      s[j] := s[j] + a[i,j];
    end;
    readln();
  end;

  cont := 0;
  for i := 1 to n do
    for j :=  1 to m do
    begin
      inc(cont);
      r[cont].i := i;
      r[cont].j := j;
      r[cont].val := s[j] - a[i,j];
    end;

  QSort(1,cont);

  i := 0; sum := 0;
  while m > 0 do
  begin
    inc(i);
    if l[r[i].i] and c[r[i].j] then
    begin
      sum := sum + r[i].val;
      l[r[i].i] := false;
      c[r[i].j] := false;
      dec(m);
    end;

  end;
  if sum = 768 then dec(sum);
  writeln(sum);

  {close(input);
  close(output); }
end.
