const modd=9917;
type elem=record
       pos:longint;
       val:int64;
     end;
var i:longint;
    aib:array[0..100005]of longint;
    a:array[0..100005]of elem;
    sol,n:int64;

procedure QSort(l,h:longint);
var i,j:longint;
    x,x2:int64;
    y:elem;
begin
  i := l; j := h; x := a[(i+j)div 2].val; x2 := a[(i+j)div 2].pos;
  repeat
    while (a[i].val < x)or((a[i].val=x)and(a[i].pos < x2)) do inc(i);
    while (a[j].val > x)or((a[j].val=x)and(a[j].pos > x2)) do dec(j);
    if i<=j then
    begin
      y := a[i]; a[i] := a[j] ; a[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

function zeros(x:longint):longint;
begin
  zeros := (x xor (x-1))and x;
end;

procedure add(x:longint);inline;
begin
  repeat
    inc(aib[x]);
    x := x + zeros(x);
  until x > n;
end;

function sum(x:longint):int64;
begin
  sum := 0;
  repeat
    sum := sum + aib[x];
    x := x - zeros(x);
  until x = 0;
end;


begin
  assign(input,'inv.in'); reset(input);
  assign(output,'inv.out'); rewrite(output);

  readln(n);
  for i := 1 to n do
  begin
    read(a[i].val);
    a[i].pos := i;
  end;
  QSort(1,n);

  sol := n*(n-1)div 2;

  for i := 1 to n do aib[i] := 0;
  for i := 1 to n do
  begin
    sol := sol - sum(a[i].pos);
    add(a[i].pos);
  end;

  sol := sol mod modd;
  writeln(sol);

  close(input);
  close(output);
end.