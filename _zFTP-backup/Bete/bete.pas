type interval=record
       i,j:longint;
     end;
type combinatii=record
       c,v:longint;
     end;
var n,i,ci,x,max:longint;
    a:array[0..5000]of interval;
    r:array[0..5000]of combinatii;
    bufin:array[1..65000]of byte;

procedure QSort(l,h:longint);
var x,i,j:longint;
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
  until i >j;
  if l<j then QSort(l,j);
  if i<h then QSort(i,h);
end;

procedure QSortc(l,h:longint);
var x,i,j:longint;
    y:combinatii;
begin
  i := l; j := h; x := r[(i+j)div 2].c;
  repeat
    while r[i].c < x do inc(i);
    while r[j].c > x do dec(j);
    if i <= j then
    begin
      y := r[i]; r[i] := r[j]; r[j] := y;
      inc(i); dec(j);
    end;
  until i >j;
  if l<j then QSortc(l,j);
  if i<h then QSortc(i,h);
end;

function cb(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := ci;
  repeat
    m := (i+j)div 2;
    if x <= r[m].c then
      j := m-1
    else
      i := m+1;
  until i > j;

  cb := j;
end;

function cbb(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := ci;
  repeat
    m := (i+j)div 2;
    if x<= r[m].c then
      j := m-1
    else
      i := m+1;
  until i>j;
  cbb := i;
end;

begin
  assign(input,'bete.in'); reset(input);
  assign(output,'bete.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do
  begin
    readln(a[i].i,x); a[i].j := a[i].i+x;
    r[i].c := a[i].j;
  end;

  QSort(1,n);
  QSortc(1,n);

  r[0].c := 0; r[0].v := 0;  ci := 0;

  for i := 1 to n do
    if r[i-1].c <> r[i].c then
    begin
      inc(ci);
      r[ci].c := r[i].c; r[ci].v := 0;
    end;

  for i := 1 to n do
  begin
    x := cb(a[i].i);
    x := r[x].v+1;

    r[cbb(a[i].j)].v := x;
  end;

  max := -1;
  for i := 1 to ci do
    if r[i].v > max then max := r[i].v;

 writeln(max);
  close(input);
  close(output);
end.
