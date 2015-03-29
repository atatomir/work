type plic=record
       x,y:longint;
     end;

var n,i,t,poz,max:longint;
    a:array[0..100001]of plic;
    v,best:array[0..100001]of longint;

procedure QSort(l,h:longint);
var i,j,x,y:longint;
begin
  i := l; j := h; x := (i+j)div 2;
  repeat
    while a[i].x < a[x].x do inc(i);
    while a[j].x > a[x].x do dec(j);
    if i <=j then
    begin
      y := a[i].x; a[i].x := a[j].x; a[j].x := y;
      y := a[i].y; a[i].y := a[j].y; a[j].y := y;
      inc(i); dec(j);
    end;
  until i > j;
  if j > l then QSort(l,j);
  if i < h then QSort(i,h);
end;
function Cautare_Binara(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := v[0];
  while i <= j do
  begin
    m := (i+j)div 2;
    if x <= v[m] then
      j := m-1
    else
      i := m+1;
  end;
  Cautare_Binara := i;
end;

begin
  assign(input,'plicuri.in'); reset(input);
  assign(output,'plicuri.out'); rewrite(output);

  readln(n);
  for i := 1 to n do
  begin
    readln(a[i].x,a[i].y);
    if a[i].x > a[i].y then
    begin
      t := a[i].x; a[i].x := a[i].y; a[i].y := t;
    end;
  end;

  QSort(1,n);

  v[1] := a[1].y;
  v[0] := 1;
  best[1] := 1;


  for i := 2 to n do
  begin
    poz := Cautare_Binara(a[i].y);
    v[poz] := a[i].y;
    best[i] := poz;
    if poz > v[0] then v[0] := poz;
  end;

  writeln(v[0]);

  close(input);
  close(output);
end.
