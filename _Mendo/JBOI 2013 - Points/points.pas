const modd = 123456789;
var n,i,s,d,x,pas,dif,ant:longint;
    a:array[0..2,0..10010]of longint;
    sum:longint;

begin
  readln(n);

  for i := 0 to 10005 do
  begin
    a[0,i] := 0;
    a[1,i] := 0;
  end;
  s := 0; d := 1;

  read(x); ant := x;
  for i := 1 to x+1 do a[s,i] := 1;

  for pas := 2 to n do
  begin
    read(x);
    if ant > x then dif := 0 else dif := x - ant;
    for i := 1 to dif do a[d,i] := 0;

    for i := 1 to x+1 do
      a[d,i+dif] := (a[d,i+dif-1]+a[s,i])mod modd;

    ant := x;
    s := s xor 1; d := d xor 1;
  end;

  sum := 0;
  for i := dif+1 to x+1 do sum := (sum+a[s,i])mod modd;
  writeln(sum);
end.
