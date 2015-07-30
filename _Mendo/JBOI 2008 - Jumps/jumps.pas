const modd=1000000;
var n:longint;
    sum:int64;

procedure rezolva(n:longint);inline;
begin
  while n >= 6 do
  begin
    sum := sum + n;
    n := n - 6;

    if n mod 5 = 0 then sum := sum mod modd;
  end;
  sum := sum + n; if n = 0 then inc(sum);
end;

begin
  readln(n);
  sum := 0;
  rezolva(n);
  writeln(sum mod modd);
end.
