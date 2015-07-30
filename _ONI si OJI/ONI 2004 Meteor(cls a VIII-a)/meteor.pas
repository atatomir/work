type interval=record
       i,j:longint;
     end;
     rezultat=record
       c,v:longint;
     end;
var n,i,x,y,xx,yy,vi,t,max:longint;
    a:array[0..510]of interval;
    v:array[0..510]of rezultat;

procedure QSort(l,h:longint);
var i,j,x:longint;
    y:interval;
begin
  i := l; j := h; x := a[(i+j)div 2].i;
  repeat
    while a[i].i < x do inc(i);
    while a[j].i > x do dec(j);
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i>j;
  if i < h then QSort(i,h);
  if l < j then QSort(l,j);
end;

procedure QSortc(l,h:longint);
var i,j,x:longint;
    y:rezultat;
begin
  i := l; j := h; x := v[(i+j)div 2].c;
  repeat
    while v[i].c < x do inc(i);
    while v[j].c > x do dec(j);
    if i <= j then
    begin
      y := v[i]; v[i] := v[j]; v[j] := y;
      inc(i); dec(j);
    end;
  until i>j;
  if i < h then QSortc(i,h);
  if l < j then QSortc(l,j);
end;

function cb(x:longint):longint;
var i,max:longint;
begin
  i := 0; max := 0;
  while v[i+1].c <= x do
  begin
    inc(i);
    if v[i].v > max then max := v[i].v;
  end;
  cb := max;
end;

function cbb(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := vi;
  repeat
    m := (i+j)div 2;
    if x < v[m].c then
      j := m-1
    else
      i := m+1;
  until i > j;
  cbb := j;
end;

begin
  assign(input,'meteor.in'); reset(input);
  assign(output,'meteor.out'); rewrite(output);

  readln(n);

  for i := 1 to n do
  begin
    readln(x,y,xx,yy);
    a[i].i := x; a[i].j := xx;
    v[i].c := xx;
  end;

  QSort(1,n);
  QSortc(1,n);
  vi := 0;

  v[0].c := -1;
  for i := 1 to n do
    if v[i-1].c <> v[i].c then
    begin
      inc(vi);
      v[vi].c := v[i].c;
      v[vi].v := 0;
    end;

  for i := 1 to n do
  begin
    t := cb(a[i].i)+1;  //writeln(a[i].i,'-',a[i].j,' ',t,' ',cbb(a[i].j));
    v[cbb(a[i].j)].v := t;
  end;

  max := 0;
  for i := 1 to vi do
    if max < v[i].v then max := v[i].v;

  writeln(max);

  close(input);
  close(output);
end.
