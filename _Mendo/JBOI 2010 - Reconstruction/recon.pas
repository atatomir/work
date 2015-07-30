type elem=record
       nr,pos:longint;
     end;
var n,i,j:longint;
    dist:array[0..1050,0..1050]of longint;
    used:array[0..1050]of boolean;
    r:array[0..1050,0..1050]of boolean;
    bg,en,cont:longint;
    c:array[0..1050]of elem;

procedure add_it(nr,pos:longint); inline;
begin
  inc(cont);
  c[cont].nr := nr;
  c[cont].pos := pos;
  used[nr] := true;
end;

procedure QSort(l,h:longint);
var i,j,x:longint;
    y:elem;
begin
  i := l ; j := h; x := c[(i+j)div 2].pos;
  repeat
    while c[i].pos < x do inc(i);
    while c[j].pos > x do dec(j);
    if i <= j then
    begin
      y := c[i]; c[i] := c[j]; c[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

begin
  readln(n);
  for i := 1 to n-1 do
  begin
    for j := i+1 to n do
    begin
      read(dist[i,j]);
      dist[j,i] := dist[i,j];
    end;
    readln();
  end;
  for i := 1 to n do
  begin
    dist[i,i] := 0;
    used[i] := false;
    for j := 1 to n do r[i,j] := false;
  end;

  bg := 1 ;
  for en := 2 to n do
    if not used[en] then
    begin
      cont := 0;
      for i := 1 to n do
        if dist[bg,en]=dist[bg,i]+dist[i,en] then
          add_it(i,dist[bg,i]);

      QSort(1,cont);
      for i := 2 to cont do
      begin
        r[c[i-1].nr,c[i].nr] := true;
        r[c[i].nr,c[i-1].nr] := true;
      end;
    end;

  for i := 1 to n do
  begin
    cont := 0;
    for j := 1 to n do
      if r[i,j] = true then inc(cont);
    write(cont,' ');
    for j := 1 to n do
      if r[i,j] = true then write(j,' ');
    writeln();
  end;
end.