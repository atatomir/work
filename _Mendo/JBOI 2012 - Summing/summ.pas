type elem=record
       id,pid:longint;
       sum:longint;
     end;
     elemq=record
       sum,pos,smax:longint;
     end;

var n,i,t,m,min:longint;
    a:array[0..100005]of elem;
    q:array[0..100005]of elemq;
    rez:array[0..100005]of longint;
    apar:array[-1..100005]of longint;
    max,k:longint;

procedure QSort(l,h:longint);
var i,j,x:longint;
    y:elem;
begin
  i := l; j := h; x := a[(i+j)div 2].pid;
  repeat
    while a[i].pid < x do inc(i);
    while a[j].pid > x do dec(j);
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

procedure QSortQ(l,h:longint);
var i,j,x:longint;
    y:elemq;
begin
  i := l; j := h; x := q[(i+j)div 2].sum;
  repeat
    while q[i].sum < x do inc(i);
    while q[j].sum > x do dec(j);
    if i <= j then
    begin
      y := q[i]; q[i] := q[j]; q[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSortQ(l,j);
  if i < h then QSortQ(i,h);
end;

function cb(x:longint):longint;
var i,j,mij:longint;
begin
  i := 1; j := m;
  repeat
    mij := (i+j)div 2;
    if x > q[mij].sum then
      i := mij+1
    else
      j := mij-1;
  until i > j;
  cb := i;
end;

procedure Cauta(pc,sum:longint);
var i,h,s:longint;
begin
  h := cb(sum);
  i := apar[pc];

  if i <> 0 then
  while a[i].pid = pc do
  begin
    s := sum + a[i].sum;
    while q[h].sum < s do
    begin
      if q[h].smax < sum then q[h].smax := sum;
      inc(h);
    end;
    Cauta(a[i].id,sum+a[i].sum);
    inc(i);
  end
  else
  if q[h].smax < sum then
    q[h].smax := sum;
end;

begin
{  assign(input,'summ.in'); reset(input);
  assign(output,'summ.out'); rewrite(output);
 }
  readln(n,m); min := 2000000001;
  for i := 1 to n do
  begin
    readln(a[i].sum,a[i].pid);
    a[i].id := i-1;

    if (a[i].pid=-1) and (a[i].sum < min) then min := a[i].sum;
  end;
  QSort(1,n); a[n+1].pid := -7;
  for i := -1 to n do apar[i] := 0;
  for i := 1 to n do
    if apar[a[i].pid] = 0 then apar[a[i].pid] := i;

  for t := 1 to m do
  begin
    readln(q[t].sum);
    q[t].smax := 0;
    q[t].pos := t;
  end;

  QSortQ(1,m); q[m+1].sum := 2000000001;

  Cauta(-1,0);
  for i := 2 to m do
    if q[i].smax < q[i-1].smax then q[i].smax := q[i-1].smax;

  for i := 1 to m do rez[q[i].pos] := q[i].smax;
  for i := 1 to m do
    if rez[i] >= min then
      writeln(rez[i])
    else
      writeln('none');
  {
  close(input);
  close(output);}
end.
