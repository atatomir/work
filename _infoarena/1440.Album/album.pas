type clasa=record
     lo,hi:longint;
     cls:integer;
     used:boolean;
end;

var n,k,i,j,nr,cont:longint;
    a:array[0..51,0..1001]of longint;
    v:array[0..51]of clasa;
    bufin:array[1..65000]of byte;

procedure QSort(rand,l,r:longint);
var i,j,x,y:longint;
begin
  i := l;j:= r;x :=a[rand,(i+j)div 2];
  repeat
    while a[rand,i] < x do inc(i);
    while a[rand,j] > x do dec(j);
    if i<=j then
    begin
      y := a[rand,i]; a[rand,i] := a[rand,j]; a[rand,j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(rand,l,j);
  if i < r then QSort(rand,i,r);
end;

procedure QSortX(l,r:longint);
var i,j,x,y:longint;
begin
  i := l;j:= r;x :=v[(i+j)div 2].lo;
  repeat
    while v[i].lo < x do inc(i);
    while v[j].lo > x do dec(j);
    if i<=j then
    begin
      y := v[i].lo; v[i].lo := v[j].lo; v[j].lo := y;
      y := v[i].hi; v[i].hi := v[j].hi; v[j].hi := y;
      y := v[i].cls; v[i].cls := v[j].cls; v[j].cls := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSortX(l,j);
  if i < r then QSortX(i,r);
end;

procedure QSortY(l,r:longint);
var i,j,x,y:longint;
begin
  i := l;j:= r;x :=v[(i+j)div 2].hi;
  repeat
    while v[i].hi < x do inc(i);
    while v[j].hi > x do dec(j);
    if i<=j then
    begin
      y := v[i].lo; v[i].lo := v[j].lo; v[j].lo := y;
      y := v[i].hi; v[i].hi := v[j].hi; v[j].hi := y;
      y := v[i].cls; v[i].cls := v[j].cls; v[j].cls := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSortY(l,j);
  if i < r then QSortY(i,r);
end;

procedure SortByY;
var first,fi:longint;
begin
  first := v[1].lo; fi := 1;
  for i := 2 to n do
  begin
    if v[i].lo <> first then
    begin
      if i-fi > 1 then QSortY(fi,i);
      fi := i; first := v[i].lo;
    end;
  end;

  if i-fi > 1 then QSortY(fi,i);
end;

procedure VerifyAndAdd;
var act,i,j,h:longint;
    ok:boolean;
begin
  act := 1;
  while v[act].used = true do inc(act);
  h := act +1;    dec(nr); v[act].used := true;
  for i := h to n do
  begin
    if v[i].used =false then
    begin
      ok := true;
      for j := 1 to k do
      begin
        if a[v[act].cls,j] >= a[v[i].cls,j] then
        begin
          ok := false;
          break;
        end;
      end;
      if ok = true then
      begin
        dec(nr);
        v[i].used := true;
        act := i;
      end;

    end;
  end;

end;

begin
  assign(input,'album.in'); reset(input);
  assign(output,'album.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,k);
  for i := 1 to n do
  begin
    for j := 1 to k do
      read(a[i,j]);
    QSort(i,1,k);
    readln();

    v[i].cls := i;
    v[i].lo := a[i,1];
    v[i].hi := a[i,k];
    v[i].used := false;
  end;

  QSortX(1,n);
  SortByY;

  nr := n; cont := 0;

  while nr > 0 do
  begin
    cont := cont + 1;
    VerifyAndAdd;
  end;

  write(cont);

  close(input);
  close(output);
end.
