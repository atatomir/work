type elem=record
       v,pos:longint;
     end;
const def= 2000000001;
var n,d,i,l,min:longint;
    a:array[0..1000005]of elem;
    bufin:array[1..65000]of byte;

procedure QSort(l, r: longint);
var
  i, j, x: longint;
  y:elem;
begin
  i := l; j := r; x := a[(l+r) DIV 2].v;
  repeat
    while a[i].v < x do i := i + 1;
    while x < a[j].v do j := j - 1;
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      i := i + 1; j := j - 1;
    end;
  until i > j;
  if l < j then QSort(l, j);
  if i < r then QSort(i, r);
end;

function modulo(x:longint):longint;
begin
  if x < 0 then modulo := -x else modulo := x;
end;

begin
  assign(input,'slidingwindow.in'); reset(input);
  assign(output,'slidingwindow.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,d);
  for i := 1 to n do
  begin
    read(a[i].v);
    a[i].pos := i;
  end;

  QSort(1,n);

  for l := 1 to (n-1) do
  begin
    min := def;
    for i := 1 to (n-l) do
    begin
      if (a[i+l].v - a[i].v) < min then
        if modulo(a[i+l].pos-a[i].pos) <= d then
        begin
          min := a[i+l].v - a[i].v;
        end;
    end;
    if min <> def then break;
  end;
  writeln(min);

  close(input);
  close(output);
end.
