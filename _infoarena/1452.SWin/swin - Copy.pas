type elem=record
       v,pos:longint;
     end;
const def= 2000000001;
var n,d,i,l,min,j,p,pi:longint;
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

    min := def;
    for i := 1 to (n-1) do
    begin
      if (a[i+1].v - a[i].v) < min then
        if abs(a[i+1].pos-a[i].pos) <= d then
        begin
          min := a[i+1].v - a[i].v;
        end;
    end;

  for i := 1 to n-2 do
  begin
    j := i+2; p := a[i].v; pi := a[i].pos;
    while abs(a[j].pos - pi) > d do
    begin
      inc(j);
      if (j > n)or(a[j].v-p >= min) then break;
    end;
    if j <= n then
      if a[j].v - p < min then min := a[j].v-p;
  end;

  writeln(min);

  close(input);
  close(output);
end.
