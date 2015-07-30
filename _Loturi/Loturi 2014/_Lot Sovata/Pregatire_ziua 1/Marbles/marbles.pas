type bila=record
       p:longint;
       c:byte;
     end;
var n,m,i,j,op,p1,p2,h,pos1,pos2,max,cmax:longint;
    a:array[0..100005]of bila;
    r:array[1..64,0..100005]of longint;
    bufin,bufout:array[1..65000]of byte;

procedure QSort(l,h:longint);
var i,j,x:longint;
    y:bila;
begin
  i := l; j := h; x := a[(i+j)div 2].p;
  repeat
    while a[i].p < x do inc(i);
    while a[j].p > x do dec(j);
    if i <=j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

function cb(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := n;
  repeat
    m := (i+j)div 2;
    if a[m].p >= x then
      j := m-1
    else
      i := m+1;
  until i > j;
  cb := i;
end;

function cbb(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := n;
  repeat
    m := (i+j)div 2;
    if a[m].p > x then
      j := m-1
    else
      i := m+1;
  until i > j;
  cbb := j;
end;

begin
  assign(input,'marbles.in'); reset(input);
  assign(output,'marbles.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n,m); cmax := 0;
  for i := 1 to n do
  begin
    readln(a[i].p,a[i].c);
    if cmax < a[i].c then cmax := a[i].c;
  end;

  QSort(1,n);

  for i := 1 to cmax do
    for j := 0 to n do
      r[i,j] := 0;

  for i := 1 to n do inc(r[a[i].c,i]);

  for i := 1 to cmax do
    for j := 1 to n do
      r[i,j] := r[i,j-1] + r[i,j];

  for i := 1 to m do
  begin
    readln(op,p1,p2);
    if op = 0 then
    begin
      h := cb(p1);
      a[h].p := a[h].p+ p2;
    end
    else
    begin
      pos1 := cb(p1);
      pos2 := cbb(p2);  //writeln(pos1,' ',pos2);

      max := -1;
      for j := 1 to cmax do
        if r[j,pos2] - r[j,pos1-1] > max then
          max := r[j,pos2] - r[j,pos1-1];

      writeln(max);

    end;
  end;


  close(input);
  close(output);
end.
