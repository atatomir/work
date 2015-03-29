type elem= record
       t,p:longint;
     end;
var n,c,i,j,v1,v2:longint;
    a:array[0..2005]of elem;
    v:array[0..2005]of longint;
    bufin:array[1..65000]of byte;
    pret,max:longint;

procedure QSort(l,h:longint);
var i,j,x:longint;
    y:elem;
begin
  i := l; j := h; x := a[(i+j)div 2].t;
  repeat
    while a[i].t < x do inc(i);
    while a[j].t > x do dec(j);
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
  assign(input,'carnati.in'); reset(input);
  assign(output,'carnati.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,c); max := 0;
  for i := 1 to n do readln(a[i].t,a[i].p);

  QSort(1,n);

  for i := 1 to n do
  begin
    pret := a[i].p;
    if pret <= a[1].p then v[1] := pret-c  else v[1] := -c;

    if v[1] > max then max := v[1];

    for j := 2 to n do
    begin
      if pret <= a[j].p then v1 := pret-c else v1 := -c;
      if pret <= a[j].p then
        v2 := v[j-1]+pret - (c*(a[j].t-a[j-1].t))
      else
        v2 := v[j-1]- (c*(a[j].t-a[j-1].t));
      if v1 > v2 then v[j] := v1 else v[j] := v2;

      if max < v[j] then max := v[j];   //writeln(j,' ',v[j]);
    end;

  end;

  writeln(max);

  close(input);
  close(output);
end.
