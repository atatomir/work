type formatie=record
       a,b:longint;
     end;

var n,i,j:longint;
    v:array[1..100001]of formatie;
    best:array[0..100001]of longint;
    bufin:array[1..65000]of byte;

procedure Sort(l, r: longint);
var
  i, j, x, y: longint;
begin
  i := l; j := r; x := v[(l+r) DIV 2].b;
  repeat
    while v[i].b < x do i := i + 1;
    while x < v[j].b do j := j - 1;
    if i <= j then
    begin
      y := v[i].a; v[i].a := v[j].a; v[j].a := y;
	  y := v[i].b; v[i].b := v[j].b; v[j].b := y;
      i := i + 1; j := j - 1;
    end;
  until i > j;
  if l < j then Sort(l, j);
  if i < r then Sort(i, r);
end;

function max(x,y:longint):longint;
begin
  if x < y then max := y else max := x;
end;

function cautare_binara(y,cauta:longint):longint;
var u,m:longint;
begin
  u := 1;    cautare_binara := 0;
  repeat
    m := (y-u)div 2 + u;
    if cauta < v[m].b then
    begin
      y := m-1;
    end
    else
    begin
      u := m +1;
    end;
  until u > y;
  cautare_binara := y;
end;

begin
  assign(input,'heavymetal.in'); reset(input);
  assign(output,'heavymetal.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do readln(v[i].a,v[i].b);
  Sort(1,n);

  for i := 1 to n do
  begin
    //j := i-1;
    //while v[i].a < v[j].b do dec(j);
    j := cautare_binara(i-1,v[i].a);
    best[i] := max(best[i-1],best[j]+v[i].b-v[i].a);
  end;

  write(best[n]);

  close(input);
  close(output);
end.
