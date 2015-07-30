var a,b,x,y,n,i:longint;
    r,s:array[0..1005]of longint;

function dif(a,b:longint):longint;
begin
  dif := a-b; if dif < 0 then dif := -dif;
end;

function max(a,b:longint):longint;
begin
  if a < b then max := b else max := a;
end;

begin
  read(n);
  readln(a,b); r[1] := a; s[1] := b;

  for i := 2 to n do
  begin
    readln(x,y);
    r[i] := max(r[i-1]+x+dif(b,y),s[i-1]+x+dif(a,y));
    s[i] := max(r[i-1]+y+dif(b,x),s[i-1]+y+dif(a,x));

    a := x; b := y;
  end;

  a := r[n];
  if s[n] > a then a := s[n];
  writeln(a);

end.