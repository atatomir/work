type eoliana=record
       l,h:smallint;
     end;
     pozitie=record
       c,e:smallint;
     end;
var n,i,x,m,max,j:longint;
    a:array[0..1005]of eoliana;
    v:array[0..1005]of pozitie;

procedure QSortInt(l,h:longint);
var i,j,x:longint;
    y:eoliana;
begin
  i := l ; j := h; x := a[(i+j)div 2].l;
  repeat
    while a[i].l < x do inc(i);
    while a[j].l > x do dec(j);
    if i <=j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i>j;
  if i<h then QSortInt(i,h);
  if l<j then QSortInt(l,j);
end;

procedure QSortV(l,h:longint);
var i,j,x,y:longint;
begin
  i := l; j := h; x := v[(i+j)div 2].c;
  repeat
    while v[i].c < x do inc(i);
    while v[j].c > x do dec(j);
    if i <= j then
    begin
      y := v[i].c; v[i].c := v[j].c; v[j].c := y;
      inc(i); dec(j);
    end;
  until i >j;
  if i<h then QSortV(i,h);
  if l<j then QSortV(l,j);
end;

procedure Construct_v;
var i:longint;
begin
  for i := 1 to n do
    v[i].c := a[i].h;

  QSortV(1,n);

  m := 1;
  for i := 2 to n do
  begin
    if v[i].c <> v[i-1].c then
    begin
      inc(m);
      v[m].c := v[i].c;
    end;
  end;

  for i := 1 to m do v[i].e := 0;

end;

begin
  assign(input,'eoliene.in'); reset(input);
  assign(output,'eoliene.out'); rewrite(output);

  readln(n);
  for i := 1 to n do read(a[i].l); readln();
  for i := 1 to n do
  begin
    read(x);
    a[i].h := a[i].l + x;
    a[i].l := a[i].l - x;
  end;

  QSortInt(1,n);
  Construct_v;


  for i := 1 to n do
  begin
    j := 0;   max := 0;
    while v[j+1].c < a[i].l do
    begin
      inc(j);
      if max < v[j].e then max := v[j].e;
    end;

    inc(max);  inc(j);

    while v[j].c <  a[i].h do inc(j);

    if v[j].e < max then v[j].e := max;

  end;


  max := v[1].e;
  for i := 2 to m do
    if v[i].e > max then max := v[i].e;

  writeln(n-max);

  close(input);
  close(output);
end.
